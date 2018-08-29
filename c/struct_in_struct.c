


struct A
{
	int m1;
	struct B {
		int m1;
	} m2;

	struct C {
		int m1;
		int m2;
	} m3;
};


int main()
{

	struct A a;

	struct A a2 =  {
		.m1 = 1,
		.m2.m1 =2,

		.m3 = {
			.m1 =1,
			.m2 =1
		}
	};

	a.m1 = 1;
	a.m2.m1 = 2;

	return 0;
}
