
#include <stdlib.h>
    
int 
main (int argc, char *argv[])
{
    unsigned char* p = NULL;
    int x=0;

    p = (unsigned char*)malloc(5 * sizeof(unsigned char));

    if ((void*)p > (void*)0xc1000000 ) {
        x = 1;
    }        

    if ((void*)p > (void*)0x07000000 ) {
        x = 2;
    }        

    free(p);  

    return 0;
}
