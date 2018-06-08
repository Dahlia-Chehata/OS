#include "file_processing.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int row_out,col_out,colRow;
long long** matrix1,**matrix2,**output_matrix;
/**
 -This function responsible for opening the required file ,scanning its content
  and saving it in the allocated memory
- reading matrix 1 and matrix 2
*/
bool readFile(char* fileName,int file_id)
{
    FILE* ptr = fopen(fileName,"r");
    if (ptr==NULL)
    {
        perror("ERROR IN OPENING THE SOURCE FILE !");
        return 0;
    }
    int rows,columns,i,j;
    long long**matrix;
    fscanf(ptr,"row=%d col=%d",&rows,&columns);
    if (!rows|| !columns)
    {
        perror(" ERROR :Matrix is NULL");
        return 0;
    }
    if (file_id==1)
    {
        row_out=rows;
        colRow=columns;
    }
    else
    {
        if (colRow!=rows)
        {
            printf("Dimensional mismatch: can't perform multiplication \n");
            exit(-1);
        }
        col_out=columns;
    }
    matrix = (long long **)malloc(rows*sizeof (long long*));
    for (i=0; i<rows; i++)
        matrix[i]=(long long*) malloc (columns*sizeof (long long));
    for (i=0; i<rows; i++)
        for (j=0; j<columns; j++)
            fscanf(ptr,"%lld",&matrix[i][j]);
    if (file_id==1) matrix1=matrix;
    else matrix2=matrix;
    return 1;
}
/**
 write the output matrix in the required file
*/
bool writeToFile(char*fileName)
{
    FILE* ptr = fopen(fileName,"w");
    if (ptr==NULL)
    {
        perror("ERROR IN OPENING THE DESTINATION FILE !");
        return 0;
    }
    int i, j;
    for (i = 0; i < row_out; i++)
    {
        for (j = 0; j < col_out; j++)
            fprintf(ptr, "%lld\t", output_matrix[i][j]);
        fprintf(ptr, "\n");
    }
    fclose(ptr);
    return 1;
}
