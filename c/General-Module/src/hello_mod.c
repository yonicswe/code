
#ifndef MODULE
#define MODULE
#endif

#ifndef __KERNEL__
#define __KERNEL__
#endif

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

int 
init_module(void) 
{
	char* b;

	printk("\nHello, world\n");

	b = kmalloc(100 * sizeof(char), GFP_KERNEL);

	printk("alloced 100 bytes: 0x%p\n",b);


	printk("Freeing 0x%p\n",b+10);
	
	kfree(b-10);


	return 0;
}

void 
cleanup_module(void)
{
	printk("\nGoodbye, world\n");

}
