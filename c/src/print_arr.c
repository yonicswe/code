#include <stdio.h>
//#include <stdlib.h>

char byte_arr[] = {
	0x12, 0x13, 0x54, 0x36, 0x2, 0x12, 0x13, 0x54, 0x36, 0x2,
	0x12, 0x13, 0x54, 0x36, 0x2, 0x12, 0x13, 0x54, 0x36, 0x2
	};
int byte_arr_sz = sizeof(byte_arr);


int 
main (int argc, char *argv[])
{
    char ascii_arr[100] = {0};
	int n;
    int index;

    for (index=0, n=0 ; index < byte_arr_sz ; index ++) {
        n += sprintf(ascii_arr + n, "%02x%c" , byte_arr[index], (index%8 == 7)?'\n':' ');
    }            

    printf("buffer=\n%s\n",ascii_arr);

    return 0;

}
