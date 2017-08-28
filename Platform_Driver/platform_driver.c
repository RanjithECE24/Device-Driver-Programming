#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("A Simple Platform Driver");

static struct resource res[] = {
	{
		.flags = IORESOURCE_MEM,
		.start = 0x3f8,
		.end = 0x3ff,
	},
	{
		.flags = IORESOURCE_MEM,
		.start = 0x4f8,
		.end = 0x4ff,
	},
	{
		.flags = IORESOURCE_IRQ,
		.start = 4,
		.end = 4,
	},
};

static int __devinit pf_driver_probe(struct platform_device *pdev)
{
	printk(KERN_ALERT "pf_driver_probe : %s\n", pdev->name);
	char *data = NULL;
	struct resource *resource_data = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if(resource_data != NULL);
		printk(KERN_ALERT "resource_data->start = %d, resource_data->end = %d, size of resource_data = %d", resource_data->start, resource_data->end, resource_size(resource_data));
	struct resource *resource_data1 = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if(resource_data1 != NULL);
		printk(KERN_ALERT "resource_data1->start = %d, resource_data1->end = %d, size of resource_data1 = %d", resource_data1->start, resource_data1->end, resource_size(resource_data1));
	struct resource *resource_data2 = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if(resource_data1 != NULL);
		printk(KERN_ALERT "resource_data2->start = %d, resource_data2->end = %d, size of resource_data2 = %d", resource_data2->start, resource_data2->end, resource_size(resource_data2));
	data = dev_get_platdata(&pdev->dev);
	if(data != NULL)
		printk(KERN_ALERT "platform device data = %s", data);
	return 0;
}

static int pf_driver_remove(struct platform_device *pdev)
{
	printk(KERN_ALERT "pf_driver_remove");
	return 0;
}

static struct platform_driver pf_driver = {
	.driver = {
		.name = "platform_driver",
		.owner = THIS_MODULE,
	},
	.probe = pf_driver_probe,
	.remove = pf_driver_remove,
};

static void pf_device_release(struct device *dev)
{
	printk(KERN_ALERT "pf_device_release");
}

static struct platform_device pf_device = {
	.name = "platform_driver",
	.id = 0,
	.resource = res,
	.num_resources = ARRAY_SIZE(res),
	.dev.platform_data = "simple platform driver",
	.dev.release = pf_device_release,
};

static int __init drivertest_init(void)
{
	platform_device_register(&pf_device);
	platform_driver_register(&pf_driver);
	return 0;
}

static void __exit drivertest_exit(void)
{
	platform_driver_unregister(&pf_driver);
	platform_device_unregister(&pf_device);
}

module_init(drivertest_init);
module_exit(drivertest_exit);
