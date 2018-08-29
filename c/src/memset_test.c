#include <stdlib.h>
#include <string.h>
          
void 
print_origin(void* func_address, 
             int line_number, 
             char* identifier)
{
    char buffer[3];

    //printf("Got iden %s len=%d\n",identifier,strlen(identifier) );

    //strncpy(buffer, identifier, 3);
    sprintf(buffer, identifier);

    if (strlen(identifier) >= 3 ) {
        buffer[2] = 0;
    }

    printf("func_address=%p, line_number=%d, identifier=%s\n",
           func_address, 
           line_number,
           buffer);
}

void 
f1(void){
    print_origin(&f1,__LINE__,"AB");
}

void 
f2(void){
    print_origin(&f2,__LINE__,"DE1234");
}

void 
f3(void){
    print_origin(&f3,__LINE__,"GHI88");
}


int 
main (int argc, char *argv[])
{
    char a[100];
    int size_a;

    size_a = sizeof(a);

    memset(a,0,size_a);

    f1();
    f2();
    f3();

    return 0;

}
