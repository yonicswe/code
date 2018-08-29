
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int e = atoi(argv[1]);
	printf("%d\n", e); 
	printf("%d : %s\n", e, strerror(-1 * e)); 
	return 0;
}
