#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("A Simple Hello World Kernel Module");
MODULE_VERSION("0.1");

static int __init hello_world_module_init(void)
{
	printk(KERN_INFO "\nHello World Kernel Module init\n");
	return 0;
}

static void __exit hello_world_module_exit(void)
{
	printk(KERN_INFO "\nHello World Kernel module exit\n");
}

module_init(hello_world_module_init);
module_exit(hello_world_module_exit);
