#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define randrange(N) rand() / (RAND_MAX/(N) + 1)

extern int* random_number(int n, int max);