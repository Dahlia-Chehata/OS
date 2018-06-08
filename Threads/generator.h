#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED
/**
generates random matrices for file and file b if they have been found empty
*/
void random_generator();
/**
 this function is responsible for writing each randomly generated value in file
*/
void fill (char*fileName,int r,int c);
/**
-check if the file is empty
*/
int checkIfEmpty(char*fileName);

#endif // GENERATOR_H_INCLUDED
