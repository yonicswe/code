

#include <stdio.h>

int main(void)
{

   int x1 = 10;
   int x2 = 20;
   int x3 = 5;
   int y;

   y = ( ( x1 > x2 ) ? (x3++, 0) :1 );  

   printf("x3: %d, y: %d\n", x3, y);

   x1 |= 0x0001;

   return 0;
}
