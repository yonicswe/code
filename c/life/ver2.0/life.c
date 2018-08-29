#include "conf.h"

int 
main(int argc, char* argv[])
{
	char* file_name;

	file_name  = argv[1];
	
	alloc_borad(file_name);	

	return 0;
}
