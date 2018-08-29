#include <stdlib.h>
char* 
my_strtok(char* str, char* token);

char* 
my_strsep(char** str, char* token);
  
#if kernel_2_6
#define STRTOK(str, token) \
            my_strtok(str, token)
#else
#define STRTOK(str, token) \
            my_strsep(&str, token)
#endif


char* 
my_strtok(char* str, char* token)
{
    printf("%s() Got str=\"%s\" and token=\"%s\"\n",__func__, str,token);
    return NULL;
}

char* 
my_strsep(char** str, char* token)
{               

    printf("%s() Got str=\"%s\" and token=\"%s\"\n",__func__, *str,token);
    return NULL;
}

////////////////////////////////////////////////////////
int
main (int argc, char *argv[])
{

    char* my_name = "yoni cohen";         

    STRTOK(my_name, "dd");

    return 0;
}
