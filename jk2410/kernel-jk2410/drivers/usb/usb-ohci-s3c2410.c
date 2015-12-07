/*
 *  linux/drivers/usb/usb-ohci-s3c2410.c
 *
 *  OHCI r1.0 compatible, CPU embedded USB host controller
 *
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/pci.h>

#include <asm/hardware.h>
#include <asm/irq.h>
#include <asm/io.h>

#define OHCI_HW_DRIVER 1
#include "usb-ohci.h"

/*
 * S3C2410 user's guide �� �ִ� 1�� ¥�� ���� ���ϸ�,
 * OHCI ȣȯ�̶�� �Ѵ�.
 *
 * UPLL ������ MISC �������Ϳ��� ��Ʈ ���̰� �츮�� �ϴ� ���� ������ �� ��.
 *
 * �׸���, s3c2410 ���� USB slave �� ������ host ��Ʈ �ϳ��� �׿��� �Ѵٴ� ��
 * ���� �� ��.
 * ������, �̷��� �ص� slave ��ȣ�� root hub �ʿ� �ִ� ������ ���� ����� ����.
 * hub.c �� ���ļ� root hub �̰�, 1 host port �� config ���� ���,
 * �� ��° ��Ʈ�� �ƿ� �Ĵٵ� ���� �ʵ��� ������ ������ ��.
 */

int __devinit
hc_add_ohci(struct pci_dev *dev, int irq, void *membase, unsigned long flags,
	    ohci_t **ohci, const char *name, const char *slot_name);
extern void hc_remove_ohci(ohci_t *ohci);

static ohci_t *s3c2410_ohci;

static void __init s3c2410_ohci_configure(void)
{
#if CONFIG_MAX_ROOT_PORTS < 2
	/* 1 host port, 1 slave port*/
	MISCCR &= ~MISCCR_USBPAD;

#if 0 // confused - bushi
	/* wakeup port 0 */
	MISCCR &= ~MISCCR_USB0_SUSPEND;
	/* sleep port 1 */
	MISCCR |= MISCCR_USB1_SUSPEND;
#endif

#else
	/* 2 host port */
	MISCCR |= MISCCR_USBPAD;

#if 0 // confused - bushi
	/* wakeup port 0 */
	MISCCR &= ~MISCCR_USB0_SUSPEND;
	/* wakeup port 1 */
	MISCCR &= ~MISCCR_USB1_SUSPEND;
#endif

#endif

	/* UPLLCON */
	UPLLCON = FInsrt(0x78, fPLL_MDIV) | FInsrt(0x02, fPLL_PDIV) 
		| FInsrt(0x03, fPLL_SDIV);

	/* CLKCON */
	CLKCON |= CLKCON_USBH;

	udelay(11);
}

static int __init s3c2410_ohci_init(void)
{
	int ret;

	s3c2410_ohci_configure();

	/*
	 * Initialise the generic OHCI driver.
	 */
	// FIXME : io_p2v() ?
	ret = hc_add_ohci((struct pci_dev *)1, IRQ_USBH,
			  (void *)(io_p2v(USBHOST_CTL_BASE)), 0, &s3c2410_ohci,
			  "usb-ohci", "s3c2410");

	return ret;
}

static void __exit s3c2410_ohci_exit(void)
{
	hc_remove_ohci(s3c2410_ohci);

	/*
	 * Stop the USB clock.
	 */
	CLKCON &= ~CLKCON_USBH;
}

module_init(s3c2410_ohci_init);
module_exit(s3c2410_ohci_exit);
