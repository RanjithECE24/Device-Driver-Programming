#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("Simple Tasklet Demonstration");

static void tasklet_entry_function(unsigned long data)
{
	printk(KERN_INFO "tasklet_entry_function");
	mdelay(5000);
}
DECLARE_TASKLET(mytask, tasklet_entry_function, 0);

static int init_tasklet(void)
{
	tasklet_schedule(&mytask);
	mdelay(200);
	return 0;
}

static void exit_tasklet(void)
{
	tasklet_kill(&mytask);
}

module_init(init_tasklet);
module_exit(exit_tasklet);
