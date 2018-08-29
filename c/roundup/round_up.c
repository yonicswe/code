#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// round up 'x' to the nearst multiple of 'y'
#define __round_mask(x, y) ((__typeof__(x))((y)-1))


#define round_up(x, y) ((((x)-1) | __round_mask(x, y)) + 1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

int main(int argc, char *argv[])
{
	int i;
	uint64_t roundto;
	uint64_t max;

	if (argc <= 1) {
		printf("usage\n");
		return -1;
	}

	roundto = atoi(argv[1]);
	max = atoi(argv[2]);

	for (i=0 ; i<max ; i++)
	{
// 		printf("roundup(%d,%d) = %d\n", i, round,  (i+round-1u)/round);
   		printf("round_up(%d,%d)=%d \t| round_down(%d,%d)=%d\n", 
		       i, roundto,  round_up(i,roundto),
		       i, roundto, round_down(i, roundto));
	}
	return 0;
}

/*
 * these kernel's round_[up,down] macros round 'x' up/down to log2 of 'y'
 * i.e. 1st round 'y' to the nearset log2 number from 'y'
 * and then round 'x' to that value.
 * here is a sample of exections :
 *
	round_up(0,4) = 0
	round_up(1,4) = 4
	round_up(2,4) = 4
	round_up(3,4) = 4
	round_up(4,4) = 4
	round_up(5,4) = 8
	round_up(6,4) = 8
	round_up(7,4) = 8
	round_up(8,4) = 8
	round_up(9,4) = 12
	round_up(10,4) = 12
	round_up(11,4) = 12
	round_up(12,4) = 12
	round_up(13,4) = 16
	round_up(14,4) = 16
	round_up(15,4) = 16
	round_up(16,4) = 16
	round_up(17,4) = 20
	round_up(18,4) = 20
	round_up(19,4) = 20
	round_up(20,4) = 20
	round_up(21,4) = 24
	round_up(22,4) = 24
	round_up(23,4) = 24
	round_up(24,4) = 24
	round_up(25,4) = 28
	round_up(26,4) = 28
	round_up(27,4) = 28
	round_up(28,4) = 28
	round_up(29,4) = 32
	round_up(30,4) = 32
	round_up(31,4) = 32 
*/
