
#include <stdio.h>
int main()
{
	unsigned long x;
	x = 0xffffffffffffffffULL;
	x++;

	printf("x = %d\n", x);

	return 0;
}
