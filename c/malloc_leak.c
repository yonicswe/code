#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// 
// doing this test to check if there is a correlation between 
// dynamic memory allocations to a process's RSS 
//


int
main(int argc, char* argv[])
{
	int size=0;
	int x;
	void *p;

	size = atoi(argv[1]);
	printf("allocating %d Mbytes",size);
	size *= 1024*1024;

	p = malloc(size);

// 	x = size;
// 	while (1) {
// 		sleep (1);
// 		 x -= 10;
// 		if ( x <= 0 ) 
// 			x = size;
// 	}
 
    ((char*)p)[size-2] = 1;

//      free (p); 

    return 0;
}
