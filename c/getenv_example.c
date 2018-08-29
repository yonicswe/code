#include <string.h>
#include <errno.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
    char* e; 

    e = getenv(argv[1]);
    printf("%s = %s\n", argv[1], e);
    return 0;    
}
