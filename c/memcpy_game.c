
#include <stdint.h>

int main()
{
	uint64_t dst;
	uint32_t src;

	src = 0x0a0b0c0d;
	dst = 0x1122334455667788;

	//*((uint32_t*)&dst) = src;
	dst = src;

	return 0;
}
