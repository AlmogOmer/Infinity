#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
void matrix_sum(int **matrix, int row_num, int col_num, int *result_arr);
int main()
{
	int row_num = 3;
	int col_num = 3;
	int **matrix;
	int i = 0;
	int j = 0; 
	int *result_arr;
	result_arr = (int*)malloc(row_num*sizeof(int));
	matrix = (int **)malloc(row_num*sizeof(int*));
	for(i=0; i< row_num; ++i)
	{
		matrix[i] = (int*)malloc(col_num*sizeof(int));
	}
	
	/* fill the matrix with numbers*/
	for(i=0; i<row_num; i++)
	{
		for(j=0; j<col_num; j++)
                {
                    matrix[i][j] = 2;
                }
        }
	
	matrix_sum(matrix, row_num, col_num, result_arr);		
	return 0;
}
		

void matrix_sum(int **matrix,int row_num, int col_num, int *result_arr)
{
	
	int i = 0, j = 0;
	int sum_row =0;
	for(i = 0; i<row_num; ++i)
	{
		sum_row = 0;
		for (j = 0; j<col_num; ++j)
		{
			sum_row += matrix[i][j];
			
		}
		result_arr[i]= sum_row;
	}
	for ( i = 0; i<row_num; ++i)
	{
		printf("%d ", result_arr[i]);
	}
	
}
	
	

