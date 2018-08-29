
#include <stdio.h>
/*struct login_flags_t{
    unsigned long nsg:2;
    unsigned long csg:2;
    unsigned long :2;
    unsigned long c_bit:1;
    unsigned long t_bit:1;
    unsigned long :24;
};*/

#define BIG_ENDIAN_BYTE_PRINT(x) \
		x##0,x##1,x##2,x##3,x##4,x##5,x##6,x##7
#define LITTLE_ENDIAN_BYTE_PRINT(x) \
		x##7,x##6,x##5,x##4,x##3,x##2,x##1,x##0

union login_flags_t{
	struct{
    unsigned char t0:1; //lsb
    unsigned char t1:1;
    unsigned char t2:1;
    unsigned char t3:1;
    unsigned char t4:1;
    unsigned char t5:1;
    unsigned char t6:1;
    unsigned char t7:1; //msb
	} bits;
	unsigned char byte;
};
int 
main (int argc, char *argv[])
{
    union login_flags_t login_req_flags;
    unsigned char t_bit;
    unsigned char c_bit;
    unsigned char csg_bits;
    unsigned char nsg_bits;
 	login_req_flags.byte = 0x82;
    //struct login_flags_t* login_flags_p;

    //ogin_flags_p = (struct login_flags_t*)(unsigned char *)&login_req_flags;

/*
    printf("0x%X: t_bit=%d c_bit=%d csg=%d nsg=%d\n",login_req_flags.byte,
           login_req_flags.bits.t_bit,
           login_req_flags.bits.c_bit,
           login_req_flags.bits.csg,
           login_req_flags.bits.nsg);
*/
 	login_req_flags.byte = 0x82;
	printf("BE: 0x%X: %d %d %d %d : %d %d %d %d\n",login_req_flags.byte,
			BIG_ENDIAN_BYTE_PRINT(login_req_flags.bits.t));
	printf("LE: 0x%X: %d %d %d %d : %d %d %d %d\n",login_req_flags.byte,
			LITTLE_ENDIAN_BYTE_PRINT(login_req_flags.bits.t));
					
	login_req_flags.byte = 0xA1;

   	printf("BE: 0x%X: %d %d %d %d : %d %d %d %d\n",login_req_flags.byte,
			BIG_ENDIAN_BYTE_PRINT(login_req_flags.bits.t));
   	printf("LE: 0x%X: %d %d %d %d : %d %d %d %d\n",login_req_flags.byte,
			LITTLE_ENDIAN_BYTE_PRINT(login_req_flags.bits.t));
    return 0;
}
