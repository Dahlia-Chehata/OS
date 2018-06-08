#ifndef ROWS_THREADING_H_INCLUDED
#define ROWS_THREADING_H_INCLUDED
/**
 responsible for row calculations for each row in the output matrix
*/
void rowMultiplication (void*thread_id);
/**
create threads  for each row in the output matrix and perform necessary computations then join threads
*/
int threadedRows ();

#endif // ROWS_THREADING_H_INCLUDED
