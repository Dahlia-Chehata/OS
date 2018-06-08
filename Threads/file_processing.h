#ifndef FILE_PROCESSING_H_INCLUDED
#define FILE_PROCESSING_H_INCLUDED
#include <stdbool.h>
extern int row_out,col_out,colRow;
extern long long** matrix1,**matrix2,**output_matrix;
/**
 -This function responsible for opening the required file ,scanning its content
  and saving it in the allocated memory
- reading matrix 1 and matrix 2
*/
bool readFile(char* fileName,int file_id);
/**
 write the output matrix in the required file
*/
bool writeToFile(char*fileName);
#endif // FILE_PROCESSING_H_INCLUDED
