#include "list.h"
#include <stdio.h>

struct desc{
	struct list_hook desc_list;
	int data;
};


void desc_list_print(struct list_hook* h);

struct desc*
desc_alloc(int data)
{
	struct desc* d;

	d = (struct desc*)malloc(sizeof(struct desc));
	d->data = data;
	INIT_LIST_HOOK(&(d->desc_list), d);
	
	printf("%s: data: %d, p: %p\n",__func__, data, d);
	
	return d;	
}

void
desc_free(struct desc* dp)
{
	list_del_init(&(dp->desc_list));
	printf("%s: %p\n",__func__, dp);
	free(dp);
}

struct list_hook*
desc_list_build(int *data, int data_size)
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
desc_list_free(struct list_hook* h)
{
	struct list_hook* l, *t;

	list_for_each_safe(h, l, t){

		desc_free(l->ent);

		printf("after deletion\n");
		desc_list_print(h);
	}
}

void
desc_list_print(struct list_hook* h)
{

	struct list_hook *l, *t;

	list_for_each_safe(h, l, t){

		printf("%d ",((struct desc*)(l->ent))->data);
	}

	printf("\n");
}






int
main(int argc, char* argv[])
{
	int data[] = {45,2,32,456,4,47,24,1231,13,14,234,2};
	int data_size = sizeof(data)/sizeof(int);
	struct list_hook* h;
	
	h = desc_list_build(data, data_size);

	desc_list_print(h);

	desc_list_free(h);
	
	return 0;
}	
