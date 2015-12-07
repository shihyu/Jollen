/*
 *  linux/drivers/char/jk2410_gpio.c
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
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/io.h>

#define JK2410_GPIO_IRQ 	IRQ_EINT11	/* S6 */

struct jk2410_gpio_data {
	char 	*str;
	int 	idx;
	wait_queue_head_t jk2410_gpio_rq;
	spinlock_t my_lock;
};

/* events */
int jk2410_gpio_event_empty;

/* interrupt handler */
void jk2410_gpio_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	struct jk2410_gpio_data *cdata = (struct jk2410_gpio_data *)dev_id;
	char *str;
	int idx;
	
	spin_lock(&cdata->my_lock);
	str = cdata->str;
	idx = cdata->idx;

	/* FIXME: */
	str[idx++] = 'A';

    	wake_up_interruptible(&cdata->jk2410_gpio_rq);
	spin_unlock(&cdata->my_lock);

	printk(KERN_ALERT "%d pressed..\n", JK2410_GPIO_IRQ);

	return;
}

int jk2410_gpio_open(struct inode *inode, struct file *filp)
{
	int devno;
	struct jk2410_gpio_data *cdata;

	devno = inode->i_rdev;
	cdata = (struct jk2410_gpio_data *)kmalloc(sizeof(struct jk2410_gpio_data), GFP_KERNEL);
	if (cdata == NULL)
		goto fail1;

	memset(cdata, 0, sizeof(struct jk2410_gpio_data *));
	cdata->idx = 0;

	cdata->str = (char *)kmalloc(64, GFP_KERNEL);
	if (cdata->str == NULL)
		goto fail1;

	memset(cdata->str, 0, 64);

	init_waitqueue_head(&cdata->jk2410_gpio_rq);
     
	filp->private_data = cdata;
	
	/* set external IRQ */
	if (set_external_irq(JK2410_GPIO_IRQ, EXT_RISING_EDGE, GPIO_PULLUP_EN)) {
		printk(KERN_ALERT "cdata: set external irq failed.\n");
		goto fail1;
	}	

	/* request IRQ */
	if (request_irq(JK2410_GPIO_IRQ, jk2410_gpio_handler, SA_SHIRQ, "jk2410-gpio", cdata)){
		printk(KERN_ALERT "cdata: request irq failed.\n");
		goto fail1;
	}

	spin_lock_init(&cdata->my_lock);
	jk2410_gpio_event_empty = 0;

	return 0;
fail1:
	return -1;
}

int jk2410_gpio_release(struct inode *inode, struct file *filp)
{
	struct jk2410_gpio_data *cdata = (struct jk2410_gpio_data *)filp->private_data;
	char *str;

	str = cdata->str;

	printk(KERN_ALERT "string: %s\n", str);
        
	kfree(cdata->str);
	kfree(cdata);
	free_irq(JK2410_GPIO_IRQ, cdata);

	return 0;
}

ssize_t jk2410_gpio_read(struct file *filp, char *buff, size_t count, loff_t *offp)
{
	struct jk2410_gpio_data *cdata = (struct jk2410_gpio_data *)filp->private_data;
	char *str;
	int idx;

	spin_lock(&cdata->my_lock);
	idx = cdata->idx;
	str = cdata->str;
	spin_unlock(&cdata->my_lock);

	if (str == NULL)
		goto fail1;

	idx--;

	/* buffer empty */
	if (idx <= 0) {
		jk2410_gpio_event_empty = 1;
	}
repeat:
	if (jk2410_gpio_event_empty == 1) {
		interruptible_sleep_on(&cdata->jk2410_gpio_rq); 
		goto repeat;   
        }

	spin_lock(&cdata->my_lock);
      	cdata->idx = idx;
	spin_unlock(&cdata->my_lock);

 	if (copy_to_user(buff, &str[idx], 1))
        	goto fail1;
     
	return 1;
fail1:
	return -EFAULT;
}

static struct file_operations jk2410_gpio_fops = {
	open:		jk2410_gpio_open,
	read:		jk2410_gpio_read,
	release:	jk2410_gpio_release,
};

int jk2410_gpio_init_module(void)
{
	printk(KERN_ALERT "registered.\n");

	if (register_chrdev(121, "Card", &jk2410_gpio_fops) < 0) {
		printk("Couln't register a device.");
	}
	return 0;

}

void jk2410_gpio_cleanup_module(void)
{
	unregister_chrdev(121, "jk2410-gpio");
	printk(KERN_ALERT "unregisterd.\n");
}

module_init(jk2410_gpio_init_module);
module_exit(jk2410_gpio_cleanup_module);

MODULE_LICENSE("GPL");
