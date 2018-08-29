#include <arpa/inet.h>
#include <endian.h>

/* 
 * network byte order is always big-endian
 * so the usage of ntohl would be the same as 
 * be64toh on a 32bit machine
 *
 */



int main()
{
    char data[] = {0xAB,0x05,0x04,0x07,0x0A,0x0C};

    uint16_t s;
    uint32_t l;
	
    uint64_t before =0;
    uint64_t after =0;

#if (__BYTE_ORDER == __BIG_ENDIAN)
#warning "big endian"
#else    
#warning "little endian"
#endif


    before = 0x1;

    after = be64toh(before);
    after = le64toh(before);
     

    s = *(uint16_t*)&(data[1]);
    l = *(uint32_t*)&(data[1]);

    s = ntohs(*(uint16_t*)&(data[1]));
    l = ntohl(*(uint32_t*)&(data[1]));

    s = ntohs(*(uint16_t*)(data + 1));
    l = ntohl(*(uint32_t*)(data + 1));
}
