
#define MODULE
#define __KERNEL__
#include <linux/module.h>
#include <linux/uio.h>

static int control_major;
static const char *control_name = "hello";

enum yoni_cmds{
	HELLO_YONI,
	GOODBYE_YONI
};


ctl_ioctl(struct inode *inode,
	  struct file *file, unsigned int cmd, unsigned long arg)
{

	switch (cmd) {
	case HELLO_YONI:
			printk("hello from driver\n");
	case GOODBYE_YONI:
			printk("goodbye from driver\n");
			return(iscsi_shutdown());
	}

	printk("iSCSI: Requested ioctl not found\n");
	return -1;
}

static struct file_operations control_fops = {
      .owner = THIS_MODULE,
      .ioctl = ctl_ioctl,   /* ioctl */
};
int init_module () {
	printk ("Hello World\n");
   
   control_major = register_chrdev(0, control_name, &control_fops);
    if (control_major < 0) {
        printk("iSCSI: failed to register the control device\n");
        ret = control_major;
        return (1);
    }
    printk("iSCSI: control device major number %d\n", control_major);
	return (0);
}

void cleanup_module () {
	printk ("Goodbye World\n");
	unregister_chrdev(control_major, control_name);
	}
