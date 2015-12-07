/*
 * linux/arch/arm/mach-s3c2410/dma.c
 *
 * Copyright (C) 2001 MIZI Research, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *
 * History
 *
 * 2002-01-xx: 김민근
 *    - dma-sa1100.c를 참고해서 어느정도 동작하도록 만듦.
 *
 * 2002-03-20: Janghoon Lyu <nandy@mizi.com>
 *    - change queue structure
 *        The S3C2400's DMA controller has not internal hardware buffer.
 *
 * 2002-04-09: Janghoon Lyu <nandy@mizi.com>
 *    - BUG: UDA1330을 이용해서 MP3파일을 플레이하는 도중에 DMA-done 인터럽트
 *           를 놓치는 경우가 있다.
 *      WORKAROUD: timer를 하나 두어서 DMA-done 인터럽트를 놓칠 경우, 이를 복원
 *                 해준다.
 *
 * 2002-04-24: Janghoon Lyu <nandy@mizi.com>
 *    - USB를 위해서 DMA구조를 변경하였습니다.
 *    - 실제로 테스트가 필요합니다.
 *
 * 2002-05-02: Janghoon Lyu <nandy@mizi.com>
 *    - 이전에는 단방향만을 고려했는 R/W를 모두 고려한 구조로 변경
 *    - BUG: DMA 채널은 4개 인데 타이머는 하나 뿐? 구조 고칠 것
 *
 * 2002-05-07: Janghoon Lyu <nandy@mizi.com>
 *    - 다시 새로운 구조로(황소장님 아이디어)
 *    - 타이머는 여전히 불안...
 *
 * 2002-05-09: Janghoon Lyu <nandy@mizi.com>
 *    - s3c2400_dma_set_callback() 함수를 request_dma()로 통합
 *    - 타이머 관련된 부분 HOOK_LOST_INT로 정리
 *    - 타이머 관리는 여전히 안되고 있음. BIG BUG...
 *    - 개선해보려고 시도를 해봤는데, 자승자박. 
 *       flush()할 때 timer를 처리를 해 줘야 되는건가?
 *
 * 2002-05-28: Janghoon Lyu <nandy@mizi.com>
 *    - S3C2400에 것을 S3C2410으로 옮김
 *
 * TODO:
 *   - sleep & wakeup 할 때의 코드를 추가해야 합니다.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/errno.h>

#include <asm/irq.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/dma.h>

#include "dma.h"

/* debug macros */
#undef DEBUG
#ifdef DEBUG
#define DPRINTK( s, arg... )  printk( "dma<%s>: " s, dma->device_id , ##arg )
#else
#define DPRINTK( x... )
#endif

/*
 * DMA processing...
 */

static void process_dma(s3c2410_dma_t *dma)
{
	dma_buf_t *buf, *next_buf;
	dma_regs_t *regs = dma->regs;
	int data_size, data_cnt; /* DMA request가 발생 할 때 보내는 데이터 크기 */
	dma_device_t *device;

	buf = dma->head;
	if (buf && (!dma->active)) {
		if (buf->write) {
			device = &dma->write;
			regs->DISRCC = device->src_ctl;
			regs->DISRC = DMA_BASE_ADDR(buf->dma_start);
			regs->DIDSTC = device->dst_ctl;
			regs->DIDST = device->dst;
		} else {
			device = &dma->read;
			regs->DISRCC = device->src_ctl;
			regs->DISRC = device->src;
			regs->DIDSTC = device->dst_ctl;
			regs->DIDST = DMA_BASE_ADDR(buf->dma_start);
		}
		data_size = readDSZ(device->ctl);
		switch(data_size) {
			case DSZ_BYTE: data_cnt = TX_CNT(buf->size); break;
			case DSZ_HALFWORD: data_cnt = TX_CNT(buf->size/2); break;
			default: data_cnt = TX_CNT(buf->size/4); break;
		}
		regs->DCON = device->ctl | data_cnt;
		regs->DMASKTRIG = (DMA_STOP_CLR | CHANNEL_ON | DMA_SW_REQ_CLR);
		dma->curr = buf;
		next_buf = dma->head->next;
		dma->head = next_buf;
		if (!next_buf)
			dma->tail = NULL;
		dma->active = 1;
		dma->queue_count--;
		DPRINTK("start dma_ptr=%#x size=%d\n", buf->dma_start, buf->size);
		DPRINTK("number of buffers in queue: %ld\n", dma->queue_count);
#ifdef HOOK_LOST_INT
		if (buf->write) start_dma_timer();
#endif
	}
}

static inline void s3c2410_dma_done(s3c2410_dma_t *dma)
{
	dma_buf_t *buf = dma->curr;
	dma_callback_t callback;

	if (buf->write) callback = dma->write.callback;
	else callback = dma->read.callback;

#ifdef HOOK_LOST_INT
	stop_dma_timer();
#endif
	DPRINTK("IRQ: b=%#x st=%ld\n", (int)buf->id, (long)dma->regs->DSTAT);
	if (callback)
		callback(buf->id, buf->size);
	kfree(buf);
	dma->active = 0;
	process_dma(dma);
}

