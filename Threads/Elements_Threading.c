#include "Elements_Threading.h"
#include "file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdint.h>
/**
 performs calculation for each element in the output matrix
*/
void elementMultiplication(void* thread_id)
{
    thread_El *element =(thread_El*)thread_id;
    int k;
    output_matrix[(*element).row][(*element).column]=0;
    for (k=0; k<colRow; k++)
        output_matrix[(*element).row][(*element).column]+=matrix1[(*element).row][k]*matrix2[k][(*element).column];
    pthread_exit(NULL);
}
/**
 responsible for creation of threads which is equal to number of elements in the output array
*/
int threadedElements()
{
    pthread_t threads[row_out*col_out];
    int i,j,rc;
    for (i=0; i<row_out; i++)
    {
        for (j=0; j<col_out; j++)
        {
            thread_El*element= (thread_El*)malloc(sizeof(thread_El));
            (*element).row=i,(*element).column=j;
            rc = pthread_create(&threads[i * col_out + j], NULL, elementMultiplication,(void *)element);
            if (rc)
            {
                printf("ERROR; return code from pthread_create() is %d\n",rc);
                return -1;
            }
        }
    }
    for (i = 0; i < row_out; i++)
        for (j = 0; j < col_out; j++)
            pthread_join(threads[i * col_out + j], NULL);

    return 0;
}
