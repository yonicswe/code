#include <stdlib.h>
//#include <string.h>

int a[5] = {1,2,3,4,5};
int b[5] = {21,22,23,24,25};


int 
main (int argc, char *argv[])
{

    char tmp_buf[100] = {0};
    char buf[1000]={0};
    int i;
    int curr;


    for (curr=0,i=0; i<5; i++) {
        sprintf(tmp_buf, "(%d, %d)->",a[i],b[i]);
        strcpy (&buf[curr], tmp_buf);
        curr += strlen(tmp_buf);
        tmp_buf[0]='\n';
    }

    printf("%s\n",buf);

    return 0;
}
