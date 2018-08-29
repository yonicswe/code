
#include <stdlib.h>
#include <stdio.h>

unsigned int mylog2( unsigned int x )
{
  unsigned int ans = 0 ;

  if (x == 1)
	  return 1;
  while( x>>=1 ) ans++;
  return ans ;
}

inline int mlx5_ilog2(int n)
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
	int val;

	val = atoi(argv[1]);
	//printf("log2(%d) = %d\n", val, mylog2(val));
	printf("log2(0x%x) = %d\n", val, mlx5_ilog2(val));

	return 0;
}
