

#include <stdio.h>

char* 
get_str(void)
{
   return "yoni is the greatest";
}

int
main(void)
{
   char* p;

   p = get_str();

   printf("%s", p);

   return 0;
}
