
#include <stdlib.h>

#define ALIGN_MASK(bit)	    ((1 << bit) - 1)
#define ALIGN_TO_BIT(x,bit) ((x + ALIGN_MASK(bit)) & ~ALIGN_MASK(bit))

struct a{
    int i;
    volatile char ch;
  //    int y;

};

int my_int_array[20];

int
main(void)
{
	//struct a *ap;
	//int x = (sizeof(*ap));

	unsigned long p = 0x80497ff;
	//void* save_p;

	//int x=sizeof(my_int_array);
	//int y=sizeof(int) * 20;
	//memset(my_int_array, 0x0001, sizeof(int)*20);

	//p = (void*)malloc(sizeof(char) * 30);

	//save_p = p;	
	
	printf("p=%p\n",p);
	
	p = ALIGN_TO_BIT((unsigned long)p,5);

	printf("p=%p\n",p);

	//free(save_p);
	
}
