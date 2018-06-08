#include "commands.h"
#include "command_parser.h"
#include"variables.h"
#include <unistd.h>  //for access() method
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include <dirent.h>
/**
 this fuction compares 2 commands and check if equal
 args : str1 , str2
 return : boolean value
 */
int checkifEqual(char* str1,char*str2)
{
    if (strlen(str1)!=strlen(str2)) return 0;
    int i;
    for (i=0; i<strlen(str1); i++)
    {
        if (str1[i]!=str2[i])
            return 0;
    }
    return 1;
}
/**
this function handles the "cd " command
args: parsed command represented by 2d pointer to char
*/
void cd(char** parsed)
{
    if (argumentSize>2)
        printf("ERROR! invalid arguments to cd\n");
    if (argumentSize==2 && parsed[1][0]=='~') //home directory
    {
        char temp[ArgumentMaxSize];
        char* home = getenv("HOME");
        strcpy(temp,home);
        int idx=strlen(home),i;
        for (i=1; parsed[1][i]!='\0'; i++)
            temp[idx++]=parsed[1][i];
            temp[idx]='\0';
        strcpy(parsed[1],temp);
    }
    if (argumentSize==1)
        parsed[1]="/";
    if(chdir(parsed[1])==-1) perror("");
}
/**
validate a given path
*/
int validate(char* path , char*env)
{
    if (!checkifEqual(path,env)) return 0;
    return 1;
}
/**
-This method checks which file has the given command using access () method and binary files
- returns the path of the command if found or invalid if not
*/
char* getCommand(char**src,char*cmd)
{   //check for file existence
    if (access(cmd,F_OK)!=-1) return cmd; //bin/ls -l
    char* ret;
    ret=(char*)malloc(ArgumentMaxSize * sizeof(char));
    int found =0;
    int i;
    for (i=0; src[i]!=NULL; i++)
    {
        char path[ArgumentMaxSize];
        strcpy(path,src[i]);
        strcat(path,"/");
        strcat(path,cmd);
        if (access(path,F_OK)!=-1)
        {
            strcpy(ret,path);
            found = 1;
            break;
        }
    }
    if(found) return ret;
    return "Invalid";
}
