#include <stdio.h>

struct my_struct_t{
	int x;

	// a union can be used without a name i.e. you can declare the following 
	// union without calling it "as" but like so : 
	// union {
	// 		int y;
	// 		int z;
	// 	};
	// 	and it will still work. just dont use the "as" when defreferencing 'y' or 'z' 
	// 	but instead m1.y or m1.z
	//
	
	union {
		int y;
		int z;
	}as;
};

typedef struct my_struct_t my_struct;


int
main( void )
{

	my_struct m1;

	m1.as.y = 0;
	m1.as.z = 1;

	printf("m1.y = %d\n",m1.as.y);

	return 0;
}
