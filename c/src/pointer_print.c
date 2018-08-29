
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
    }


    // set values.
    for (i=0 ; i<10 ; i++) {
        point_arr[i]->x = i;
        point_arr[i]->y = i * 2;
    }


    // free
    for (i=0 ; i<10 ; i++) {
        point_arr[i] = (struct point*) malloc(sizeof(struct point));
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

