
#include <stdlib.h>


int
fib2(int x)
{
	int a,b;
	static int printed=0;
	
	if (x<=2 ){ 
		if (x > printed){
			printf("1 1 ");
			printed++;
		}
		return 1;
	}
		
	a = fib(x-1);
	b = fib(x-2);
	if (x > printed){
		printf("%d ",a+b);
		printed++;
	}
	return a+b; 
}

int
fib1(int n)
{
    if (n == 1) {
        return 1;
    }

    if (n == 2) {
        return 2;
    }

    return  fib(n -1) + fib(n-2);
}



int 
main(int argc, char *argv[])
{
    int n; 
    int index;
    int len=0;
    char buffer[1024]={0};

    n = atoi(argv[1]);

    for (index=1; index < n; index++) {
        sprintf((char*)(buffer+len),"%3d, " ,fib(index) );
        len += 5;
    }

    printf("%s\n",buffer);

    return 0;
}
