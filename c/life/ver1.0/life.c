
//	       size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
//:       char *strsep(char **stringp, const char *delim);


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "life.h"

	   
void
set_board(struct matrix* m, int col, int row, int data)
{
	*(m->board + m->cols*row +col) = data;
}

int*
get_board(struct matrix *m, int col, int row)
{
	return (m->board + m->cols*row +col);
}

struct matrix* 
alloc_matrix(char* conf_file_name)
{
	
	FILE* fp;
	char* file_name;
	char *tok;
	int cols, rows;
	char* row_p;
	int col;
	int row;
	int data;

	struct matrix* mtrx=NULL;

	char *input_str;
	fp = fopen(conf_file_name, "r");

	if (fp == NULL ) {
		printf("failed to open \"%s\"\n", conf_file_name);
		exit(1);
	}
	
	input_str = (char*)malloc(sizeof(char) * CONF_MAX_ROW_SIZE);
	memset(input_str, 0, sizeof(char)*CONF_MAX_ROW_SIZE);
	row_p = input_str;

	/* get matrix size and allocate */ 
	fgets(row_p, CONF_MAX_ROW_SIZE, fp);
	tok = strsep(&row_p, ",");
	rows = atoi(row_p); 
	cols= atoi(tok); 
	
	printf("cols: %d, rows: %d\n",cols, rows);	

	mtrx = (struct matrix*)malloc(sizeof(struct matrix));
	mtrx->cols  = cols;
	mtrx->rows = rows;
	mtrx->cur_node.col = -1;
	mtrx->cur_node.row = -1;
	
	mtrx->board = (int*)malloc(sizeof(char) * cols * rows);
	memset(mtrx->board, 0, sizeof(char) * cols * rows);

	/* read conf file and initialize the board */
	for (row=0; row<rows; row++){
		
		memset(input_str, 0, sizeof(char)*CONF_MAX_ROW_SIZE);
		row_p = input_str;
		fgets(row_p, CONF_MAX_ROW_SIZE, fp);
		
		for (col=0; col<cols; col++){
			tok = strsep(&row_p, ",");	
			data = atoi(tok);
			set_board(mtrx, col, row, data);
		}
	}
		

	fclose(fp);
	free(input_str);
	return mtrx;

}

void
free_matrix(struct matrix* m)
{

	free(m->board);
	free(m);
}

void
print_matrix(struct matrix* m)
{
	int cols;
	int rows;
	int col;
	int row;
	int data;
	cols = m->cols;
	rows = m->rows;

	for (row=0; row<rows; row++)
		for (col=0; col<cols; col++){
			
			data = *(get_board(m, col, row));
			printf("%c ",(data==1)?'x':' ' );
			if (col%(cols-1) == 0 && col !=0 )
				printf("\n");
		}
	printf("\n");	

}

int
count_neighs(struct matrix* m, struct node* n) 
{
	int max_col = m->cols-1;
	int max_row = m->rows-1;
	int col = n->col;
	int row = n->row;
	int count=0;
/*
	col-1, row-1 | col, row-1 | col+1, row-1
	-------------+------------+-------------
	col-1, row   |            | col+1, row
	-------------+------------+-------------
  	col-1, row+1 | col, row+1 | col+1, row+1 
 
 */ 
		
	/* upper row */		
	if (col-1 >= 0 && row-1 >=0 ) 
		count += *(get_board(m, col-1, row-1));

	if (row -1 >= 0)  
		count += *(get_board(m, col, row-1));
	
	if (col+1 <= max_col && row-1 >=0) 
		count += *(get_board(m, col+1, row-1));

	/* local row */
	if (col-1 >=0)
		count += *(get_board(m, col-1, row));
	
	if (col+1 <= max_col) 
		count += *(get_board(m, col+1, row));

	

	/* lower row */ 
	if (col-1 >=0 && row+1 <= max_row)
		count += *(get_board(m, col-1, row+1));

	if (row+1 <= max_row) 
		count += *(get_board(m, col, row+1));

	if (col+1 <= max_col && row+1 <= max_row)
		count += *(get_board(m, col+1, row+1));

	return count;
}


void
iterate_matrix(struct matrix* m, int count)
{

	struct node* cur_n;
	int neighs;
	int i;
	
	for (i=0; i<count; i++){
		
		printf("cycle: %d\n",i); 
		print_matrix(m);

		while ((cur_n = get_next_node(m)) != NULL){
			//print_matrix(m); 
			neighs = count_neighs(m, cur_n);
			live_or_die(neighs, cur_n);
		}
	}
}

struct node*
get_next_node(struct matrix* m)
{
	int *col = &(m->cur_node.col);
	int *row = &(m->cur_node.row);
	struct node* n = &m->cur_node;
	int max_col = m->cols-1;
	int max_row = m->rows-1;
	
	/* 1st time */ 
	if (*col == -1 && *row == -1) {
		(*col) = 0; 
		(*row) = 0; 
		n->cell = get_board(m,0,0); 
		return n;
	}

	/* last col */ 
	if (*col == max_col){
		if (*row == max_row){
			/* last row => reset */ 
			(*col) = -1; 
			(*row) = -1; 
			return NULL;
		}

		(*col)=0;
		(*row)++;
		n->cell = get_board(m, *col, *row);
		return n;
	}

	(*col)++;
	n->cell = get_board(m, *col, *row);
	return n;

}

int 
live_or_die(int neighs, struct node* n)
{	
	int *life = n->cell;
	if (*life == 0){
		/* check if life can be created */
		if (neighs >= 2 )
			*life = 1;
	}
	else{
		/* check if cell should die */ 
		if (neighs > 2){ 
			/* to croud */
			*life = 0; 
		}
		else{
			if (neighs < 2 ) {
				/* to lonely */ 
				*life = 0;
			}
		}
	} 

}

void
usage(void)
{
	printf("Usage: life <conf file name> <number of iterations>\n");
	exit(1);
}

int
main(int argc, char* argv[])
{
	char* conf_file_name;
	struct matrix* m;
	int iterations;
	
	if (argc != 3) 
		usage();
	
	conf_file_name = argv[1];
	iterations = atoi(argv[2]);

	m = alloc_matrix(conf_file_name);

	iterate_matrix(m,iterations);

	free_matrix(m);

	return 0;
}
