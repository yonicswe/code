#include <stdlib.h>


void
vPrintConnRunList(int *numbers, int size)
{
    char buffer[1024]={0};
    int len = 0;
    int index;


    for (index = 0; index < size ; index ++ ) {

        sprintf((void*)(buffer+len),"(%4lu),",numbers[index]);

        len +=7;                         
    }

    printf("%s() %s\n",__func__,buffer);
}   

int 
main (int argc, char *argv[])
{

/*    int numbers[] = {456, 345, 12, 123, 56, 32, 765, 31};
    int size = 8;
*/
    int numbers[] = {456};
    int size = 1;

    vPrintConnRunList(numbers,size);

    return 0;
}
