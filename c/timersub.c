#include <sys/time.h>

int
sub_times(const struct timeval *a,
          const struct timeval *b,
          struct timeval *result)
{

    timersub(a,b,result);

    return timercmp(a,b,<);

}

int
main(void)
{
    struct timeval a;
    struct timeval b;
    struct timeval c;
    int r;

    a.tv_sec = 30;
    a.tv_usec = 0;

    b.tv_sec = 20;
    b.tv_usec = 1;

    r = sub_times(&b,&a,&c);

    return r;

}
