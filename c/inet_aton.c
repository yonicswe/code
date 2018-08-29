#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>


int
main(int argc, char* argv[]) 
{
    struct in_addr s;        

    char p[50] = {'1' ,'2' ,'7' ,'.' ,'0' ,'.' ,'0' ,'.' ,'1', '\0', '2'};

//     inet_aton(argv[1], &s);
    inet_aton(p, &s);

//     printf(

    return 0;

}
