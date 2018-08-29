
#include <stdio.h>
#include <stdlib.h>

static inline int mlx5_ilog2(int n)
{
	int t;

	if (n <= 0)
		return -1;

	t = 0;
	while ((1 << t) < n)
		++t;

	return t;
}

int main(int argc, char *argv[])
{
	int n;

	n = atoi(argv[1]);

	printf("mlx5_ilog2(%d) = %d, %d\n", n, mlx5_ilog2(n), 1<<( mlx5_ilog2(n)) );
	return 0;
}
