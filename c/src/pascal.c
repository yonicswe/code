
/* 
	     Build pascal triangle 
	=============================
	line 0   			1
    line 1			  1   1
	line 2			1   2   1
	line 3		  1   3   3   1
	line 4		1   4   6   4   1
	line 5	  1   5   10  10  5   1



 
*/







#include <stdlib.h>

void
pascal(int max_row)
{
	int *pas_arr;
	int pas_arr_size;
	int row,col;
	int *prev_row;
	int *cur_row;

	/* calc the size of needed array that holds all lines of pascal triangle */
	for (pas_arr_size=0, row=0; row< max_row; row++)
		pas_arr_size += row+1;

	/* allocate the array */
	pas_arr = (int*)malloc(sizeof(int) * pas_arr_size );
	pas_arr[0]= 1;

	for (row=1, prev_row = &pas_arr[0], cur_row = &pas_arr[1]; 
			row < max_row; 
			row++) {

		cur_row[0] = 1; 
		cur_row[row] = 1;

		for (col=1 ; col < row ; col++) {
			cur_row[col] = prev_row[col-1] + prev_row[col];			
		} 		
		

		if (row+1 < max_row) {	
			prev_row = cur_row;
			cur_row = &cur_row[row+1];
		}	
	}

	for (col=0; col < row; col++)
		printf("%d ",cur_row[col]);
	
	
	free(pas_arr);
	

}



int
main (int arg, char* argv)
{
	
	pascal(1);	
	printf("\n");
	pascal(2);	
	printf("\n");
	pascal(3);	
	printf("\n");
	pascal(4);	
	printf("\n");
	pascal(5);	
	printf("\n");
	pascal(6);	
	printf("\n");
	pascal(7);	
	printf("\n");
	
	return 0;
}
