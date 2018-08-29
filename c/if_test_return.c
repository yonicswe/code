

int f()
{
	return -1;
}

int ff()
{
	int r=0;

	r= f();
	return r ? : -3;
}

int main()
{
	int r;
	r = ff();

	return 0;
}


