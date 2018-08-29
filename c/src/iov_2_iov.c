#include <stdlib.h>
#include <stdio.h>

#define u32 unsigned long

struct iovec{
	void* iov_base;
	u32 iov_len;
};

struct iovec lun_arr[30] = {{0,4},{4,4},{8,4},{12,4},
                            {16,4},{20,4},{24,4},{28,4},
                            {32,4},{36,4},{40,4},{44,4}};

/*=============================================
copy from one iovec array to another.
=============================================*/
int
cpy_iovarr_2_iovarr(struct iovec* src_iov,
					u32 src_iov_len,
					struct iovec* dst_iov,
					u32 dst_iov_len)
{
	u32 indx;
	u32 max_indx;

	void* src_addr;
	void* dst_addr;
	u32 src_indx			=0;
	u32 dst_indx			=0;
	u32 src_offset		=0;
	u32 dst_offset		=0;
	u32 src_size			=0;
	u32 dst_size			=0;
	u32 cpy_size			=0;
	u32 src_total_size	=0;
	u32 dst_total_size	=0;


    //calculate src_total_size and dst_total_size
	max_indx = (src_iov_len > dst_iov_len)? src_iov_len: dst_iov_len;
	for (indx = 0 ; indx < max_indx ; indx++ ) {
		src_total_size += (indx < src_iov_len)?src_iov[indx].iov_len:0;
		dst_total_size += (indx < dst_iov_len)?dst_iov[indx].iov_len:0;
	}

	//sanity check
	if (dst_total_size < src_total_size)
		return 1;

	while (src_total_size > 0) {
		src_size = src_iov[src_indx].iov_len - src_offset;
		src_addr = (void*)((u32)src_iov[src_indx].iov_base + src_offset);
		dst_size = dst_iov[dst_indx].iov_len - dst_offset;
		dst_addr = (void*)((u32)dst_iov[dst_indx].iov_base + dst_offset);

		cpy_size = (src_size < dst_size) ? src_size : dst_size ;

		memcpy(dst_addr, src_addr, cpy_size);

		src_total_size -= cpy_size;

		src_offset = (src_offset + cpy_size)%src_iov[src_indx].iov_len;
		dst_offset = (dst_offset + cpy_size)%dst_iov[dst_indx].iov_len;

		src_indx += (src_offset)?0:1;
		dst_indx += (dst_offset)?0:1;
	}   

	return 0;
}

/*=============================================
        allocate memeory to an iovec array 
        and initialize with the sizes in 
        init_sizes
=============================================*/
int
alloc_iovarr(struct iovec** iov_arr,		//OUT
			u32 iov_arr_size,	//IN
			u32 *init_sizes)	//IN
{
	u32 indx;

	(*iov_arr) = (struct iovec*)malloc(sizeof(struct iovec) * iov_arr_size);

	if ((*iov_arr) == NULL)
		return 1;

	for (indx =0 ; indx<iov_arr_size; indx++) {
		(*iov_arr)[indx].iov_base = (struct iovec*)malloc( sizeof(char) * init_sizes[indx]);

		if ((*iov_arr)[indx].iov_base == NULL)
			return 1;

		(*iov_arr)[indx].iov_len = init_sizes[indx];
	}            

	return 0;
}

/*=============================================
        free the iovec memeory regiosns 
=============================================*/
void
free_iovarr(struct iovec* iov_arr,    	//IN
			u32 iov_arr_len)	//IN
{
	u32 indx;

	for (indx =0 ; indx < iov_arr_len; indx++) {
		free(iov_arr[indx].iov_base);
	}

	free(iov_arr);
}


/*=============================================
    print the content of the iovec array.
=============================================*/
void
print_iovarr(struct iovec* iov_arr,
             u32 iov_arr_len)
{
    u32 iov_indx;
    u32 ch_indx;

    for (iov_indx = 0 ; iov_indx < iov_arr_len; iov_indx++) {

        for (ch_indx=0; ch_indx < iov_arr[iov_indx].iov_len; ch_indx++) {
            putchar( ((char*)(iov_arr[iov_indx].iov_base))[ch_indx] );
            putchar(',');
        }
        putchar ('\n');
    }
}


void
lun_sector_ofset_2_iovarr(/*u32 lun,*/
                          u32 sector,
                          u32 ofset,
                          u32 size,
                          struct iovec** iov_arr,
                          u32* iov_arr_len)
{
    u32 indx;
    u32 base;
    u32 len;
    u32 ofset_sector = ofset / 4;
    ofset = ofset % 4;

    (*iov_arr_len) = 1;
    (*iov_arr_len) += (size - 4 + ofset) / 4;
    (*iov_arr_len) += ( (size - 4 + ofset)%4 ) ? 1 : 0 ;

    *iov_arr_len = (void*)malloc(sizeof(struct iovec) * (*iov_arr_len) ) ;

    for (indx=0; indx<iov_arr_len; indx++) {
        base = lun_arr/*[lun]*/[sector].iov_base;
    }
}


int
main(int argc,char* argv[])
{
	int ret;

	u32 src_data_sizes[] =  {4,5,4,12};
	u32 src_data_sizes_len = sizeof(src_data_sizes)/sizeof(u32);
	u32 dst_data_sizes[] =  {4,3,5,2,15};
	u32 dst_data_sizes_len = sizeof(dst_data_sizes)/sizeof(u32);

	char* names[] = {"yoni","dvora", "maya","cohen family"};

	struct iovec* src_iov;
	u32 src_iov_len;
	struct iovec* dst_iov;
	u32 dstiov_len;


	ret = alloc_iovarr(&src_iov,
					   src_data_sizes_len,
					   src_data_sizes);

	if (ret)
		return 1;

	ret = alloc_iovarr(&dst_iov,
					   dst_data_sizes_len,
					   dst_data_sizes);
	if (ret)
		return 1;

    printf("src_iov:\n");
    print_iovarr(src_iov, src_data_sizes_len);

    memcpy (src_iov[0].iov_base,names[0], strlen(names[0]));
    memcpy (src_iov[1].iov_base,names[1], strlen(names[1]));
    memcpy (src_iov[2].iov_base,names[2], strlen(names[2]));
    memcpy (src_iov[3].iov_base,names[3], strlen(names[3]));
    
    printf("src_iov:\n");
    print_iovarr(src_iov, src_data_sizes_len);

    ret = cpy_iovarr_2_iovarr(src_iov,
							  src_data_sizes_len,
							  dst_iov,
							  dst_data_sizes_len);
    printf("dst_iov:\n");
    print_iovarr(dst_iov, dst_data_sizes_len);

    if (ret)
		return 1;


	free_iovarr(src_iov, src_data_sizes_len);
	free_iovarr(dst_iov, dst_data_sizes_len);

	return 0;
}
	
