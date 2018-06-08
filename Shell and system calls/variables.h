#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

extern int const argumentsNumber , ArgumentMaxSize ,inputSize, maxInputSize  ;
extern int argumentSize,pathLength;
extern char* historyPath,*logPath,*batchPath ,*PATH,**srcs,*HOME,*workingDir,*pos,*argpos;


void updateVars ();
void setVariables();


#endif // VARIABLES_H_
