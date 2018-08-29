#include <stdio.h>
#include <string.h>

#define enter_crit(ch) \
	_enter_crit(ch,__FUNCTION__)

void _enter_crit(char ch,char* calling_func_name)
{
	printf("got %c from %s\n",ch,calling_func_name);
}

void func_a(void)
{
	enter_crit('a');
}

void func_b(void)
{
	enter_crit('b');
}

void func_c(void)
{
	enter_crit('c');
}

typedef enum yoni_e{
	A,
	B,
	C
}yoni_e;

int main(void)
{
	yoni_e yoni;
	char arr[11] = {'d','v','o','r','a',' ','n','e','d','e','l'};
	char arr_p[] = "yoni cohen";
	char *p_arr = arr;
	
	unsigned char num_arr[4] = {0,1,0,0};
	unsigned long num;


	

	num = *(unsigned long*)num_arr;

	printf("num=%u\n",num);

	
	func_a();
	func_b();
	func_c();
	return (0);
}

