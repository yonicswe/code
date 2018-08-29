
#include <stdio.h>

int compare(int a, int b)
{
	int d;

	d = (a-b) << 8;
	return d;
}

int main()

{
	printf("d = %d\n", compare(4,5));
	printf("d = %d\n", compare(5,4)); 
	return 0;
}
