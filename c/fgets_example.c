#include <stdio.h>


int
main(int argc, char* argv[])
{
	FILE* fp;
	char* conf_file_name;
	char input_str[120] = {0};
	char *eof=NULL;
	//int count;

	conf_file_name = argv[1];
	//count = atoi(argv[2]);

	fp = fopen(conf_file_name, "r");

	if (fp == NULL) {
		printf("failed to open\n");
		return 1;
	}

	while ( (eof = fgets(input_str, 120, fp)) != NULL ) {
		printf("input_str: %s",input_str);
	}

	fclose(fp);	

	return 0;
}
