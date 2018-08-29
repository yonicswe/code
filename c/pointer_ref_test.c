
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char yonic[] = "yonicohen";
char dvoric[] = "dvoric";


void
func1(char** str, int which)
{
	if (which==1)
		*str=yonic;
	if (which==2) 
		*str=dvoric;

}



int 
main(void)
{
	char name[64];
	char* name_ref;
    unsigned long yonic_size = sizeof(yonic);

    char *c1;
    char *c2;

// 	func1(&name, 1);
// 	printf("name: %s\n",name);
// 	func1(&name, 2);
// 	printf("name: %s\n",name);

//  name = malloc(yonic_size);

    name_ref = name;

    memcpy(name, yonic, yonic_size);

    c1 = &name[2];
    c2 = &name_ref[2];

//     free(name);

	
	return 0;
}
