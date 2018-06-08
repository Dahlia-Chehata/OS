#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_
#include <stdio.h>

/**
	history file basic functions' prototypes
*/
FILE* open_history_file();
void read_from_history_file();
FILE* write_in_history_file();
/**
	this method writes in the log file when the  process child terminates
*/
void signalHandler();
/**
	this method reads commands in batch file
*/
FILE* read_batch_file();

#endif // FILE_PROCESSING_H_
