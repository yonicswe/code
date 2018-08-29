#include <stdlib.h>
#include <string.h>

typedef struct node_t{
    int data;
    struct node_t* next;
}node_t;

typedef struct {
    node_t* head;
    node_t* tail;
    int size;
}list_t;

//////////////////////////////////////////////////////////////

void
add_node(list_t* list_p, node_t* new_node_p)
{   
    node_t* node_p = list_p->head;
    node_t* prev_node_p = NULL;

    // 1st item 
    if (node_p == NULL) {
        list_p->head = new_node_p;
        list_p->tail = new_node_p;
        list_p->size++;
        return;
    }

    // try adding to the end 
    if (new_node_p->data >= list_p->tail->data) {
        list_p->tail->next = new_node_p;
        list_p->tail = new_node_p;
        list_p->size++;
        return;
    }

    // try finding the right place from the start
    while (node_p != NULL) {

        if (new_node_p->data < node_p->data ) {

            if (prev_node_p == NULL) {
                new_node_p->next = list_p->head;
                list_p->head = new_node_p;
            }
            else {
                prev_node_p->next = new_node_p;
                new_node_p->next = node_p;
            }

            list_p->size++;
            return;
        }

        prev_node_p = node_p;
        node_p = node_p->next;
    }       
}

void
print_list(list_t* list_p)
{
    char ch_buf[1024]={0};
    char seperator[3]={'-','>',0};
    node_t* node_p = list_p->head;
    int len = 0;
    int count =0;

    while (node_p != NULL && len<1024) {
        count++;
        
        sprintf(&ch_buf[len], "(%d)%s",node_p->data,(count<list_p->size)?seperator:"\n" );
        len = strlen(ch_buf);
        node_p = node_p->next;
    }

    printf("size=%d, %s",list_p->size,ch_buf);

}

void 
init_node(node_t** new_node_p,int data)
{
    *new_node_p = (node_t*)malloc(sizeof(node_t));
    (*new_node_p)->next = NULL;
    (*new_node_p)->data = data;
}

void
free_list(list_t* list_p)
{
    node_t* node_p = list_p->head;
    node_t* del_node_p = NULL;

    while (node_p) {
        del_node_p = node_p;
        node_p = node_p->next;
        free (del_node_p);
    }
}

void
init_list(list_t* list_p)
{
    list_p->head = NULL;
    list_p->tail = NULL;
    list_p->size =0 ;
}

//////////////////////////////////////////////////////
int main (int argc, char *argv[])
{
   list_t ll1;
   node_t* node_p;
   int index;
   int data_arr[] = {30,50,24,12,45,8,100,102,56,123};
   int data_arr_size = sizeof(data_arr)/sizeof(int);

   init_list(&ll1);

   for (index=0; index < data_arr_size; index++){
       init_node(&node_p, data_arr[index]);
       add_node(&ll1, node_p);
   }

   print_list(&ll1);

   free_list(&ll1);
}
