#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_LINE_LEN 256

int
main(void)
{

	char Buff[DEFAULT_LINE_LEN];
	int  BuffLen = 0;

	while(1)	{	
		char* r = fgets( (char*)Buff, DEFAULT_LINE_LEN, stdin );
		if (r == NULL)
		{
			BuffLen = 0;
		}
		else
		{
			BuffLen = strlen((char*)Buff);
		}
	}
}
