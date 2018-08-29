#include<stdlib.h>

void
cast_func(int i_buff)
{
	int i;

	i = i_buff;

}


int
main (void)
{
	long l_buff;
	void* p_buff;


	p_buff = (void*)malloc( 5 * sizeof(int));

//	l_buff = p_buff;	
	cast_func(p_buff);


	return 0;
	
	
}
