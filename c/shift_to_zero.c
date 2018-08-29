
#include <stdio.h>

int
main()
{
    int x = 0x5454;

    int y=0;

    y = x<<31; 

    printf("%0x\n",y);


    return 0;
}
