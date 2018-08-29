
#include <string.h>

#define b1_size 10
#define b2_size 10


struct a{


    int size;
    char b1[b1_size];
    char b2[b2_size];
};


void
fill_b(char *b)
{
    struct a* a1 = (struct a*)b;

    a1->size = 2;
    memset(a1->b1, 0xa, b1_size);
    memset(a1->b2, 0xb, b2_size);
    
}




int
main()
{
    char b[sizeof(struct a)] = {0}; 

    fill_b((char*)&b);


    return 0;
}
