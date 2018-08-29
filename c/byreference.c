

#include <stdio.h>

int
main(void)
{

   int x1 =2;

   int* x;

   x = &x1;


   printf("*x = %d, x = %p, &x = %p",*x, x, &x );

   return 0;
}
