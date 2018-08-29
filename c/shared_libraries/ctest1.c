#include <stdio.h>
#include "ctest.h"



void ctest1(void* buffer, int buffer_size)
{

   printf("%s: Entered\n", __func__);
   
   ctest2(buffer, BUFFER_SIZE); 
   
   printf("%s: \"%s\"\n", __func__, (char*)buffer);
}
