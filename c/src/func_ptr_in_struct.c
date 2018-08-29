typedef struct test{
	void (*func_ptr)(void);
}test;

void my_print1(void)
{
	printf("\n\n!!hello yoni from my_print1!!\n\n");
}

void my_print2(void)
{
	printf("\n\n!!hello yoni from my_print2!!\n\n");
}

void* ptr_arr[] = {my_print1,my_print2};

void main(void)
{
	test test1;
	int i;

	for (i=0; i<2 ; i++){
		test1.func_ptr = ptr_arr[i];
		test1.func_ptr();	
	}
}


