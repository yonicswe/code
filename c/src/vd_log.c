#include <stdio.h>

#define VDLOG_PANIC         0
#define VDLOG_ERROR         1
#define VDLOG_WARNING       2
#define VDLOG_INFO          3
#define VDLOG_DEBUG         4
#define VDLOG_FUNC          5

static char* 
vdlog_levels[] = {
    "PANIC  ",
    "ERROR  ",
    "WARNING",
    "INFO   ",
    "DEBUG  ",
    "FUNC   "
};

#define VD_LOG(__level, __fmt, __args...) \
do { \
    printf("%lu %s : iTarget : " __fmt , \
          jiffies, vdlog_levels[(__level)] , ##__args); \
}while(0)

#define yoyo(fmt,args...) printf(fmt,args)

int 
main (int argc, char *argv[])
{

    VD_LOG(VDLOG_DEBUG,"%s() Hello\n",__func__);

	yoyo("%d %d %d %d", 1,"2",3,4);

    return 0;
    
}
