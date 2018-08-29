

struct t{
	union {
		int x;
		int y;
	}; // <----------- you can define a union (or struct without a name or type
	   //              and then access it directly.
};

int main(void)
{
	struct t t1;

	t1.x = 5;
	t1.y = 6;

	return 0;
}
