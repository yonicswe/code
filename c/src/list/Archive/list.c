
#include "list.h"
#include <stdio.h>

struct desc{
	struct list_hook desc_list;
	int data;
};

struct desc*
desc_alloc(int data)
{
	struct desc* d;
	d = (struct desc*)malloc(sizeof(struct desc));
	d->data = data;
	INIT_LIST_HOOK(&(d->desc_list), d);
	return d;
}

struct list_hook* 
desc_list_build(int* data, int data_size)
{
	int index;
	struct list_hook* h;	
	struct desc* d;

	h = (struct list_hook*)malloc(sizeof(struct list_hook));
	INIT_LIST_HOOK(h, NULL);
	
	for (index=0; index<data_size; index++){
		d = desc_alloc(data[index]);	
		list_add_tail(h, &(d->desc_list)); 
	}

	return h;

}


void
desc_list_print(struct list_hook* h)
{
	struct list_hook* l, *t;

	list_for_each_safe(h, l, t){
		printf("%d ", ((struct desc*)l->ent)->data);
	}

	printf("\n");

}

void
desc_list_del(struct list_hook* h)
{
	struct list_hook *l, *t;

	list_for_each_safe(h, l, t){
		printf("%s: %d\n",__func__, ((struct desc*)(l->ent))->data);
		list_del_init(l);

		printf("after deletion\n");
		desc_list_print(h);
	}


}

int
main(int argc, char* argv[])
{

	int data[] = {12,3,4,5,676,4,34,3,1212,90};
	int data_size = sizeof(data)/sizeof(int);
	struct list_hook* h;

	h = desc_list_build(data, data_size);

	desc_list_print(h);

	desc_list_del(h); 

	return 0;
}











	
