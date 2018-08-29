#include <stdlib.h>
                                
#define SIZE 5

              
struct item{
    int x;
    int y;
};

int 
main (int argc, char *argv[])
{

    struct item* item_arr[SIZE];
    struct item* item_p;
    int index;

    for (index=0; index<SIZE; index++) {
        item_arr[index] = malloc(sizeof(struct item));
        item_arr[index]->x = index;
        item_arr[index]->y = index;
    }   

    item_p=(struct item*)item_arr;
    for (index=0; index<SIZE; index++, item_p++) {
        printf("x=%d, y=%d\n",item_p->x, item_p->y);
    }

    for (index=0; index<SIZE; index++) {
        free(item_arr[index]);
    }   

    return 0;
}
