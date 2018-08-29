#include <stdlib.h>


void*
zallocn(int sz) 
{
   int s;
   unsigned long p;
   unsigned long rp;

   // adjust the size 
   s = sz + sizeof(unsigned long) + ((1<<5)-1);

   p = (unsigned long)malloc(s);

   rp = ( p + sizeof(long) + ((1<<5)-1)) & (~0)<<5;
   
   *(rp - sizeof(long)) = p;

   return (void*)rp;
}


void
freen(void* p)
{
   free(*(void*)(p-sizeof(long)));
}

int
main




