#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>



int main(int argc, char *argv[]) {
    struct ifreq ifr;
    int sock, j, k;
    char *p, addr[32], mask[32], mac[32];


    if (argc<2) {
        fprintf(stderr,"missing argument, example: eth0\n");
        return 1;
    }


    sock=socket(PF_INET, SOCK_STREAM, 0);
    if (-1==sock) {
        perror("socket() ");
        return 1;
    }


    strncpy(ifr.ifr_name,argv[1],sizeof(ifr.ifr_name)-1);
    ifr.ifr_name[sizeof(ifr.ifr_name)-1]='\0';


    if (-1==ioctl(sock, SIOCGIFADDR, &ifr)) {
        perror("ioctl(SIOCGIFADDR) ");
        return 1;
    }
    p=inet_ntoa(((struct sockaddr_in *)(&ifr.ifr_addr))->sin_addr);
    strncpy(addr,p,sizeof(addr)-1);
    addr[sizeof(addr)-1]='\0';


    if (-1==ioctl(sock, SIOCGIFNETMASK, &ifr)) {
        perror("ioctl(SIOCGIFNETMASK) ");
        return 1;
    }
    p=inet_ntoa(((struct sockaddr_in *)(&ifr.ifr_netmask))->sin_addr);
    strncpy(mask,p,sizeof(mask)-1);
    mask[sizeof(mask)-1]='\0';


    if (-1==ioctl(sock, SIOCGIFHWADDR, &ifr)) {
        perror("ioctl(SIOCGIFHWADDR) ");
        return 1;
    }
    for (j=0, k=0; j<6; j++) {
        k+=snprintf(mac+k, sizeof(mac)-k-1, j ? ":%02X" : "%02X",
            (int)(unsigned int)(unsigned char)ifr.ifr_hwaddr.sa_data[j]);
    }
    mac[sizeof(mac)-1]='\0';


    printf("\n");
    printf("name:    %s\n",ifr.ifr_name);
    printf("address: %s\n",addr);
    printf("netmask: %s\n",mask);
    printf("macaddr: %s\n",mac);
    printf("\n");


    close(sock);
    return 0;
}
