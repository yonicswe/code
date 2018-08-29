#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_THREADS 27

#define THREAD_MASK(i) \
	( (0xffffffe0 >> ( MAX_THREADS - i ) ) & 0xffffffe0 )

int
main(int argc, char *argv[])
{
	unsigned long num_of_threads;
	num_of_threads = strtoul(argv[1], NULL, 10);

	printf("for %ul threads, the threadmask is %x\n",
			num_of_threads, THREAD_MASK(num_of_threads));

	return 0;

}
