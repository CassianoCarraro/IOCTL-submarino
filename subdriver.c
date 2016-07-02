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
#define BUF_LEN 1

int init_device(void);
void cleanup_device(void);
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length,loff_t * offset);
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

module_init(init_device);
module_exit(cleanup_device);

static char mensagem[BUF_LEN];

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
	printk("O dispositivo %s foi lido.\n", DEVICE_NAME);

	return 0;
}

static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset){	
	printk("O dispositivo %s foi escrito.\n", DEVICE_NAME);

	return length;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param){
	device_write(file, (char *)ioctl_param, 0, 0);
	return SUCCESS;
}