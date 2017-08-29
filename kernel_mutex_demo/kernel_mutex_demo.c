#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("Mutex demo");

static struct task_struct *thread1_cb = NULL;
static struct task_struct *thread2_cb = NULL;

static int counter = 0;

DEFINE_MUTEX(mutex_cb);

static int kthread1_entry_function(void *data)
{
	while(!kthread_should_stop())
	{
		mutex_lock(&mutex_cb);
		counter++;
		printk(KERN_ALERT "kthread1_entry_function: counter = %d", counter);
		ssleep(2);
		mutex_unlock(&mutex_cb);
		schedule();		
	}
	printk(KERN_ALERT "Kernel Thread1 Exiting");
	do_exit(0);
	return 0;
}

static int kthread2_entry_function(void *data)
{
	while(!kthread_should_stop())
	{
		mutex_lock(&mutex_cb);
		counter++;
		printk(KERN_ALERT "kthread2_entry_function: counter = %d", counter);
		ssleep(2);
		mutex_unlock(&mutex_cb);
		schedule();
	}
	printk(KERN_ALERT "Kernel Thread2 Exiting");
	do_exit(0);
	return 0;
}

static int __init kernel_threads_init()
{
	thread1_cb = kthread_run(kthread1_entry_function, NULL, "kthread1");
	if(thread1_cb)
		printk(KERN_ALERT "Kernel Thread1 created successfully");
	else
		printk(KERN_ALERT "Kernel Thread1 creation failed");
	thread2_cb = kthread_run(kthread2_entry_function, NULL, "kthread2");
	if(thread2_cb)
		printk(KERN_ALERT "Kernel Thread2 created successfully");
	else
		printk(KERN_ALERT "Kernel Thread2 creation failed");
	return 0;
}

static void __exit kernel_threads_exit()
{
	if(thread1_cb)
	{
		kthread_stop(thread1_cb);
		printk(KERN_ALERT "Kernel Thread1 Stop Requested");
	}
	if(thread2_cb)
	{
		kthread_stop(thread2_cb);
		printk(KERN_ALERT "Kernel Thread2 Stop Requested");
	}
}

module_init(kernel_threads_init);
module_exit(kernel_threads_exit);
