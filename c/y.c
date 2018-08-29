#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


int
main(void)
{
   int x;
   
   x = strtol("y", NULL, 10);
   printf("x = %lu, errno: %d\n", x, errno);

   return 0;

}
