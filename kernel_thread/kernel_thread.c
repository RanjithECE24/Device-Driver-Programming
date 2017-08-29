#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("Kernel Thread demo");

static struct task_struct *thread_cb = NULL;

static int kthread_entry_function(void *data)
{
	char *received_data = (char*)data;
	printk(KERN_ALERT "received_data = %s", received_data);
	allow_signal(SIGKILL);
	while(!kthread_should_stop())
	{
		printk(KERN_ALERT "Kernel Thread Running");
		ssleep(5);
		if(signal_pending(thread_cb))
			break;
	}
	printk(KERN_ALERT "Kernel Thread Exiting");
	do_exit(0);
	return 0;
}

static int __init kthread_init()
{
	thread_cb = kthread_run(kthread_entry_function, "123", "kthread_demo");
	if(thread_cb)
		printk(KERN_ALERT "Kernel Thread created successfully\n");
	else
		printk(KERN_ALERT "Kernel Thread creation failed\n");
	return 0;
}

static void __exit kthread_exit()
{
	if(thread_cb)
	{
		kthread_stop(thread_cb);
		printk(KERN_ALERT "Kernel Thread Stop Requested");
	}
}

module_init(kthread_init);
module_exit(kthread_exit);
