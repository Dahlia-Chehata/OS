#include "file_processing.h"
#include "variables.h"
/**history file section*/
FILE* open_history_file()
{
    return fopen(historyPath, "a");
}

void read_from_history_file()
{
    FILE *filereader = fopen(historyPath, "r");
    char command[maxInputSize];
    while(fgets(command, inputSize, filereader) != NULL)
    {
        printf("%s", command);
    }
}
FILE * write_in_history_file(char input[])
{
    FILE *filewriter = fopen(historyPath, "a");
    fprintf(filewriter, "%s\n", input);
    fclose(filewriter);
    return filewriter;
}
/** log file section */
void signalHandler()
{
    FILE *filewriter = fopen(logPath, "a");
    fprintf(filewriter, "%s\n", "Child process was terminated");
    fclose(filewriter);
}
/** CommandsBatch file section */
FILE* read_batch_file()
{
    return fopen(batchPath, "r");
}
