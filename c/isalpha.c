
#include <ctype.h>

int 
main (int argc, char *argv[])
{

	int ch;

	ch = argv[1][0];

	printf("checking %c\n",ch);

	if (isalpha(ch) !=0) {
		printf("%c is alpha\n",ch);
	}
	if (isascii(ch) !=0) {
		printf("%c is isascii\n",ch);
	}
	if (isblank(ch) !=0) {
		printf("%c is isblank\n",ch);
	}
	if (iscntrl(ch) !=0) {
		printf("%c is iscntrl\n",ch);
	}
	if (isdigit(ch) !=0) {
		printf("%c is isdigit\n",ch);
	}
	if (isgraph(ch) !=0) {
		printf("%c is isgraph\n",ch);
	}
	if (islower(ch) !=0) {
		printf("%c is islower\n",ch);
	}
	if (isprint(ch) !=0) {
		printf("%c is isprint\n",ch);
	}
	if (ispunct(ch) !=0) {
		printf("%c is ispunct\n",ch);
	}
	if (isspace(ch) !=0) {
		printf("%c is isspace\n",ch);
	}
	if (isupper(ch) !=0) {
		printf("%c is \n",ch);
	}
	if (isxdigit(ch) !=0) {
		printf("%c is isxdigit\n",ch);
	}

	exit(0);


}

