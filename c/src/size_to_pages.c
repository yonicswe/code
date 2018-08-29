
#define PAGE_SIZE 4096
#define PAGE_SHIFT 12
#define SIZE_TO_PAGES(size) \
       (size/PAGE_SIZE) + ((size%PAGE_SIZE)?1:0)
	


int 
get_order(unsigned long size)
{
	int order;

	size = (size-1) >> (PAGE_SHIFT-1);
	order = -1;
	do {
		size >>= 1;
		order++;
	} while (size);
	return order;
}

int 
main(void)
{

	int order=0;
	unsigned long size=0;

	//size = atoi(argv[1]);
    size = 4096;
	order = get_order(size);
//
//        pages = (size/PAGE_SIZE) + ((size%PAGE_SIZE)?1:0);



	printf("size: %d, order: %d\n",size, order);

	return 0;


}
