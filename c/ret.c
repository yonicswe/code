int foo(int x)
{
	return x ? : 10;
}

int main(void)
{	
	int x;

	foo(0);
	foo(1);

	return 0;
}
