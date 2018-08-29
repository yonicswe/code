//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]
// took this off the voltaire code to see if 
// it works.
// and it does.
//
// SOURCE:
// build/src/fcib/itarget/iSCSI_Sources/Voltaire/MngInterface.c
//
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *chop(char *buf)
{
	char *p;
	p=buf+strlen(buf)-1;
	while(isspace(*p) && p!=buf) *p--='\0';
		return buf;
}


int main(void)
{
	char buffer[] =  "yoni and dvora cohen    ";

	char *buffer1 = buffer;
	char *buffer2;

	buffer2 = (char*)malloc(sizeof(buffer));

	buffer2 = chop(buffer1);
}
