//#include <stdlib.h>

#define ISER_DEBUG_LOG(fmt,arg...)  printf("printing" fmt , ##arg)


char yoni[] = "yonicohen"; 

int main (int argc, char *argv[])
{
    ISER_DEBUG_LOG(yoni);

    return 0;
}