static void dma_irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	s3c2410_dma_t *dma = (s3c2410_dma_t *)dev_id;

	DPRINTK(__FUNCTION__"\n");

	s3c2410_dma_done(dma);
}

#ifdef HOOK_LOST_INT
static void dma_timer_irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	s3c2410_dma_t *dma = NULL;
	int channel;

	//DPRINTK("in timer interrupts\r\n");
	for (channel = 0; channel < MAX_S3C2410_DMA_CHANNELS; channel++) {
		dma = &dma_chan[channel];
		if ((dma->in_use == 1) && (dma->regs->DSTAT == 0x0) && (dma->active)) {
			DPRINTK(__FUNCTION__" channel=%d\n", (int)channel);
			s3c2410_dma_done(dma);
		}
	}
}
#endif

/*
 * DMA interface functions
 */

static int fill_dma_source(int channel, const char *dev_name, 
			   dma_device_t *write, dma_device_t *read)
{
	int source;
	dma_type_t *dma_type = dma_types[channel];
	for(source=0;source<4;source++) {
		if (strcmp(dma_type[source].name, dev_name) == 0)
			break;
	}
	if (source >= 4) return -1;

	dma_type += source;

	write->src = dma_type->write_src;
	write->dst = dma_type->write_dst;
	write->ctl = dma_type->write_ctl;
	write->src_ctl = dma_type->write_src_ctl;
	write->dst_ctl = dma_type->write_dst_ctl;

	read->src = dma_type->read_src;
	read->dst = dma_type->read_dst;
	read->ctl = dma_type->read_ctl;
	read->src_ctl = dma_type->read_src_ctl;
	read->dst_ctl = dma_type->read_dst_ctl;

	return 0;
}

static spinlock_t dma_list_lock;
int s3c2410_request_dma(const char *device_id, dmach_t channel,
			dma_callback_t write_cb, dma_callback_t read_cb)
{
	s3c2410_dma_t *dma;
	int err;

	if ((channel < 0) || (channel >= MAX_S3C2410_DMA_CHANNELS)) {
		printk(KERN_ERR "%s: not support #%d DMA channel\n", device_id, channel);
		return  -ENODEV;
	}
	err = 0;
	spin_lock(&dma_list_lock);
	dma = &dma_chan[channel];
	if (dma->in_use) {
		printk(KERN_ERR "%s: DMA channel is busy\n", device_id);
		err = -EBUSY;
	} else {
		dma->in_use = 1;
	}
	spin_unlock(&dma_list_lock);
	if (err)
		return err;

	err = fill_dma_source(channel, device_id, &dma->write, &dma->read);
	if (err < 0) {
		printk(KERN_ERR "%s: can not found this devcie\n", device_id);
		dma->in_use = 0;
		return err;
	}

	err = request_irq(dma->irq, dma_irq_handler, 0 * SA_INTERRUPT,
					  device_id, (void *)dma);

	if (err) {
		printk( KERN_ERR
			"%s: unable to request IRQ %d for DMA channel\n",
			device_id, dma->irq);
		dma->in_use = 0;
		return err;
	}

	dma->device_id = device_id;
	dma->head = dma->tail = dma->curr = NULL;
	dma->write.callback = write_cb;
	dma->read.callback = read_cb;
	DPRINTK("write cb = %p, read cb = %p\n", dma->write.callback, dma->read.callback);
	DPRINTK("requested\n");
	return 0;
}

int s3c2410_dma_queue_buffer(dmach_t channel, void *buf_id,
			     dma_addr_t data, int size, int write)
{
	s3c2410_dma_t *dma;
	dma_buf_t *buf;
	int flags;

	dma = &dma_chan[channel];
	if ((channel >= MAX_S3C2410_DMA_CHANNELS) || (!dma->in_use))
		return -EINVAL;

	buf = kmalloc(sizeof(*buf), GFP_ATOMIC);
	if (!buf)
		return -ENOMEM;

	buf->next = NULL;
	buf->ref = 0;
	buf->dma_start = data;
	buf->size = size;
	buf->id = buf_id;
	buf->write = write;
	DPRINTK("queueing b=%#x, a=%#x, s=%d, w=%d\n", (int) buf_id, data, size, write);

	local_irq_save(flags);
	if (dma->tail)
		dma->tail->next = buf;
	else
		dma->head = buf;	
	dma->tail = buf;
	buf->next = NULL;
	dma->queue_count++;
	DPRINTK("number of buffers in queue: %ld\n", dma->queue_count);
	process_dma(dma);
	local_irq_restore(flags);

	return 0;
}

