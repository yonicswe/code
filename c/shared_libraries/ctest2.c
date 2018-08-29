
#include <stdio.h>
#include "ctest.h"

void 
ctest2(void* buffer, int buffer_size)
{
   printf("%s: Entered\n", __func__);
   snprintf(buffer, BUFFER_SIZE, "nice probe version 4.7 testing snmp");
}
