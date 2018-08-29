#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)

int main(int argc, char *argv[])
{
	int i;
	int round;
	int max;
	uint64_t result;
	uint64_t round_mask;
	uint64_t roundme;

	round = atoi(argv[1]);
	max = atoi(argv[2]);

	for (i=0 ; i<max ; i++)
	{
		printf("roundup(%d,%d) = %d\n", i, round,  (i+round-1u)/round);
	}


	roundme = 0xa000;
	round_mask = 1 << 2;
	result = round_up(roundme, round_mask);

	return 0;
}
