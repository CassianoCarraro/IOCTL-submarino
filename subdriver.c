#include <linux/kernel.h>	
#include <linux/module.h>	
#include <linux/fs.h>
#include <linux/string.h>
#include <asm/uaccess.h>

#include "subdriver.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cassiano Carraro, Daniel Balbinot");
MODULE_DESCRIPTION("Submarino");

#define DEVICE 60
#define DEVICE_NAME "submarino"

int init_device(void);
void cleanup_device(void);
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length,loff_t * offset);
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

module_init(init_device);
module_exit(cleanup_device);

static char key;

struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,	
	.unlocked_ioctl = device_ioctl,
};

int init_device(){
	register_chrdev(DEVICE, DEVICE_NAME, &fops);
	printk("O dispositivo %s foi carregado.\n", DEVICE_NAME);
	return 0;
}

void cleanup_device(){
	unregister_chrdev(DEVICE, DEVICE_NAME);
	printk("O dispositivo %s foi descarregado.\n", DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file){	
	return 0;
}

static int device_release(struct inode *inode, struct file *file){
	return 0;
}

static ssize_t device_read(struct file *file, char __user * buffer, size_t length, loff_t * offset){
	put_user(key, buffer);

	if (!key) {
		return 0;
	}
	key = 0;

	return 1;
}

static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset){	
	char keyTmp;
	get_user(keyTmp, buffer++);

	if (keyTmp >= 65 && keyTmp <= 68) {
		key = keyTmp;
	}

	return 1;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param){
	switch (ioctl_num) {
		case IOCTL_SET_KEY:
			device_write(file, (char *)ioctl_param, 1, 0);
			break;
		case IOCTL_GET_KEY:
			device_read(file, (char *)ioctl_param, 1, 0);
			break;
		default:
			return FAILURE;
	}

	return SUCCESS;
}