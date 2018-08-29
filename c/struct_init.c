

struct st {
	int x;
	int y;
};

struct base {
	int x;
	int y; 
};

struct child {
	struct base b;
	struct st *s;
	int x;
};


int main ()
{
	struct child c = {};

	c.x =0 ;

	return 0;
}
