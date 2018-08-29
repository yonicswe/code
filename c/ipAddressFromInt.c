
#include <arpa/inet.h>
#include <stdio.h>

void print_ip(int ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;   
    printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);        
}

main(int argc, char* argv[]) 
{

    uint32_t ip = atoi(argv[1]);//2110443574;
    struct in_addr ip_addr;
    ip_addr.s_addr = ip;
    printf("The IP address is %s\n", inet_ntoa(ip_addr));
}

