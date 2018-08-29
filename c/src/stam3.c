struct moshe_t{
	int x;
	char arr_x[20];
};

void func1(char *str)
{
	str[0] = 0;
}


main()
{
	struct moshe_t m1;

	m1.arr_x[19] = 0;
	m1.x = 0;

	func1(m1.arr_x);
	return 0;
}


