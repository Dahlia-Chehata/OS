#include "commands.h"
#include "command_parser.h"
#include "environment.h"
#include "file_processing.h"
#include"variables.h"

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define Batch 1
#define Interactive 0

int mode;
void shell_loop();
pid_t execute(pid_t pid,char**parsed,char *command);
char* remove_backslash(char*s1);

int main(int argc, char *argv[])
{
    setup_environment();
    if( argc > 1 )
    {
        mode=Batch;
        batchPath = argv[1] ;
        if( access(batchPath, F_OK ) == -1 )
        {
            perror("Invalid batch File\n");
            return 0;
        }
    }
    else
        mode= Interactive;
    shell_loop();
    return 0;
}
/**
 responsible for forking process
*/
pid_t execute(pid_t pid,char**parsed,char *command)
{
    pid = fork();
    int status;
    if (pid==0)
    {
        if (checkifEqual(parsed[argumentSize-1],"&")) //background
            parsed[argumentSize-1]=NULL;
        char* args[ArgumentMaxSize];
        int i;
        for(i=0; parsed[i]!=NULL; i++)
            args[i] = parsed[i];
        args[i] = NULL;
        execv(command,args);
    }
    else
    {
        if (!checkifEqual(parsed[argumentSize-1],"&")) //foreground
        {
            do
            {
                waitpid(pid, &status, WUNTRACED);
                //The status of any child processes specified by pid that are stopped, and whose status
                //has not yet been reported since they stopped, shall also be reported to the requesting process.
            }
            while( !WIFEXITED(status) && !WIFSIGNALED(status));
            //WIFEXITED(status) returns true if child terminated normally
            //WIFSIGNALED(status) returns true if the child process was terminated by a signal.
        }
    }
    return pid;
}
char* remove_backslash(char * s1)
{
    char *s2;
    char *p;
    s2 = strdup (s1);   //  Make a copy of the original.
    p = strchr (s2, '\\');
    while (p)
    {
        strcpy (p, p+1);
        p = strchr (s2, '\\');  //  Check for another backslash.
    }
    return s2;
}
void shell_loop()
{
    char input[inputSize];
    pid_t pid = -1;
    signal(SIGCHLD,signalHandler);
    FILE* batchFileReader =read_batch_file();
    while(true)
    {
        if(mode==Interactive)
        {
            printf("SHELL> ");
            if(fgets(input, inputSize, stdin)== NULL)  break;
        }
        else
        {
            if(fgets(input, inputSize, batchFileReader) == NULL) break;
            printf("%s",input);
        }

        char*temp=remove_backslash(input);
        memset(input,'\0',sizeof input);
        strcpy(input,temp);
        input[strlen(input)-1] = '\0';
        if(input[strlen(input)-2]=='\r')input[strlen(input)-2] = '\0';
        FILE *filewriter= write_in_history_file(input);
        if(strlen(input)>maxInputSize)
        {
            printf("ERROR!! : very long command line\n");
            continue;
        }
        char** parsed = parse_command(input,' ');
        if(parsed==NULL) continue; // if Comment skip
        if(argumentSize==0)continue; // empty line case
        if(checkifEqual(parsed[0],"exit")) break;

        if(checkifEqual(parsed[0], "export"))
        {
            char*tp;
            tp=(char*)malloc(ArgumentMaxSize* (sizeof(char)));
            strncpy(tp, input + strlen("export"), strlen(input) - strlen("export"));
            free(parsed);
            parsed = parse_command(tp,' ');
            continue;
        }
        if(checkifEqual(parsed[0],"cd"))
        {
            cd(parsed);
            continue;
        }
        if (checkifEqual(parsed[0],"ls") || checkifEqual(parsed[0],"cp")||checkifEqual(parsed[0],"cat")
                ||checkifEqual(parsed[0],"mv") ||checkifEqual(parsed[0],"printenv"))
        {
            if (!validate(getenv("PATH"),PATH))
            {
                printf("Command is available in \'/bin/command\'\n");
                printf("The command could not be located because \'/bin\' ");
                printf("is not included in the PATH environment variable.\n");
                printf("ERROR: command not found\n");
                continue;
            }
        }
        if(checkifEqual(parsed[0], "history") && parsed[1]==NULL)
        {
            read_from_history_file();
            filewriter=open_history_file();
            continue;
        }
        char* command;
        command =(char*)malloc(ArgumentMaxSize* (sizeof(char)));
        command = getCommand(srcs, parsed[0]);
        if(checkifEqual(command,"Invalid"))
        {
            printf("ERROR!! : invalid command\n");
            continue;
        }
        pid=execute(pid,parsed,command);
    }
}
