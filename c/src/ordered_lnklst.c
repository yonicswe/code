#include <stdlib.h>


typedef struct node node;
struct node{
    int x;
    node* next;
};

typedef struct node_list;
struct node_list{
    node* head;
};


void 
print_list(node_list* list_p)
{

    node* node_p = list_p->head;
    while (node_p!= NULL) {
        printf("(%d)->",node_p->x);
        node_p = node_p->next;
    }

}

void
add_to_list(node_list* list_p, node* new_node)
{
    node* next_node_p = list_p->head;
    node* prev_node_p = NULL;

    if (next_node_p == NULL) {
        // 1st addtion
        list_p->head = new_node;
        return;
    }

    while (next_node_p != NULL) {

    }

}

void
free_list(node_list* list_p)
{
    node* next_node_p = list_p->head;
    node* prev_node_p  = NULL;

    while (next_node_p != NULL) {

        prev_node_p = next_node_p;
        next_node_p = next_node_p->next;
        free (prev_node_p);
    }                      
}

void
init_list(node_list* list_p)
{
    list_p->head = NULL;

}

/////////////////////////////////////////////////////////
int 
main (int argc, char *argv[])
{
    int data[] = {20,6,17,34,1,13};
    int data_size = sizeof(data) / sizeof(int) ;
    int index;
    node_list my_list;

    init_list(&my_list);

    for (index =0 ; index < data_size; index++ ) {
        node* new_node  = (node*)malloc(sizeof(node));
        new_node->x = data[index];
        new_node->next = NULL;

        add_to_list(&my_list, new_node);
    }

    print_list(&my_list);

    free_list(&my_list);

    return 0;
}
