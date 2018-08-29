#include <stdlib.h>
#include <stdio.h>
#define SIZE 4096

char path[SIZE];

int 
main(int argc, char **argv)
{ 
	if (argc<2) 
		exit(1);

	if (realpath(argv[1],path)) 
		printf("%s\n",path);
	else 
		exit(1);
}

