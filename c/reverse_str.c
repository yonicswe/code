
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <stdlib.h>

#if dbg
	#define my_print(fmt, args...) \
	do {printf(fmt, ## args );}while(0)
#else 
	#define my_print(fmt, args...) \
		do {} while(0)
#endif 

int
non_char(char ch)
{

	my_print("checking %c\n",ch);

	if (isalpha(ch) !=0) {
		my_print("%c is alpha\n",ch);
		return 1;
	}
	if (isascii(ch) !=0) {
		my_print("%c is isascii\n",ch);
		return 1;
	}
	if (isblank(ch) !=0) {
		my_print("%c is isblank\n",ch);
		return 1;
	}
	if (iscntrl(ch) !=0) {
		my_print("%c is iscntrl\n",ch);
		return 1;
	}
	if (isdigit(ch) !=0) {
		my_print("%c is isdigit\n",ch);
		return 1;
	}
	if (isgraph(ch) !=0) {
		my_print("%c is isgraph\n",ch);
		return 1;
	}
	if (islower(ch) !=0) {
		my_print("%c is islower\n",ch);
		return 1;
	}
	if (isprint(ch) !=0) {
		my_print("%c is isprint\n",ch);
		return 1;
	}
	if (ispunct(ch) !=0) {
		my_print("%c is ispunct\n",ch);
		return 1;
	}
	if (isspace(ch) !=0) {
		my_print("%c is isspace\n",ch);
		return 1;
	}
	if (isupper(ch) !=0) {
		my_print("%c is \n",ch);
		return 1;
	}
	if (isxdigit(ch) !=0) {
		my_print("%c is isxdigit\n",ch);
		return 1;
	}

	return 0;

}



#if not_yet
void
reverse_only_chars(char* buff, int size)
{
	char s_w; //pointer to stat of word
	char e_w; //pointer to end of word
	int sz = size;
	int i;


	for (s_w=buff, i=0; i<sz; i++, s_w++) {
		if (non_char(*s_w) == 0 ) {
			e_w = s_w;
			while ( (non_char(*e_w) == 0) && i<sz ){ 
				e_w++;
				i++;
			}
		}


	}

}
#endif

int 
main (int argc, char *argv[])
{

	char file_name[30];
	char *input_str;
	int n=0;
	int fd;



	strcpy(file_name, argv[1]);

	my_print("file: %s\n",file_name);

	fd = open(file_name, O_RDONLY);

	if (fd == -1 ) {
		my_print("failed to open\n");
		exit(1);
	}
	my_print("opened fd: %d\n",fd);

	input_str = (char*)malloc(120);

	while ( (n=read(fd, input_str, 120)) !=0 ) {
		my_print("%s\n",input_str);
	}


	close(fd);
	free(input_str);

	exit(0);
}
