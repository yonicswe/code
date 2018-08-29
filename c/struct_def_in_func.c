
#include<stdlib.h>
#include<string.h>

enum {
   TRUE  =0,
   FALSE =1
};

void
f1(void)
{
   struct _flow_state{
      char desc_alloced;
      char list_init;
      char queue_init;
   } flow_state; 


   memset(&flow_state, 0, sizeof(struct _flow_state));

   flow_state.desc_alloced = 1;



}

int
main(void)
{

   f1();

   return 0;
}
