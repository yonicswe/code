#include <string.h>

struct header{
    unsigned char t0:1; //lsb
    unsigned char t1:1;
    unsigned char t2:1;
    unsigned char t3:1;
    unsigned char t4:1;
    unsigned char t5:1;
    unsigned char t6:1;
    unsigned char t7:1; //msb

    unsigned long t8_39:31;
    unsigned long t40:1;
};

int main (int argc, char *argv[])
{
    struct header h;

    memset (&h, 0, sizeof(h));

    h.t1 = (unsigned int)0x2;

    h.t1 = (unsigned int)0x3;

    return 0;
}
