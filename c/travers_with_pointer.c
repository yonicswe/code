
#include <stdio.h>
#include <stdlib.h>

// 
// this code shows that when traversing memory with a pointer 
// the pointer is incremented by the number of bytes correspoinding to the 
// size of the type of the pointer and not by 4 bytes which is the standard 
// pointer size 
// 


struct bucket{
   int x1;
   int x2;
   int x3;
   int x4;
   int x5; 
};

int
main(void)
{
   char *arr=NULL;
   struct bucket *p;
   int count;
   int i;

   count = 1024 / sizeof(struct bucket);

   arr = malloc(1024);

   p = (struct bucket*)arr;
   for (i=0 ; i < count ; i++, p++)
   {
      printf("i: %d, p: %p\n", i, p); 

   }

   free(arr);

   return 0;
}
