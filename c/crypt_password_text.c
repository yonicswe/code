
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>

int 
main(int argc, char* argv[]) 
{
  
   char *pass=argv[1];
   char *crypted_pass;
   
   crypted_pass = crypt(pass, "aa");  


    printf("\n%s\n", crypted_pass);
    //printf("%s", pass);


   return 0;

}
