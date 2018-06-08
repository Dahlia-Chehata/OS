#include "environment.h"
#include "command_parser.h"
#include "variables.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> //getenv setenv
/**
 -this function removes $ from the environment variable name
*/
void remove_$ (char* envName)
{
    char* temp;
    temp = (char*) malloc(ArgumentMaxSize*(sizeof(char)));
    int idx = 0;
    int i;
    for(i=1; envName[i]!='\0'; i++)
        temp[idx++] = envName[i];
    strcpy(envName,temp);
}
/**
  -this function is responsible for getting the environment variable corresponding value that
   has been already set ex:: for echo $x case
  - return : char*
*/
char* getEnvironmentVars(char* envName)
{
    char* solution;
    solution =(char*) malloc(ArgumentMaxSize* (sizeof (char)));
    if (envName[0]=='$') //remove $
        remove_$(envName);
    solution = getenv(envName);
    if(solution[0]!='$') return solution;
    return getEnvironmentVars(solution);
}
/**
  -this function responsible for parsing the expression x=value and setting value for the environment
   variable chosen
  - return : boolean if 1 continue the loop for other arguments
*/
int setEnvironmentsVars(char**parsed,int arg)
{
    char *environmentVars, *environmentVals, *tmp,*s1;
    environmentVars = (char*)malloc(ArgumentMaxSize * (sizeof (char)));
    environmentVals =(char*)malloc(ArgumentMaxSize * (sizeof (char)));
    tmp =(char*)malloc(ArgumentMaxSize * (sizeof (char)));
    s1 =(char*)malloc(ArgumentMaxSize * (sizeof (char)));
    int idx1=0,idx2=0,idx3=0,i,j;
    for (i=0; parsed[arg][i]!='\0' && parsed[arg][i]!='='; i++)
        environmentVars[idx1++]=parsed[arg][i];
   if(parsed[arg][i]!='\0' && parsed[arg][i]=='=')
   {
        for (j=i+1; parsed[arg][j]!='\0' &&(parsed [arg][j]>'9'||parsed [arg][j]=='$'); j++)
            tmp[idx3++]=parsed[arg][j];
        if(idx3) s1=getEnvironmentVars(tmp);
        for (i=0; i<idx3; i++)
            environmentVals[idx2++]=s1[i];
        idx3=0;
        for(i=j; parsed[arg][i]!='\0'; i++)
            s1[idx3++]=parsed[arg][i];
        strcat(environmentVals,s1);
       setenv(environmentVars, environmentVals, 1);
    return 1;
}
return 0;
}
/**
-this function replaces environments variables with their values in "parsed"
*/
void ReplaceVarsWithVals(char**parsed)
{
    int i, idx=0;
    char* envName;
    envName = (char*) malloc(ArgumentMaxSize*(sizeof(char)));
    for (i=0; parsed[i]!=NULL; i++)
    {
         int j;
          for (j=0;j<parsed[i][j]!='\0';j++)
          {
             if (parsed[i][j]=='$')
             { int start=j;
               while ( parsed[i][j]!='\0' && !isNum(parsed[i][j]) && parsed[i][j]!=' '
               && parsed[i][j]!='\t'&& parsed[i][j]!='\\')
                  envName[idx++] = parsed[i][j++];
               char*replace;
               replace = (char*) malloc(ArgumentMaxSize*(sizeof(char)));
               replace=getEnvironmentVars(envName);
                 int end=j-1;
                char *first,*last;
                first = (char*) malloc(ArgumentMaxSize*(sizeof(char)));
                last= (char*) malloc(ArgumentMaxSize*(sizeof(char)));
                 strncpy(first,parsed[i],start);
                 strncpy(last,parsed[i+end+1],strlen(parsed[i]-end));
                 memset(parsed[i],'\0',sizeof(parsed[i]));
                 strcat(parsed[i],first);
                 strcat(parsed[i],replace);
                 strcat(parsed[i],last);
             }
          }
    }
}
/**
 - This function sets all paths as for history file , log file .
*/
void setup_environment( void )
{
    PATH = getenv("PATH");
    HOME = getenv("HOME");
    srcs = parse_command(PATH, ':');
    workingDir = getenv("PWD");
    historyPath=(char*) malloc (ArgumentMaxSize * sizeof(char));
    logPath=(char*) malloc (ArgumentMaxSize * sizeof(char));
    strcpy(historyPath,workingDir);
    strcpy(logPath,workingDir);
    strcat(historyPath,"/history.txt");
    strcat(logPath,"/log.txt");
}
