#ifndef ELEMENTS_THREADING_H_INCLUDED
#define ELEMENTS_THREADING_H_INCLUDED
/**
struct thread element
*/
typedef struct thread_element
{
    int row,column;
} thread_El;
/**
 performs calculation for each element in the output matrix
*/
void elementMultiplication(void* thread_id);
/**
 responsible for creation of threads which is equal to number of elements in the output array
*/
int threadedElements();

#endif // ELEMENTS_THREADING_H_INCLUDED
