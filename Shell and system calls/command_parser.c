#include "command_parser.h"
#include "environment.h"
#include "variables.h"
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int ARG;
/**
-check if character exits in string
*/
bool contains (const char*cmd,char c)
{
    for (int i=0; i<strlen(cmd); i++)
        if (cmd[i]==c) return true;
    return false;
}
/**
-check if character is digit
*/
bool isNum (char c)
{
  if( (c>='1' && c<='9')) return true;
  return false;
}
/**
	- This function is responsible for importing all details of the command
    - Using helper functions, it sets environments variables wth their values
    - parses the command with split over space/tab for instruction and over : for path
    - considers all parsing special cases, example: many spaces in  "ls     -a"
	- set the arguments size
    - return: double pointer to parsed data
*/
char**parse_command(const char* command,char split)
{
    if (command[0]=='#') return NULL; // comment case
    char* op,*reform ;
    op=(char*)malloc(ArgumentMaxSize * (sizeof(char)));
    reform=(char*)malloc(ArgumentMaxSize * (sizeof(char)));
    memset(reform,'\0',sizeof (reform));
    strncpy(op,command,4);

    char**parsed;
    if ((contains(command,'=') && contains(command,'\"')) || (checkifEqual(op,"echo")))
        parsed = echoSplit(command,split);
    else
    {
        if (split==' ')
        {
            parsed = echoSplit(command,split);
            ReplaceVarsWithVals(parsed);
            int i=0;
            while(i<ARG-1)
            {
                strcat(reform,parsed[i]);
                strcat(reform," ");
                i++;
            }
            strcat(reform,parsed[i]);
        }
        else
            reform = command;
        parsed = Splitter(reform,split);
    }
    if (split==' ') //replacing the environment variables with their values in case of $
    {
        ReplaceVarsWithVals(parsed);
        argumentSize = ARG;
    }
    if (split==':') pathLength=ARG;
    return parsed;

}
/**
-splitting the command on spaces
*/
char** Splitter(const char*command,char split)
{
    char**parsed;

    parsed =(char**)malloc(argumentsNumber * (sizeof(char*))); //allocates array of strings in memory
    memset(parsed,NULL, argumentsNumber * sizeof (char*)); //initializing with null
    int i;
    for (i=0; i<argumentsNumber; i++)
    {
        parsed[i] =(char*)malloc(ArgumentMaxSize * (sizeof(char))); //allocate space for each string/argument
        memset(parsed[i],'\0',ArgumentMaxSize * (sizeof(char)));
    }
    int arg = 0, index = 0, character = 0, inputSize = strlen(command);
    while (index< inputSize)
    {
        if (index<inputSize  && command[index]=='\"') index++;

        while (index< inputSize  && command[index]!= split && command[index]!='\t' && command[index]!='\"')
            parsed[arg][character++]=command[index++];

        while (index< inputSize &&(command[index]== split || command[index]=='\t'))
            index++;
            if(setEnvironmentsVars(parsed,arg))continue;
        arg++,character=0;
    }
    parsed[arg]= NULL; // denoting the end of command
    ARG=arg;
    return parsed;
}
/**
splitting the command on spaces unless ther is quotations
*/
char**echoSplit (const char*command,char split)
{
    char**parsed;

    parsed =(char**)malloc(argumentsNumber * (sizeof(char*))); //allocates array of strings in memory
    memset(parsed,NULL, argumentsNumber * sizeof (char*)); //initializing with null
    int i;
    for (i=0; i<argumentsNumber; i++)
    {
        parsed[i] =(char*)malloc(ArgumentMaxSize * (sizeof(char))); //allocate space for each string/argument
        memset(parsed[i],'\0',ArgumentMaxSize * (sizeof(char)));
    }
    int arg = 0, index = 0, charact = 0, inputSize = strlen(command);
    while (index< inputSize)
    {
        while (index< inputSize  && command[index]!= split && command[index]!='\t')
        {
            if (index<inputSize  && command[index]=='\"')
            {
                index++;
                int start=index;
                while (command[index]!='\"') index++;
                char* temp ;
                temp=(char*)malloc(ArgumentMaxSize * (sizeof(char)));
                strncpy(temp,command+start,index-start);
                strcat(parsed[arg],temp);
                index++;
            }
            else if (index<inputSize)
                parsed[arg][charact++]=command[index++];
        }
        while (index< inputSize &&(command[index]== split || command[index]=='\t'))
            index++;
            if(setEnvironmentsVars(parsed,arg))continue;
        arg++,charact=0;
    }
    ARG=arg;

    return parsed;
}

