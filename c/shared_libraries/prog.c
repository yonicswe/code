#include <stdio.h>
#include "ctest.h"

char buffer[BUFFER_SIZE] = {0} ;

int 
main()
{
   ctest1(&buffer, BUFFER_SIZE);

   printf("%s: %s\n", __func__, buffer);

   return 0;
}
