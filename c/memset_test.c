#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
int buffer[BUFFER_SIZE] = {0};


struct child_t {
	struct father_t {
		int x;
		int y;

	} father;

	int x;
	int y; 
};


int
main(int argc, char *argv[])
{
	int val=0;

	struct child_t c = {};

	c.father.x =1;
	c.father.x++;

	val =strtoul(argv[1], NULL, 10);

	memset(buffer, val, BUFFER_SIZE);


	return 0;
}
