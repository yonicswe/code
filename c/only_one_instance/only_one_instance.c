#include <sys/file.h>
#include <errno.h>
#include <stdio.h>

int
only_one_instance(void)
{

    int lock_file = open("/var/run/analyzer.lock", O_CREAT | O_RDWR, 0666);
//     int lock_file = open("./analyzer.lock", O_CREAT | O_RDWR, 0666);
    if (lock_file < 0 ) 
        return 0;

    int rc = flock(lock_file, LOCK_EX | LOCK_NB);
    if(rc) {
        if(EWOULDBLOCK == errno)
            return 0; // another instance is running
    }
    else {
        // this is the first instance
        return 1;
    }

}

main()
{
    if (!only_one_instance())
    {
        printf("another process is already running\n");
        return 1;
    }

    while (1)
    {
        sleep(3);
    } 

    return 0;
}
