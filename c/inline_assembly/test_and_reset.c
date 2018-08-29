
#include <stdio.h>


typedef long							REGISTER,	*PREGISTER;
typedef unsigned char					BOOLEAN,	*PBOOLEAN;
#define BTR_POSTFIX						"btrq"

//
// to see the inline-assembler result you can invoke gcc with -ggdb switch 
// and then use objdump -S to the sources intermixed with assembly.
//
// 1. gcc -ggdb test_and_reset.c -o test_and_reset
// 2. objdump -S test_and_reset | less
//
//
static inline BOOLEAN 
kosdep_asm_bit_test_and_reset(
   PREGISTER prBitField, 
   REGISTER rBitID)
{
	BOOLEAN bReturn;

   __asm__ volatile
	(
		"lock ;" BTR_POSTFIX " %2, %0 ;"
		"setc %1"
		: "=m" (*prBitField), "=mq" (bReturn)
		: "Jr" (rBitID)
		: "memory"
	);


	// TRUE if CF (Old=1)
	return bReturn;
}

int 
main()
{
   REGISTER reg=0xff;
   REGISTER bit=1;

   printf("calling kosdep_asm_bit_test_and_reset\n");
   kosdep_asm_bit_test_and_reset(&reg, bit);

   return 0;

}
