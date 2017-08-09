#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("Sample ISR Registration in kernel module");
MODULE_VERSION("0.1");

int flag = 1;

int tempdev = 0;

irqreturn_t sample_isr(int irq, void *dev_id)
{
	printk(KERN_ALERT "\nsample_isr function called\n");
	return IRQ_NONE;		
}

static int __init init_kernel_module(void)
{
	if(request_irq(21, sample_isr, IRQF_SHARED, KBUILD_MODNAME, (void*)&tempdev))
	{
		printk(KERN_ALERT "\nError in isr registration\n");
		flag = 0;	
	}
	return 0;
}

static void __exit exit_kernel_module(void)
{
	if(flag)
		free_irq(21, (void*)&tempdev);
}

module_init(init_kernel_module);
module_exit(exit_kernel_module);
