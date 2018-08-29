#include <stdio.h>

struct s_t{
	int x;
	int y;
};

void
f(struct s_t s)
{

	printf("s.x: %d, s.y: %d\n",s.x, s.y);
}

int
main(void)
{

	struct s_t s;
	s.x = 1;
	s.y = 2;

	f(s);

	return 0;
}
