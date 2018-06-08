#include "Rows_Threading.h"
#include "file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
/**
 responsible for row calculations for each row in the output matrix
*/
void rowMultiplication (void*thread_id)
{
    int tid = (int) thread_id; //row
    int j,k;
    for (j=0; j<col_out; j++)
    {
        output_matrix[tid][j]=0;
        for (k=0; k<colRow; k++)
            output_matrix[tid][j]+=matrix1[tid][k]*matrix2[k][j];
    }
    pthread_exit(NULL);
}
/**
create threads  for each row in the output matrix and perform necessary computations then join threads
*/
int threadedRows ()
{
    pthread_t threads [row_out];
    int thread,rc;
    for (thread=0; thread<row_out; thread++)
    {
        rc=pthread_create(&threads[thread],NULL,rowMultiplication,(void*)(int)thread);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            return -1;
        }
    }
    for (thread=0; thread<row_out; thread++)
        pthread_join(threads[thread],NULL);
    return 0;
}
