#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include "cdata_ioctl.h"


#ifdef CONFIG_SMP
#define __SMP__
#endif

#define CDATA_MAJOR 121 

struct cdata_t {
    char    *buf;
    int     index;
    wait_queue_head_t   wq;
    struct timer_list   timer;
};

int cdata_open(struct inode *inode, struct file *filp)
{
    struct cdata_t *cdata;


    printk(KERN_ALERT "hugh cdata: in cdata_open\n");

    printk(KERN_ALERT "filep=0x%p\n", (void*)filp );


    cdata = (struct cdata_t *)kmalloc(sizeof(struct cdata_t), GFP_KERNEL);
    cdata->buf = (char *)kmalloc(128, GFP_KERNEL);

    cdata->index = 0;

    init_waitqueue_head(&cdata->wq);
   
    init_timer(&cdata->timer);

    filp->private_data = (void *)cdata;

    return 0;
}

long cdata_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	char* temp_str;
    	struct cdata_t *cdata;

	cdata=(struct cdata_t *)filp->private_data;
	
	switch(cmd) {
     
   	case IOCTL_EMPTY:
      		printk(KERN_ALERT "hugh cdata: in ioctl: IOCTL_EMPTY");		
    	        memset(cdata->buf, 0, 128);	
      	break;

	case IOCTL_SYNC:
		temp_str=(char*)cdata->buf;
      		printk(KERN_ALERT "hugh cdata: in ioctl: IOCTL_SYNC");
		printk(KERN_ALERT "cdata->buf=%s \n", temp_str );
	break;

	case IOCTL_NAME:
		temp_str=(char*)arg;
      		printk(KERN_ALERT "hugh cdata: received msg= %s", temp_str);
	break;

	case IOCTL_WRITE:
      		printk(KERN_ALERT "hugh cdata: in ioctl: IOCTL_WRITE");
		strcpy(cdata->buf, (char*)arg);
	break;
	default:
      		printk(KERN_ALERT "hugh cdata: ioctl default");
		return -ENOTTY;
	}//end of switch

	return 0;
}

int cdata_release(struct inode *inode, struct file *filp)
{
        struct cdata_t *cdata = (struct cdata_t *)filp->private_data;
	del_timer(&cdata->timer);
        printk(KERN_ALERT "hugh cdata: in cdata_release()\n");
        printk(KERN_ALERT "hugh cdata: flush buf = %s\n", cdata->buf);
        return 0;
}

void flush_data(unsigned long priv)
{

	struct cdata_t *cdata = (struct cdata_t *) priv;	
	//move data to HD

	//remove data from buffer
	
	cdata->index=0;
	//wake up the task
	wake_up(&cdata->wq);
}

ssize_t cdata_write(struct file *filp, const char __user *buf, size_t size, loff_t *off)
{
    int i;
    struct cdata_t *cdata = (struct cdata_t *)filp->private_data;
    char *data = cdata->buf;
    unsigned int index = cdata->index;
    struct timer_list *timer = &cdata->timer;

    DECLARE_WAITQUEUE(wait, current);

    for(i = 0; i < size ; i++)
    {
	copy_from_user(&data[index], &buf[i], 1);
	index++;
	
	//remember to move overflow here

    }
    
    if(index >= 128){
	//no space
	timer->expires = jiffies + 500;
	timer->data = (unsigned long)cdata;
	timer->function = &flush_data;
	add_timer(timer);

#if 0 //not atomic 
	//interruptible_sleep_on(&cdata->wq);

#else //atomic

	#if 0 //macro with spinlock

		prepare_to_wait(&cdata->wq, &wait, TASK_INTERRUPTIBLE);

	#else //step by step
		//1. change status
		set_current_state(TASK_INTERRUPTIBLE);
	
		//2. put current into wait queue
    		add_wait_queue(&cdata->wq, &wait);
	
		//init_waitqueue_head(&cdata->wq);
		//3. call schedule
		schedule();
	#endif
	
#endif	

	index = cdata->index; // *sys*

    }

    printk(KERN_ALERT "hugh cdata: cdata_write = %s\n", data);
    cdata->index=index;

    return 0;
}

struct file_operations cdata_fops = {
     .owner = 	      THIS_MODULE,
     .open =  	      cdata_open,
     .release =         cdata_release,
     .unlocked_ioctl =           cdata_ioctl,
     //read:           cdata_read,
     .write =          cdata_write,
};

/*
static struct miscdevice cdata_misc = {
        minor:  20,
        name:   "cdata-test",
        fops:   &cdata_fops,
};
*/

int my_init_module(void)
{

	if(register_chrdev(CDATA_MAJOR, "cdata", &cdata_fops) < 0)
	{
		printk("KERN_INFO" "CDATA: canʼt register driver\n");
		return -1;
	}
	/*
         if (misc_register(&cdata_misc)) {
                 printk(KERN_ALERT "hugh cdata: register failed\n");
                 return -1;
         }
	*/
         printk(KERN_ALERT "hugh cdata module: registered.\n");
 
         return 0;
}
 
void my_cleanup_module(void)
{

	unregister_chrdev(CDATA_MAJOR, "cdata");	
         //misc_deregister(&cdata_misc);
	
        printk(KERN_ALERT "hugh cdata module: unregisterd.\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);
 
MODULE_LICENSE("GPL");

