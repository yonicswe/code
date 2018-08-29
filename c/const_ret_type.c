
#include <stdio.h>

const int f1(int x)
{

	return x+1;

}

// not much point in using const as a return type since 
// it means that the function writer means for the caller of his function 
// not to be able to change the return value.
// but the return value is saved on a local variable which is no const.


int
main(void)
{
	int x=1;
	int y=0;

	y =f1(x);
	
	printf("y= %d\n", y);

	y++;
	printf("y= %d\n", y);

	return 0;
}
