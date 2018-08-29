#include <stdio.h>
#include <linux/list.h>

typedef struct {
	char name;
	int number;
}worker;

struct name{
	char first;
	char last;
}name;

struct person{
	struct name person_name;
	int preson_id;
};

typedef struct{
	//struct person me;	
	//struct list_head lll;
	char data1;
	long data2;
	long data3;
	long data4;
}my_item;

int main(void)
{
#if kaka
	worker worker_list[5]={{0x41},{0x42,2},{0x43,3},{0x44,4},{0x45,5}};
	int i;

	for (i=0; i<5; i++){
		printf("%c - %d\n",worker_list[i].name,worker_list[i].number);
	}

#endif
	
	// look at address 0 with glasses of my_item.
	// and show the address where each field resides
	// this of-course will give the offset of each fiels 
	// from the start of the structure.
	printf("data1=%x\ndata2=%x\ndata3=%x\ndata4=%x"	,&((my_item*)0)->data1
													,&((my_item*)0)->data2
													,&((my_item*)0)->data3
													,&((my_item*)0)->data4);

	return (0);
}
