#include <stdlib.h>

struct yoni{
    char a;
    char b;
    int c;
};

void func(char *p_a)
{
	int x=0;
	return;
}

int
main (int argc, char *argv[])
{
//    struct yoni* py;
    struct yoni  ty;
	int x;
//	char m=4;
//	char a[3] = {1,2,3};
//	char * pa = NULL;
//
//	pa = &a;
// 
//	x = a;
// 
//	func(a);
//	func(&a);

//	a = m;
	
//    x = sizeof(*y);
    x = sizeof(ty);
    printf("x=%d\n",x);

    return 0;
}
