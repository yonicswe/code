#include <stdio.h>
#include <stdlib.h>

struct item{
	int data1;
	int data2;
};

void
array_initer(struct item** item_arr, int* item_arr_len)
{
	int indx;
	
	*item_arr_len = 3;
	*item_arr = (struct item*)malloc(sizeof(struct item) * (*item_arr_len) );

	for (indx =0 ; indx < (*item_arr_len) ; indx++){
		(*item_arr)[indx].data1 = indx; 
		(*item_arr)[indx].data2 = indx *2; 
	}
	
}

void
array_freer(struct item *free_this_item)
{
	free(free_this_item);
}

int 
main(int argc, char* argv[])
{
	struct item* item_arr;
	int item_arr_len;
	int indx;

	void* void_ptr;

	array_initer(&item_arr, &item_arr_len);

	for (indx = 0; indx < item_arr_len; indx++){
		printf("item[%d].data1=%d, item[%d].data2=%d\n",indx,item_arr[indx].data1,
														indx,item_arr[indx].data2);
	}

	array_freer(item_arr);
	
	return 0;
}
