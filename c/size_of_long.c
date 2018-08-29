
#include <stdio.h>

struct d{
   int x;
   int a[12];
}d;

int
main(int argc, char* argv)
{
    //int a[1];
    int *a;

    struct d  dd;
    struct d* ddp = &dd;

    printf("%u\n", sizeof(ddp->a));

    printf("sizeof(a): %u\n",sizeof(a));
    printf("sizeof(int): %ubits\n",sizeof(int)*8);
    printf("sizeof(long): %ubits\n",sizeof(long)*8);
    printf("sizeof(unsigned long long): %ubits\n",sizeof(unsigned long long)*8);

    return 0;

}
