
/*
 * the differences between array and pointer are 
 * 1. sizeof(p) is 8 which is the address size on a 64 bit machine   
 *    sizeof(a) is 19 the actual array size holding the one byte characters and the newline 
 * 
 * 2. according to c semantics an array name is a synonym for its 1st element 
 *    but a pointer is not 
 *    here is the output of objdump -Sl array_vs_pointer
			 c = a[3];
		  400606:       0f b6 45 e3             movzbl -0x1d(%rbp),%eax -\
		  40060a:       88 45 f7                mov    %al,-0x9(%rbp)   -/  1 step
				c = p[3];
		  40060d:       48 8b 45 f8             mov    -0x8(%rbp),%rax --\
		  400611:       0f b6 40 03             movzbl 0x3(%rax),%eax     } 3 steps 
		  400615:       88 45 f7                mov    %al,-0x9(%rbp)  --/  needed for pointer arithmetics
 * 
 * 3. you cannot change the value of array althogh you might consider it as a pointer.
 *    you cannot do a++ but you can do p++
 *
 * 4. one of the common gotch in c is declaring an array in one file like 
 *        char my_arr[10];
 *    and in another file reach it with extern 
 *        extern char* my_arr;   
 */

#include <stdio.h>

// void print_a(char* a, int s)  // its the same as the next line
void print_a(char a[], int s)
{
	int i;
	for (i=0; i<s; i++)
		printf("%c,", a[i]);

	printf("\n");

}

int main(void)
{
	char a[] = "yonicohenisthebest";
	int x1;
	int x2;
	int x3;
	char c;
	char* p = a;

	
	c = a[3];
	c = p[3];

	// a++; // compilation error
	p++;

#if 0
	printf("sizeof(p) is %u\n", sizeof(p));
	printf("sizeof(a) is %u\n", sizeof(a));

	printf("1st element of p is %c\n", p[3]);
	printf("1st element of a is %c\n", a[3]);


	print_a(p, 4);
	print_a(a, 4);
	// 	print_a(&a, 4); // cause a compilation error
	print_a((char*)&a, 4);
#endif
	return 0;
	
}
