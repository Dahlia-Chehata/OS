#include "file_processing.h"
#include"generator.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int maxArraySize=1000;
/**
generates random matrices for file and file b if they have been found empty
*/
void random_generator()
{
    srand((unsigned)time(NULL));
    if (checkIfEmpty("a.txt")||checkIfEmpty("b.txt"))
    {
        colRow = rand()% maxArraySize;
        row_out = rand()% maxArraySize;
        col_out = rand()% maxArraySize;
        fill("a.txt",row_out,colRow);
        fill("b.txt",colRow,col_out);
    }
}
/**
 this function is responsible for writing each randomly generated value in file
*/
void fill (char*fileName,int r,int c)
{
    FILE *fptr = fopen(fileName,"w");
    int i,j;
    fprintf(fptr,"row=%d col=%d\n",r,c);
    for(i = 0; i<r; i++)
    {
        for(j=0; j<c; j++)
            fprintf(fptr,"%d\t",rand());
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}
/**
-check if the file is empty
*/
int checkIfEmpty(char*fileName)
{
    FILE *fp = fopen(fileName,"r");
    if (fp!=NULL)
    {
        fseek (fp, 0, SEEK_END);
        int size = ftell(fp);
        if (!size) return 1;
    }
    return 0;
}
