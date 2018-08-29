#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

//int gettimeofday(struct timeval *tv, struct timezone *tz);

//int settimeofday(const struct timeval *tv , const struct timezone *tz);
/*
DESCRIPTION
       The functions gettimeofday and settimeofday can get and set the time as well as a timezone.  The tv argument is a timeval struct, as
       specified  in <sys/time.h>:
 
       struct timeval {
               time_t         tv_sec;    // seconds 
               suseconds_t    tv_usec;  // microseconds 
       };
 
       and gives the number of seconds and microseconds since the Epoch (see time(2)).  The tz argument is a timezone :
 
       struct timezone {
               int  tz_minuteswest; // minutes W of Greenwich 
               int  tz_dsttime;     // type of dst correction 
       };
*/

#include <stdio.h>

int 
main (int argc, char *argv[])
{
    struct timeval  tv1;
    struct timeval  tv2;
    struct timezone tz2;

    tv1.tv_sec = atoll(argv[1]);

    gettimeofday(&tv2, &tz2);
    tv2.tv_sec -= tv1.tv_sec;

    printf("%s\n",ctime(&tv2.tv_sec));

    return 0;

}
