#include <stdio.h>

enum mask {
	CAP_1 = (1<<0),
	CAP_2 = (1<<1)
};


void foo(enum mask m)
{
	if (m | CAP_1)
		printf("CAP_1\n");
	if (m | CAP_2)
		printf("CAP_2\n");

	printf("\n");
}

int main()
{

	enum mask;

	foo(CAP_1);
	foo(CAP_1| CAP_2);

	return 0;

}
