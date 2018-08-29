
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_ROW_SIZE 120


void
count_file_row_col_size(FILE* fp, int* rows, int* cols)
{
	int ch;

	int biggest_cols =0;
	*cols = 0;
	*rows = 0;
	do{ 
		ch = fgetc(fp);
		if (ch == '0' || ch == '1') 
			(*cols)++;		
		
		if (ch == '\n'){
			(*rows)++; 
			if ((*cols) > biggest_cols)
				biggest_cols =(*cols);
			(*cols) = 0;
		}
		
	}while (ch != EOF);

	(*cols) = biggest_cols;
}

int
alloc_borad(char* conf_file)
{
	FILE* fp;
	int rows;
	int cols;
	char* row_str;
	char matrix;
	

	fp = fopen(conf_file, "r");

	if (fp == NULL) {
		printf("Failed to open \"%s\"\n",conf_file);
		return 1;
	}

	count_file_row_col_size(fp, &rows, &cols);	

	printf("file \"%s\": has rows: %d, cols: %d\n",conf_file, rows, cols);
	matrix	= (char*)malloc(sizeof(char) * rows * cols);

	free(matrix); 
	
	fclose(fp);
	
	return 0; 
}
