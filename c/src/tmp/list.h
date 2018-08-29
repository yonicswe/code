/*
	this linked list is very similar to the kernel's but eliminates the use of list_entry macro. 
	no need for it if the list_head struct can point to its owner upon allocation.
                    
		+->+-------------+   +->+-------------+  +->+-------------+   +->+-------------+
		|  |  list_hook  |   |  | list_hook   |  |  | list_hook   |   |  | list_hook   |  
		|  | +---------+ |   |  | +---------+ |  |  | +---------+ |   |  | +---------+ |
		+-------(node) | |   +-------(node) | |  +-------(node) | |   +------(node)  | |
		   | |         | |      | |         | |     | |         | |      | |         | |
		   | +----+----+ |      | +----+----+ |     | +----+----+ |      | +----+----+ |
		   | |    |    | |      | |    |    | |     | |    |    | |      | |    |    | |   
		   | |    |next---------->|    |next--------->|    |next---------->|    |next----->1st node
		   | |    |    | |      | |    |    | |     | |    |    | |      | |    |    | |  
       last<----------prev|    |<----------prev|    |<---------prev|    |<--------- prev|    | |   
       node        | +----+----+ |      | +----+----+ |     | +----+----+ |      | +----+----+ |
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   |             |      |             |     |             |      |             |  
		   +-------------+      +-------------+     +-------------+      +-------------+

	
*/

#ifndef _LIST_H_
#define _LIST_H_


struct list_head{
	struct list_head* prev;
	struct list_head* next;
	void* node; //points to the actual node.
};

/*
#define list_entry(addr, type, property) \
		(type*)((unsigned long)addr -(unsigned long)&( ( (type*)(0))->property) );
*/		
#define LIST_HEAD_INIT(l, n) \
		do { \
			(((l)->next) = ((l)->prev) = (l)); \
			(((l)->node) = (n)); \
		}while(0);

#define list_add_tail(h, l) \
	do { \
		((l)->next) = (h); \
		((l)->prev) = ((h)->prev); \
		((h)->prev->next) = (l); \
		((h)->prev) = (l); \
	}while(0)

#define list_del_init(l) \
	do {\
		(l)->prev->next = (l)->next; \
		(l)->next->prev = (l)->prev; \
		(l)->prev = NULL; \
		(l)->next = (l)->prev; \
	}while(0)

#define list_empty(h)\
	(h->next == h)?1:0

#define list_for_each_safe(h, l, t) \
	for (l = (h)->next, t = l ;  l != h; t=l, l=(l)->next)

#endif
