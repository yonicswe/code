
/*
 * is it really possible to write while loop
 * inside an argument list of a method ??
 */

#define SWAP(a,b) \
	do { \
		int tmp = (a); \
		(a) = (b); \
		(b) = tmp; \
	} while(0)


void foo(int x)
{
	x++;
}

int main()
{
	int x=1;
	int y=2;
	// 	foo(SWAP(x,y));
	SWAP(x,y);
	return 0;
}
