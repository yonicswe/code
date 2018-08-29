
//#include <stdlib.h>

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

int 
main (int argc, char *argv[])
{
    printf("%u is smaller than %u\n",
           MIN(atoi(argv[1]),atoi(argv[2])),
           MAX(atoi(argv[1]),atoi(argv[2])) );
}
