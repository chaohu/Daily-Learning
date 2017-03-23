#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ajay");  
MODULE_DESCRIPTION("ajay->A simple virtual char device.");


int mydev_open(struct inode *inode,struct file *filp);
int mydev_release(struct inode *inode,struct file *filp);
static ssize_t mydev_read(struct file *filp,char __user *buf,size_t size,loff_t *f_pos);
static ssize_t mydev_write(struct file *filp,const char __user *buf,size_t size,loff_t *f_pos);
int mydev_init(void);
void mydev_exit(void);

struct file_operations mydev_fops = {
	owner:THIS_MODULE,
	read:mydev_read,
	write:mydev_write,
	open:mydev_open,
	release:mydev_release
};

struct dev_buff {
	struct cdev my_dev;
	char data[4096];
};

int mydev_major = 60;
char *mydev_buffer;
struct dev_buff *dev_buff;
int r_locate = 0;
int w_locate = 0;


module_init(mydev_init);
module_exit(mydev_exit);


//模块装载时初始化
int mydev_init(void) {
	int result;
	result = register_chrdev(mydev_major,"mydev",&mydev_fops);
	if(result < 0) {
		printk("<1>mydev:can't obtain major number %d\n",mydev_major);
		return result;
	}

	//申请内存
	dev_buff = kmalloc(sizeof(struct dev_buff),GFP_KERNEL);
	if(!dev_buff) {
		result = - ENOMEM;
		mydev_exit();
		return result;
	}
	memset(dev_buff,0,sizeof(struct dev_buff));

	printk("<1>Inserting mydev module\n");
	return 0;
}


void mydev_exit(void) {
	unregister_chrdev(mydev_major,"mydev");
	if(dev_buff) kfree(dev_buff);
    printk("<1>Removing mydev module\n");
}

int mydev_open(struct inode *inode,struct file *filp) {
	r_locate = 0;
	w_locate = 0;
	unsigned int num = MINOR(inode->i_rdev);
	if(num >= 2) return -ENODEV;
	filp->private_data = dev_buff;
	return 0;
}

int mydev_release(struct inode *inode,struct file *filp) {
	return 0;
}

static ssize_t mydev_read(struct file *filp,char __user *buf,size_t size, loff_t *f_pos) {
	unsigned long p = r_locate;	//记录文件指针的偏移位置
	unsigned int count = size;	//记录需要读取的字节数
	int ret = 0;	//返回值
	struct dev_buff *dev_temp = filp->private_data;	//获得设备结构体指针
	
	//判断读位置是否有效
	if(count > 4096 - p) count = 4096 - p;	//要读取的字节大于设备的内存空间
	
	//读数据到用户空间：内核空间->用户空间
	if(copy_to_user(buf,dev_temp->data + p,count)) ret = - EFAULT;
	else {
		r_locate = (r_locate+count)%4096;
		ret = count;
		printk("KERN_INFO: read %d bytes(s) from %ld\n",count,p);
	}
	
	return ret;
}

static ssize_t mydev_write(struct file *filp,const char __user *buf,size_t size,loff_t *f_pos) {
	unsigned long p = w_locate;
	unsigned int count = size;
	int ret = 0;
	struct dev_buff *dev_temp = filp->private_data;	//获得设备结构体指针

	//分析和获取有效的写长度
	if(count > 4096 - p) count = 4096 - p;	//要写入的字节大于设备的内存空间
	
	//从用户空间写入数据
	if(copy_from_user(dev_temp->data + p,buf,count)) ret = - EFAULT;
	else {
		w_locate = (w_locate+count)%4096;
		ret = count;
		printk("KERN_INFO: written %d bytes(s) from %ld\n",count,p);
	}

	return ret;
}