/*
 * dma_get_current()를 호출한 후 dma_stop()을 호출해야 합니다.
 * 역순으로 하면 원하는 값이 안 나올수도 있습니다.
 */
int s3c2410_dma_get_current(dmach_t channel, void **buf_id, dma_addr_t *addr)
{
	s3c2410_dma_t *dma = &dma_chan[channel];
	dma_regs_t *regs;
	int flags, ret;

	if ((channel >= MAX_S3C2410_DMA_CHANNELS) || (!dma->in_use)) 
		return -EINVAL;

	regs = dma->regs;
	local_irq_save(flags);
	if (dma->curr) {
		dma_buf_t *buf = dma->curr;
		int status = regs->DSTAT;

		if (buf_id)
			*buf_id = buf->id;
		if (status > 0)
			*addr = regs->DCSRC;
		DPRINTK("curr_pos: b=%#x a=%#x\n", (int)dma->curr->id, *addr);
		ret = 0;
	} else if (dma->head && !dma->active) {
		dma_buf_t *buf = dma->head;
		if (buf_id)
			*buf_id = buf->id;
		*addr = buf->dma_start;
		ret = 0;
	} else {
		if (buf_id)
			*buf_id = NULL;
		*addr = 0;
		ret = -ENXIO;
	}
	local_irq_restore(flags);
	return ret;
}

/*
 * 해당 채널의 DMA controller를 정지시킵니다.
 * dma_resume()에 대해서는 아직 고려가 안 되어있습니다.
 */
int s3c2410_dma_stop(dmach_t channel)
{
	s3c2410_dma_t *dma = &dma_chan[channel];
	dma_buf_t *buf = dma->curr;
	dma_regs_t *regs = dma->regs;
	dma_callback_t callback;
	int flags;

	if (!dma->active)
		return 0;

	local_irq_save(flags);
#ifdef HOOK_LOST_INT
	stop_dma_timer();
#endif
	regs->DMASKTRIG = DMA_STOP; 

	if (buf->write) callback = dma->write.callback;
	else callback = dma->read.callback;

	if (callback)
		callback(buf->id, buf->size);

	kfree(buf);
	dma->active = 0;
	process_dma(dma);
	local_irq_restore(flags);
	DPRINTK("dma stopped\n");
	return 0;
}

int s3c2410_dma_flush_all(dmach_t channel)
{
	s3c2410_dma_t *dma = &dma_chan[channel];
	dma_buf_t *buf, *next_buf;
	int flags;

	if ((channel >= MAX_S3C2410_DMA_CHANNELS) || (!dma->in_use))
		return -EINVAL;

	local_irq_save(flags);
	dma->regs->DMASKTRIG = DMASKTRIG_STOP;
	buf = dma->head;
	dma->head = dma->tail = dma->curr = NULL;
	dma->active = 0;
	dma->queue_count = 0;
	dma->active = 0;
	local_irq_restore(flags);
	while (buf) {
		next_buf = buf->next;
		kfree(buf);
		buf = next_buf;
	}
	DPRINTK("flushed\n");
	return 0;
}

void s3c2410_free_dma(dmach_t channel)
{
	s3c2410_dma_t *dma;

	if (channel >= MAX_S3C2410_DMA_CHANNELS)
		return;

	dma = &dma_chan[channel];
	if (!dma->in_use) {
		printk(KERN_ERR "Trying to free DMA%d\n", channel);
		return;
	}

	s3c2410_dma_flush_all(channel);

	free_irq(dma->irq, (void *)dma);

	dma->in_use = 0;
#ifdef HOOK_LOST_INT
	stop_dma_timer();
#endif

	DPRINTK("freed\n");
}

EXPORT_SYMBOL(s3c2410_request_dma);
EXPORT_SYMBOL(s3c2410_dma_queue_buffer);
EXPORT_SYMBOL(s3c2410_dma_get_current);
EXPORT_SYMBOL(s3c2410_dma_stop);
EXPORT_SYMBOL(s3c2410_dma_flush_all);
EXPORT_SYMBOL(s3c2410_free_dma);

static int __init s3c2410_init_dma(void)
{
	int channel;
#ifdef HOOK_LOST_INT
	int ret;
#endif

	for (channel = 0; channel < (MAX_S3C2410_DMA_CHANNELS); channel++) {
		dma_chan[channel].regs =
				(dma_regs_t *)io_p2v(0x4b000000 + 0x40 * channel);
		dma_chan[channel].irq = IRQ_DMA0 + channel;
		dma_chan[channel].channel = channel;
	}

#ifdef HOOK_LOST_INT
	/* 필요한가? 확인 사살용 */
	stop_dma_timer();
	ret = request_irq(IRQ_TIMER3, dma_timer_irq_handler, SA_INTERRUPT,
			  "DMA timer", NULL);
	if (ret)
		printk(__FUNCTION__ " : could not allocate IRQ (errno %d)\n", ret);
#endif

	return 0;
}

__initcall(s3c2410_init_dma);
