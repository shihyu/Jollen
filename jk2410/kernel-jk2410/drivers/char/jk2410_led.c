/*
 *  linux/drivers/char/jk2410_led.c
 *
 *  Copyright (C) 2008 Jollen Chen
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/config.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/ioport.h>
#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/io.h>

struct jk2410_led_data {
	char 	*str;
	int 	idx;
      wait_queue_head_t jk2410_led_wq;
	void *led_mem;
	void *led_data;
};

int jk2410_led_event_full;

/* wait queue */
struct timer_list jk2410_led_int_timer;

/* write data to led */
struct timer_list led_timer;

/* led I/O wrapper function */
#define GPBCON			0x0000
#define	led_write(value)	writel(~(value|GPBCON), cdata2->led_mem)
#define	LED1		(0x1<<10)
#define	LED2		(0x1<<8)
#define	LED3		(0x1<<9)
#define	LED4		(0x1<<7)

#define	NUM_0		(0)
#define	NUM_1		(LED1)
#define	NUM_2		(LED2)
#define	NUM_3		(LED1|LED2)
#define	NUM_4		(LED3)
#define	NUM_5		(LED1|LED3)
#define	NUM_6		(LED2|LED3)
#define	NUM_7		(LED1|LED2|LED3)
#define	NUM_8		(LED4)
#define	NUM_9		(LED1|LED4)
#define	NUM_10		(LED2|LED4)
#define	NUM_11		(LED1|LED2|LED4)
#define	NUM_12		(LED3|LED4)
#define	NUM_13		(LED1|LED3|LED4)
#define	NUM_14		(LED2|LED3|LED4)
#define	NUM_15		(LED1|LED2|LED3|LED4)

void jk2410_led_interrupt_handler(unsigned long x)
{
    struct jk2410_led_data *cdata2 =(struct jk2410_led_data *)x;

    jk2410_led_int_timer.expires =jiffies + 10;
    jk2410_led_int_timer.data=(unsigned long)x;
    jk2410_led_int_timer.function=jk2410_led_interrupt_handler;

    wake_up_interruptible(&cdata2->jk2410_led_wq);
    add_timer(&jk2410_led_int_timer);
}

void write_led(unsigned long x)
{
    struct jk2410_led_data *cdata2 =(struct jk2410_led_data *)x;
	char * str, c;
	int idx;

	led_timer.expires = jiffies + 1*HZ;
	led_timer.data = (unsigned long)x;
	led_timer.function = write_led;

	/* read data buffer */
	str = cdata2->str;
	idx = cdata2->idx;

	if (str == NULL) return;
	if (idx <= 0) return;

	c = str[idx-1];
	idx--;
	cdata2->idx = idx;

	/* write data to led */
	if (c == 0) led_write(NUM_0);
	else if (c == 1) led_write(NUM_1);
	else if (c == 2) led_write(NUM_2);
	else if (c == 3) led_write(NUM_3);
	else if (c == 4) led_write(NUM_4);
	else if (c == 5) led_write(NUM_5);
	else if (c == 6) led_write(NUM_6);
	else if (c == 7) led_write(NUM_7);
	else if (c == 8) led_write(NUM_8);
	else if (c == 9) led_write(NUM_9);
	else if (c == 10) led_write(NUM_10);
	else if (c == 11) led_write(NUM_11);
	else if (c == 12) led_write(NUM_12);
	else if (c == 13) led_write(NUM_13);
	else if (c == 14) led_write(NUM_14);
	else if (c == 15) led_write(NUM_15);

	add_timer(&led_timer);
}

int jk2410_led_open(struct inode *inode, struct file *filp)
{
	int devno;
        int i;
	struct jk2410_led_data *cdata2;

	devno = inode->i_rdev;
	cdata2 = (struct jk2410_led_data *)kmalloc(sizeof(struct jk2410_led_data), GFP_KERNEL);
	if (cdata2 == 0)
		goto fail1;

	memset(cdata2, 0, sizeof(struct jk2410_led_data *));

	cdata2->idx = 0;
	cdata2->str = (char *)kmalloc(64, GFP_KERNEL);
	if (cdata2->str == 0)
		goto fail1;

	memset(cdata2->str, 0, 64);
	init_waitqueue_head(&cdata2->jk2410_led_wq);
	init_timer(&jk2410_led_int_timer);
     
	filp->private_data = cdata2;
	jk2410_led_interrupt_handler((unsigned long)filp->private_data);
	/* GPB control register */
	cdata2->led_mem = ioremap(0x56000010, 4);

	/* GPB data register */
	cdata2->led_data = ioremap(0x56000014, 4);

	/* set GPB */
	writel(0x00154000, cdata2->led_mem);

	return 0;
fail1:
	return -1;
}

int jk2410_led_release(struct inode *inode, struct file *filp)
{
	struct jk2410_led_data *cdata2 = (struct jk2410_led_data *)filp->private_data;
	char *str;

	str = cdata2->str;

	printk(KERN_ALERT "string: %s\n", str);
        
      kfree(cdata2->str);
	kfree(cdata2);
      del_timer(&jk2410_led_int_timer);

	return 0;
}

ssize_t jk2410_led_write(struct file *filp, const char *buff, size_t count, loff_t *offp)
{
	struct jk2410_led_data *cdata2 = (struct card_data2 *)filp->private_data;
	char *str, c;
	int  idx;

	if (count == 0)
		goto fail1;

	idx = cdata2->idx;
	str = cdata2->str;

	if (str == NULL)
		goto fail1;

	if (copy_from_user(&c, buff, 1))
		goto fail1;

	/* filtering, 0x0-0xF (0-15) */
	if (c < '0') c = '0';
	else if (c > '9') c = '9';
	else if ((c|0x20) < 'a') c = 'A';
	else if ((c|0x20) > 'f') c = 'F';

	if ( ((c|0x20) >= 'a') && ((c|0x20) <= 'f') ) {
		c |= 0x20;
		c -= 'a';
	} else {
		c -= '0';
	}

	idx++;

      if ( idx >= 64) {
      		jk2410_led_event_full=1;
	}
repeat:
         if (jk2410_led_event_full == 1) {
      		interruptible_sleep_on(&cdata2->jk2410_led_wq);
           goto repeat;              
        }

	idx = cdata2->idx;
	str[idx++] = c;
	cdata2->idx = idx;

	return 1;
fail1:
	return -EFAULT;
}

static struct file_operations jk2410_led_fops = {
	open:		jk2410_led_open,
	write:		jk2410_led_write,
	release:	jk2410_led_release,
};

int jk2410_led_init_module(void)
{
	printk(KERN_ALERT "registered.\n");

	if (register_chrdev(122, "jk2410-led", &jk2410_led_fops) < 0) {
		printk("Couln't register a device.");
	}

fail1:
	return 0;
}

void jk2410_led_cleanup_module(void)
{
	unregister_chrdev(122, "jk2410-led");
	printk(KERN_ALERT "unregisterd.\n");
}

module_init(jk2410_led_init_module);
module_exit(jk2410_led_cleanup_module);

MODULE_LICENSE("GPL");
