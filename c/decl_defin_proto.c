

int 
main(void)
{
	int a=3;
	int b=2;
	int c=3;

	c = my_max(a,b);

	return c;
	

}

int my_max(int a, int b)
{
	return my_max_2(a,b);
}

int my_max_2(int a, int b)
{
	return (a>b);
}
