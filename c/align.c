#include <stdio.h>
#include <stdlib.h>

static inline unsigned long align(unsigned long val, unsigned long align)
{
	return (val + align - 1) & ~(align - 1);
}

int main(int argc, char *argv[])
{
	int x;

	x = atoi(argv[1]);

	printf("align(%d) = %d\n", x, align(x,16));

	return 0;
}
