
#include <stdio.h>


struct square { 
   int len;
   int width;

   int area(void);

};

int 
square::area(void)
{
   return ( len * width );
}

#define LEN 6
#define WIDTH 5

int
main(void)
{

   struct square s;
   int a =0;

   s.len = LEN;
   s.width = WIDTH;

   a = s.area();

   printf("area = %d\n", a);
   
   return 0;


}

