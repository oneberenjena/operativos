/*
  shelloutput.c

  Autores: - Benjamin Amos #12-10240
           - Roberto Camara #11-10235
  
  Ult Modificacion: 22/06/15
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randrange(N) rand() / (RAND_MAX/(N) + 1)
#define DIR_SIZE 10
#define REG_SIZE 11
#define TEXT_SIZE 512
#define MAX_M 19
#define MAX_N 9
#define PIPE_BUFFER 1024

extern int* random_number(int n, int max);
extern char shell_outputFile(char* directory);