#include <stdint.h>

#define MAX_VAL_16_BITS (1<<16)-1
#define MAX_VAL_12_BITS (1<<12)-1
#define MASK_BIT_16 (1<<15)

int main()
{
	uint32_t u;

	u = MAX_VAL_16_BITS;
	u = MAX_VAL_12_BITS;
	u = MASK_BIT_16;
	return 0;
}
