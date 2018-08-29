#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
	struct timeval t1;
	struct timeval t2;
	struct timeval res;

	gettimeofday(&t1, NULL);
	// sleep(2);
	usleep(2.123434 * 1000000);
	gettimeofday(&t2, NULL);
	timersub(&t2, &t1, &res);

	printf("t1 %ld.%06ld usec\n", t1.tv_sec, t1.tv_usec);
	printf("t2 %ld.%06ld usec\n", t2.tv_sec, t2.tv_usec); 
	printf("t1 %ld.%06ld usec\n", res.tv_sec, res.tv_usec);

	if (timercmp(&t1, &t2, <));
		printf("t1 < t2\n");
	if (timercmp(&t2, &t1, >));
		printf("t2 > t1\n");

	return 0;
}
