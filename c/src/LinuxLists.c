#include <string.h>
#include "list.h"

struct list_heads{
	struct list_head name_list_item; 
    struct list_head num_list_item;
};

struct name_item{
	struct list_head name_list_item;
	char name[100]; 
};

struct number_item {
    struct list_head num_list_item;
    unsigned long number;
};

struct list_heads my_lists;

char *names[] = {"yoni", "dvora","michal","david"};
int names_size = 4;

unsigned long numbers[] = {0x43, 0x12, 0x37, 0x8, 0x2, 0x100 , 0x20, 0x4, 0x80, 0x87};
unsigned long numbers_size = sizeof(numbers)/sizeof(unsigned long);

void
add_2_list(struct list_head* head_list_ptr, struct number_item* new_number_item_p)
{
	struct number_item* number_item_p;
    struct list_head* list_ptr;

    list_for_each(list_ptr, head_list_ptr){
        number_item_p = list_entry(list_ptr, struct number_item, num_list_item);
        if ( new_number_item_p->number > number_item_p->number )
            continue;
        break;
    }

    list_add_tail(&new_number_item_p->num_list_item, list_ptr);
}

int
main(void)
{       
	unsigned long       i;
	struct number_item* new_number_item_p;
	struct name_item*	name_tmp_item;
    struct list_head*   list_ptr;
    char*               ch_ptr;

	
	INIT_LIST_HEAD(&my_lists.num_list_item);

	//====================================
	// fill the name list 
	//====================================

#if kaka
	for (i=0; i<names_size; i++){
		name_tmp_item = (struct name_item*)malloc(sizeof(struct name_item));
		strcpy(name_tmp_item->name, names[i]);
		list_add_tail(&name_tmp_item->name_list_item, &my_lists.name_list_item);
	}
#endif

    //sort. 
    for (i=0; i<numbers_size; i++) {

        new_number_item_p = (struct number_item*)malloc(sizeof(struct number_item));
        new_number_item_p->number = numbers[i];
        INIT_LIST_HEAD(&new_number_item_p->num_list_item);

        add_2_list(&my_lists.num_list_item, new_number_item_p);

    }

    //print after 
    list_for_each(list_ptr, &my_lists.num_list_item){
        printf("%lx.\n",(list_entry(list_ptr, struct number_item, num_list_item))->number);
    }

#if kaka
    printf("\nand backwards:\n");

    list_for_each_prev(list_ptr, &my_lists.name_list_item){
        printf("%s.\n",(list_entry(list_ptr,struct name_item ,name_list_item))->name);
    }
#endif
	
}

