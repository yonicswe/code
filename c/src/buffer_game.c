#include <stdio.h>

char received[] = {'a','b','c','\0',
                   'd','e','f','g','\0',
                   'h','i','j','k','l','\0'};
int received_size = sizeof(received)/sizeof(char);

#if kaka
void
fill_buffer(char *buffer)
{
    int len,i=0,j=0;

    printf("%s(%u) entered\n",__func__,__line__);

    while (j<received_size) {
        len = strlen( (char*)((int)(received)+j) );
        sprintf( (char*)((int)buffer+i),"%s",(char*)((int)(received)+j) );
        i+= len;
        j+= len+1;
    }

}
#endif

void
fill_buffer (char *buffer)
{
    int i,j;
    for (i=0,j=0; i<received_size; i++) {
        if (received[i] != '\0') {
           buffer[j++] = received[i]; 
        }
    }
}

int
main(void)
{
    char buffer[100];

    fill_buffer(buffer);
    printf("%s\n",buffer); 
}
