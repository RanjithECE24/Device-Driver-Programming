#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/semaphore.h>

#define DATA_SIZE	1024
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ranjith Thangavel");
MODULE_DESCRIPTION("Semaphore Demo");

static char data[DATA_SIZE] = {0};

static struct semaphore semaphore_cb;

static int misc_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "misc_open");
	return 0;
}

static ssize_t misc_read(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
	int ret = down_interruptible(&semaphore_cb);
	if(ret != 0)
	{
		printk(KERN_ALERT "Unable to acquire semaphore");
		return -ret;
	}
	size_t data_size = strlen(data);
	int bytes_to_read = data_size - *ppos;
	if(bytes_to_read == 0)
		return 0;
	int bytes_read = bytes_to_read - (copy_to_user(buf, (data + *ppos), bytes_to_read));
	*ppos += bytes_read;
	printk(KERN_ALERT "misc_read : bytes_to_read = %d, bytes_read = %d", bytes_to_read, bytes_read);
	return 0;
}

static ssize_t misc_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
	up(&semaphore_cb);
	size_t data_size = strlen(data);
	if(len < data_size)
		memset(data, '\0', DATA_SIZE);
	strncpy(data, buf, len);
	printk(KERN_ALERT "misc_write : %s size = %d", data, len);
	return len;
}

static int misc_release(struct inode *inodep, struct file *filp)
{
	printk(KERN_ALERT "misc_close");
	return 0;
}

static const struct file_operations misc_operations = {
	.owner = THIS_MODULE,
	.open = misc_open,
	.release = misc_release,
	.read = misc_read,
	.write = misc_write
};

struct miscdevice misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "misc_driver",
	.fops = &misc_operations
};

static int __init misc_driver_init(void)
{
	int ret = misc_register(&misc_device);
	sema_init(&semaphore_cb, 0);
	return ((ret != 0) ? ret : 0);
}

static void __exit misc_driver_init_cleanup(void)
{
	misc_deregister(&misc_device);
}

module_init(misc_driver_init);
module_exit(misc_driver_init_cleanup);
