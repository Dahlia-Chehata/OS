#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H
#include <stdbool.h>
/**
	/**
	- This function is responsible for importing all details of the command
    - Using helper functions, it sets environments variables wth their values
    - parses the command with split over space/tab for instruction and over : for path
	- considers all parsing special cases, example: many spaces in  "ls     -a"
	- set the arguments size
    - return: double pointer to parsed data
*/
char** parse_command(const char* command ,char split);
/**
-splitting the command on spaces
*/
char** Splitter(const char* command,char split);
/**
splitting the command on spaces unless ther is quotations
*/
char** echoSplit(const char* command,char split);

#endif // COMMAND_PARSER_H
