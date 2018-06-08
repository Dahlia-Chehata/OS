#include "file_processing.h"
#include "Elements_Threading.h"
#include "Rows_Threading.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

const int maxLength=100,maxThreads=46620;
char*inputFile1,*inputFile2,*outputFile1,*outputFile2;

void setup();
bool checkExtension(char*fileName);
char* modifyFileName(char* fileName,char*extension);
void displayData (struct timeval start, struct timeval stop,int threads,int id);
void performMethod1();
void performMethod2();
/**
 read files,execute multithreaded multiplication and write output to files
*/
int main(int argc,char*argv[])
{
    setup();
    random_generator();
    if (argc>1)inputFile1= argv[1];
    if (argc>2)inputFile2= argv[2];
    if (argc>3)
    {
        outputFile1= modifyFileName(argv[3],"_1");
        outputFile2= modifyFileName(argv[3],"_2");
    }
    if (!readFile(inputFile1,1) ||!readFile(inputFile2,2)) exit(-1);
    output_matrix=(long long**) malloc (row_out*sizeof (long long*));
    int i;
    for (i=0; i<row_out; i++)
        output_matrix[i]=(long long*)malloc (col_out*sizeof (long long));
    performMethod1();
    performMethod2();
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
/**
 sets up the inout and output files
*/
void setup()
{
    inputFile1 ="a.txt";
    inputFile2 ="b.txt";
    outputFile1 ="c_1.txt";
    outputFile2 ="c_2.txt";
}
/**
this function handles file extensions".txt"
*/
bool checkExtension(char*fileName)
{
    char*temp=(char*)malloc(maxLength*sizeof(char));
    strncpy(temp,fileName+strlen(fileName)-4,4);
    int i;
    char* compare=".txt";
    for(i=0; i<4; i++)
        if (temp[i]!=compare[i])
            return 0;
    return 1;
}
/**
-modifies filenames ending with ".txt"
*/
char* modifyFileName(char* fileName,char*extension)
{
    char* newName;
    newName= (char*)malloc(maxLength*sizeof(char));
    if (checkExtension(fileName))
    {
        strncpy(newName,fileName,strlen(fileName)-4);
        strcat(newName,extension);
        strcat(newName,".txt");
    }
    else
    {
        strncpy(newName,fileName,strlen(fileName));
        strcat(newName,extension);
    }
    return newName;
}
/**
prints Data concerning time and number of threads to console for each method
*/
void displayData (struct timeval start, struct timeval stop,int threads,int id)
{
    printf("Mehod %d:\n",id);
    printf("Number of Thread = %d\n", threads);
    printf("Number of Microseconds taken = %lu\n", stop.tv_usec - start.tv_usec);
    printf("Number of Seconds taken = %lu\n\n", stop.tv_sec - start.tv_sec);
}
/**
performs multiplication using threading for each row
*/
void performMethod1()
{
    struct timeval stop, start;
    if (row_out<=maxThreads)
    {
        gettimeofday(&start, NULL);
        if (threadedRows()==-1) return;
        gettimeofday(&stop, NULL);
        displayData(start,stop,row_out,1);
        if (!writeToFile(outputFile1))
         perror("METHOD 1 failed in writing to file");
    }
    else
    {
        printf("METHOD 1 ERROR: MAX NUMBER OF THREADS REACHED !!\n");
    }

}
/**
performs multiplication using threading for each element
*/
void performMethod2()
{
    struct timeval stop, start;
    if (row_out*col_out <=maxThreads)
    {
        gettimeofday(&start, NULL);
        if (threadedElements()==-1) return;
        gettimeofday(&stop, NULL);
        displayData(start,stop,row_out*col_out,2);
        if (!writeToFile(outputFile2))
            perror("METHOD 2 failed in writing to file");
    }
    else
    {
        printf("METHOD 2 ERROR: MAX NUMBER OF THREADS REACHED !!\n");
    }
}
