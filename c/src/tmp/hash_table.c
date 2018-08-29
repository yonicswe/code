#include <stdlib.h>
#include "hash.h"
	
struct desc{
	int data;
	struct list_head desc_list;
};


struct desc* 
find_hash_desc(int data, struct ht* htp)
{
	int i;
	int j;
	struct list_head* h;
	struct list_head* tmp;
	struct list_head* l;
	struct desc* d;

	i = hash_func(data);
	h = &(htp->bucket[i]);
	
	list_for_each_safe(h, l, tmp){
		d = l->node;
		if (d->data == data ) 
			return d;
	}

	return NULL; 
}

struct desc*
alloc_desc(int data)
{
	struct desc *desc_tmp;
	desc_tmp = malloc(sizeof(struct desc));	
	if (desc_tmp == NULL ) 
		return NULL;

	LIST_HEAD_INIT(&desc_tmp->desc_list, desc_tmp);
	desc_tmp->data = data;
	
	printf("%s: alloc desc: 0x%p, data: %d\n",__func__, desc_tmp, desc_tmp->data);
	
	return desc_tmp; 
}

void
free_desc(struct desc* d)
{
	printf("%s: desc: 0x%p data: %d\n",__func__, d, d->data);
	memset(d,0,sizeof(d));
	free(d); 
}

int
build_desc_list(int* data, int data_size, struct list_head* h)
{
	int i;
	struct desc* desc_tmp;
	struct list_head *l;
	
	if (h == NULL) 
		return 1;

	LIST_HEAD_INIT(h, NULL);
	
	for (i=0; i<data_size; i++){
		desc_tmp = alloc_desc(data[i]);	

		if ( desc_tmp == NULL ){
			printf("failed to allocate desc\n");
			return 1;
		}

		list_add_tail(h, &(desc_tmp->desc_list));
	}

	return 0;
	
}

void
free_desc_list(struct list_head* hp)
{
	struct list_head* l,*t,*h=hp;
	struct desc* d;
	
	list_for_each_safe(h, l, t){
		//d = list_entry(l, struct desc, desc_list);
		d = l->node;
		free_desc(d);
	} 
}


void
print_desc_list(struct list_head* h)
{
	struct list_head *l,*t;
	struct desc* d;
	
	printf("\n");
	list_for_each_safe(h, l, t){
		//d = list_entry(l, struct desc, desc_list);
		d = l->node;
		printf("%d ",d->data);
	} 
	printf("\n"); 
}

int
main(void)
{
	struct list_head lst1;
	struct desc* desc_tmp;
	int ret;
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
	int data_size = sizeof(data)/sizeof(int);
	
	ret = build_desc_list(data, data_size, &lst1);
	if (ret != 0 ) 
		goto failed_alloc;

	print_desc_list(&lst1);

	free_desc_list(&lst1);

	return 0;

failed_alloc:
	free_desc_list(&lst1);
	return 1;

}
