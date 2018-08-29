
#include <stdio.h>

#define __raw_readb(a)          (*(volatile unsigned int   *)(a))

#define ioread8(p)  ({ unsigned int __v = __raw_readb(p); __v; })

#define KSEG_VIRT_ADDR(x) 0xffffffff##x

int
main (void)
{
	int x;
	int arr[3] = {1, 2, 3};

   x = KSEG_VIRT_ADDR(BA90000);

	x = ioread8(&arr[1]);

	printf("x: %u\n", x);
		

	return 0;
}



