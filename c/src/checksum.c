#include <string.h>

#define BUF_SIZE 21
			    

char
cal_checksum(char* addr, int size)
{
	int loop;
       char result=0;

	for (loop=0; loop<size; loop++) {
		result ^= addr[loop];
	}


	return result;
}


int
verify_AA_pattern(char* addr, 
	 	   unsigned int  offset,
	 	   unsigned int  size)
{
	 int ret =0;

	 for (;offset<size; offset++) {
		 if ((char)addr[offset] != (char)0xAA) {
		    ret = 1;
		    break;
		 }
	 }

	 return ret;
}


int 
main (int argc, char *argv[])
{
	char buffer[BUF_SIZE];// = {0xFE,2,1};
	int str_len=0;
	char* tst_str = "yoni";

//         int fake_addr1 = 0xc32f8a21;
//         int fake_addr2 = 0xc32f8a20;
//         int align_32 =0;
//
//         align_32 = fake_addr1%0x20;
//         align_32 = fake_addr2%0x20;

	 //printf("checksum: 0x%x\n", cal_checksum((char*)&buffer, 3) );

	memset(buffer, 0xAA, sizeof(buffer));

	strcpy(buffer, tst_str);

	str_len = strlen(tst_str) +1;

	verify_AA_pattern(buffer,str_len, BUF_SIZE); 

	 return 0;
        
}
