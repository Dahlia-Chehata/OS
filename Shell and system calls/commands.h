#ifndef COMMANDS_H_   /* Include guard */
#define COMMANDS_H_
/**
 compare 2 commands
*/
int checkifEqual(char* str1,char*str2);
/**
	- This function is responsible for implementing the "cd" shell command
*/
void cd(char** parsed );
int validate(char* path , char*env);
/**
    -This method checks which file has the given command using access () method and binary files
    - returns the path of the command if found or invalid if not
*/
char* getCommand(char**src,char*cmd);


#endif // COMMANDS_H_
