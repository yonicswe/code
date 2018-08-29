
/*
 * find last bit of word
 * this is equivalent to log2(word)
 *
 */ 


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static inline unsigned long __fls(unsigned long word)
{
	asm("bsr %1,%0"
			: "=r" (word)
			: "rm" (word));
	return word;
}

static __always_inline int fls(int x)
{
	int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}

/*
 * from https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
 *
 * Built-in Function: int __builtin_clz (unsigned int x)
 * Returns the number of leading 0-bits in x,
 * starting at the most significant bit position.
 * If x is 0, the result is undefined.
 */
static inline uint64_t fls_with_gnu_builtin(uint64_t x)
{
	return x ? sizeof(x) * 8 - __builtin_clz(x) -1 : 0;
}

int main(int argc, char *argv[])
{
	uint64_t x;
	int last_bit=0;

	x = atoi(argv[1]);

	last_bit = __fls(x);
// 	printf("last_bit(0x%x) = %d\n", x, last_bit);
// 	last_bit = fls(x);
// 	printf("last_bit(0x%x) = %d\n", x, last_bit);

// 	last_bit = fls_with_gnu_builtin(x);
	printf("last_bit(0x%llx) = %lld\n", x, last_bit);

	return 0;

}
