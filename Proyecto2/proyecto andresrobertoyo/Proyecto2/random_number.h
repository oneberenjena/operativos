#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randrange(N) rand() / (RAND_MAX/(N) + 1)
#define DIR_SIZE 10
#define REG_SIZE 11
#define TEXT_SIZE 512
#define MAX_M 19
#define PIPE_BUFFER 1024

extern int* random_number(int n, int max);
extern char shell_outputFile(char* directory);