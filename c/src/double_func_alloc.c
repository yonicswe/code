#include <stdlib.h>

struct a{
    int x;
    int y;
};


    
void second_alloc_func(struct a **p)
{
    *p = (struct a*)malloc(sizeof(int) * 10);
}


void first_alloc_func(struct a **p)
{
    second_alloc_func(p);

    (*p)->x = 2;
    (*p)->y = 32;
}

    
int main (int argc, char *argv[])
{
    struct a *a1;

    first_alloc_func(&a1);

    free(a1);

    return 0;
}
