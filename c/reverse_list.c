#include <stdlib.h>
#include <stdio.h>

typedef struct list_t {
   
   int d;
   struct list_t* next;
      
} list_t;


list_t* 
new_list_item(int d)
{
   list_t* l;

   l = malloc(sizeof(list_t));
   l->d = d; 
   l->next = NULL;
   return l;
}

void
build_list(list_t** head, int* data_arr, int data_arr_size)
{
   int index;
   list_t* n;
   list_t* h;

   h = NULL;

   for (index =0 ; index < data_arr_size; index++)
   {
      n = new_list_item(data_arr[index]);

      if (h == NULL)
      {
         // 1st item
         h = n;
      }
      else
      {
         // general item
         n->next = h;
         h = n; 
      } 
   }

   *head = h;

}

void 
free_list(list_t** head)
{
   list_t* h;
   list_t* c;

   h = *head;
   while (h) 
   {
      c=h->next;
      printf("free %d\n", h->d);
      free(h); 
      h=c;   
   } 

   *head = NULL; 
}

void
print_list(list_t* head)
{
   list_t* h;
   
   h = head; 

   if (NULL == h) {
      printf("list empty\n");
      return;
   }

   while (h)
   {
      printf("%d, ", h->d);
      h =h->next;

   }

   printf("\n");

}

//   p      c      n
//  [ ] -> [ ] -> [ ] 

void
reverse_list(list_t** head)
{

   list_t* p;
   list_t* c;
   list_t* n;

   p = NULL;
   c = *head;

   while (c)
   {
      n = c->next;

      c->next = p; 
      
      p = c;
   
      c = n; 
      
   }

   *head = p;

}


//int data_arr[] = {1,2,3,4,5,6,7,8,9,10};
int data_arr[] = {1,2,3};
int data_arr_size=sizeof(data_arr)/sizeof(int);

int
main(void)
{
   list_t* l1;

   // build the linked list.
   build_list(&l1,data_arr, data_arr_size); 
   
   
   // print the linked list.
   print_list(l1);

   // reverse the list.
   reverse_list(&l1);
   
   // print the linked list.
   print_list(l1);

   // free the list.
   free_list(&l1);
   
   // print the linked list.
   print_list(l1);
   return 0;
}
