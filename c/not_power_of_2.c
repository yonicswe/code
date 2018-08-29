

#include <stdio.h>
int main(int argc, char *argv[])
{

	int arg = atoi(argv[1]);
	int not_power_of_2 =0;

	if ((arg & (arg-1)))
		// 		printf("%d - not power of 2\n", arg);
		not_power_of_2 =1;
	else
		printf("%d - power of 2\n", arg);

	return 0;
}
