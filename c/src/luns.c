#include <stdlib.h>


#define TOTAL_LUNS			2
#define SECTORS_PER_LUN		256
#define SECTOR_SIZE			4
#define PAGE_SIZE			128
#define SECTORS_PER_PAGE	(PAGE_SIZE / SECTOR_SIZE)

#define LUN_SECTOR_VALID(LUN,SECTOR) \
	( (LUN>=0) && (LUN<TOTAL_LUNS) && (SECTOR>=0) && (SECTOR<SECTORS_PER_LUN) )

#define SECTORS_TO_PAGE_BREAK(SECTOR) (32 - (SECTOR % 32) )
#define SIZE_TO_PAGE_BREAK(SEC_2_PG_BRK) (SECTOR_SIZE * SEC_2_PG_BRK)
	

struct iov{
	void* base;
	unsigned long len;
};

struct data_buf{
	void* data;
	unsigned long len;
};


struct sector_t {
	void* page_p;
	unsigned long page_offset;
	unsigned char valid;
	unsigned long size;
};

struct sector_t* lun_array[TOTAL_LUNS];
void init_storage(void);


void
clear_storage(void)
{
	unsigned int lun;
	unsigned int sector;

	for (lun=0; lun<TOTAL_LUNS; lun++) {

		for (sector=0; sector<SECTORS_PER_LUN; sector += SECTORS_PER_PAGE ) {
			free( (lun_array[lun])[sector].page_p );
		}
	}
	
}

void 
init_storage(void)
{
	unsigned int lun;
	unsigned int sector;
	void* last_page_p;

	for (lun=0; lun<TOTAL_LUNS; lun++) {
		lun_array[lun] = (void*)malloc(sizeof(struct sector_t) * SECTORS_PER_LUN);

		//==================================
		// init each sector.
		//==================================
		last_page_p = NULL;
		for (sector=0; sector<SECTORS_PER_LUN; sector++) {

			(lun_array[lun])[sector].valid = 1;	//1=VALID, 0=NOT-VALID
			(lun_array[lun])[sector].page_offset = (sector % SECTORS_PER_PAGE) * SECTOR_SIZE;
			(lun_array[lun])[sector].size = SECTOR_SIZE;

			if (sector % SECTORS_PER_PAGE == 0) {
				(lun_array[lun])[sector].page_p = (void*)malloc(sizeof(unsigned char) * PAGE_SIZE);//128 BYTES
				last_page_p = (lun_array[lun])[sector].page_p;
			}
			else {
				(lun_array[lun])[sector].page_p = last_page_p;
			}
		}
	}
}

void 
set_sector(unsigned long lun, 
		   unsigned long sector, 
		   unsigned long val)
{
	memset( (lun_array[lun])[sector].page_p + (lun_array[lun])[sector].page_offset, 
			val,
			(lun_array[lun])[sector].size );
}



void
sector_to_ptr(unsigned long lun, 			//IN
			  unsigned long sector,			//IN
			  unsigned long size,			//IN
			  struct iov* iov_arr,			//OUT
			  unsigned long *iov_arr_len)	//OUT
{

	unsigned long sz_2_pg_brk;
	unsigned long sctrs_2_pg_brk;

	sctrs_2_pg_brk = SECTORS_TO_PAGE_BREAK(sector);
	sz_2_pg_brk = SIZE_TO_PAGE_BREAK( sctrs_2_pg_brk );

	if (sz_2_pg_brk >= size) {
		iov_arr[0].base = (lun_array[lun])[sector].page_p + (lun_array[lun])[sector].page_offset;
		iov_arr[0].len = size;
		*iov_arr_len = 1;

	}
	else {
		iov_arr[0].base = (lun_array[lun])[sector].page_p + (lun_array[lun])[sector].page_offset;
		iov_arr[0].len = sz_2_pg_brk;
		iov_arr[1].base = (lun_array[lun])[sector+sctrs_2_pg_brk].page_p +
                            (lun_array[lun])[sector+sctrs_2_pg_brk].page_offset;
		iov_arr[1].len = size - sz_2_pg_brk;
		*iov_arr_len = 2;
	}   
}

int
main(int argc, 
	 char* argv[])
{
	char* sector_p;    
	struct iov iov_arr[2] = {{NULL,1},{NULL,2}};
	unsigned long iov_len;

	init_storage();

	set_sector(0,0,0);
	set_sector(0,1,1);
	set_sector(0,2,2);
	set_sector(0,3,3);

	//create iovec from sector=1 holding 30bytes.
	sector_to_ptr(0,1,30,iov_arr,&iov_len);

	//create iovec from sector=30 holding 10bytes.
	sector_to_ptr(0,30,10,iov_arr,&iov_len); 

	//create iovec from sector=30 holding 10bytes.
	sector_to_ptr(0,1,128,iov_arr,&iov_len); 

	//create iovec from sector=30 holding 10bytes.
	sector_to_ptr(0,20,128,iov_arr,&iov_len); 

	clear_storage();
	
	return 0;
}

	   
