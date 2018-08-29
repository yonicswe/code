
#include <stdio.h>

int 
main(void)
{
   unsigned long long x=0x8000800028151244ULL;

   printf("x = %llx, x>>40 =%llx\n", x, (x>>40)&0x3fff);
   printf("x = %llx, x<<10 >> 50  =%llx\n", x, (x<<10)>>50);

   return 0;
}
