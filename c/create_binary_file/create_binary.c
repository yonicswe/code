#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int
main(void)
{
   int fd;
   int i;
   char b=0xa5;

   fd = open("f1.binary", O_RDWR|O_CREAT);

   for ( i=0 ; i<1024 ; i++)
      write(fd,&b,1);

   close(fd);

   return 0;

}
