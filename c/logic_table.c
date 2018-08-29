#include <stdio.h>
int
main(void)
{
   int i,j;
   printf("=======================================\n");
   for (i=0; i<2 ; i++)
      for (j=0; j<2 ; j++){
         printf("%d | %d = %d\t"
                "%d & %d = %d\t"
                "%d ^ %d = %d\n" 
                , i, j, i|j
                , i, j, i&j
                , i, j, i^j );
      }
   printf("=======================================\n");


   return 0;
}
