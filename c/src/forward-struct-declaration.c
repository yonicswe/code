
//         Prototyping structures.
// you can prototype a structure then declare it either as global 
// or as  a property of another structure but only if you declare
// a pointer for that struture !!!!
// the compiler wont accept a static declaration of that structure since
// it wouldnt know how much space to allocate for it.
// you cannot do as follows : 
// 		struct two_t; //prototype
//
// 		struct one_t{
//  		  struct two_t two; //missuse !! only pointers.
// 		};
//
// 		struct two_t{
//    		int data;
// 		};
//
//
//           This is how it should be done.

struct two_t;


struct one_t{
	struct two_t *two;
};


struct two_t{
	unsigned int data;
};


int
main(char *argv[], int argc)
{

	struct one_t one;


	//one.two.data = 12;
	
	return 0;
}
