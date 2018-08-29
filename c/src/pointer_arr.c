
#include <stdio.h>

struct point{
    int x;
    int y;
}point;


struct point** point_arr;

int 
main(void)
{
//	char* p;
    int i;

    point_arr = (struct point**) malloc(10 * sizeof(struct point*));

    // alloc
    for (i=0 ; i<10 ; i++) {
        point_arr[i] = (struct point*) malloc(sizeof(struct point));
        printf("Alloced point_arr[%d] = 0x%p\n",i, point_arr[i]);
    }


    // set values.
    for (i=0 ; i<10 ; i++) {
        point_arr[i]->x = i;
        point_arr[i]->y = i * 2;
    }

    // print array 
    for (i=0 ; i<10 ; i++) {
        printf("point_arr[%d]->x=%d, point_arr[%d]->y=%d\n",
               i,point_arr[i]->x, i, point_arr[i]->y);
    }


    // free
    for (i=0 ; i<10 ; i++) {
        printf("Freed point_arr[%d] = 0x%p\n",i, point_arr[i]);
        free(point_arr[i]);
    }

    return 0;

//     p = NULL;
//
//     printf("p=%p",p);
//
//     p = (char*)malloc(10);
//     printf("p=%p",p);
//     free(p);

	
}

