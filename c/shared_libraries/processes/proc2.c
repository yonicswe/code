#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int a[10] = {1,2,3,4,5,6,7,8,9,10};


int get_a(int i)
{
   return a[i];
}


int 
main(void) 
{
   int f=0;

   while (1) {

      if ( f==0 ) {
         f =1;
         printf("%s: pid: %d\n", __FILE__, getpid());
      }
      
   }

   return 0;
   
}
