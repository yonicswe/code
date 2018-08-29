#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib1.h"

int 
main(void) 
{
   int f=0;

   while (1) {

      if ( f==0 ) {
         f =1;
         printf("%s: pid: %d\n", __FILE__, getpid());

         printf("%s: a[0]: %d, a[1]: %d\n", __FILE__, 
             get_data_from_proc2(0),  
             get_data_from_proc2(1));  
      }
      
   }

   return 0;
   
}
