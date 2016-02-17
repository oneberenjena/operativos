/*
  shelloutput.c

  Autores: - Benjamin Amos #12-10240
           - Roberto Camara #11-10235
  
  Ult Modificacion: 22/06/15
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "random_number.h"

int* random_number(int n, int max) {
	int i;
	const int MAX = max;
	int *directories;
	int candidates[MAX];
	srand(time(NULL));  // Crea la semilla del random 
	directories = (int *) malloc(sizeof(int)*n);

	for (i=0; i<MAX; i++)
		candidates[i] = i;

	for (i = 0; i < MAX-1; i++) 
	{
		int c = randrange(MAX-i);
		int t = candidates[i];
		candidates[i] = candidates[i+c];
		candidates[i+c] = t;
	}

	for (i=0; i<n; i++)
		directories[i] = candidates[i] + 1;

	return directories;
}

char shell_outputFile(char* directory) {
	FILE *pf;
	char *command;
	command = malloc(sizeof(char)*(sizeof(directory)+8));
	char data[DIR_SIZE];
	char dir[] = "directory";
	char reg[] = "ASCII text";  
	
	char fileCommand[] = "file -b ";
	strcat(fileCommand, directory);
	sprintf(command, "%s" ,fileCommand); 

	pf = popen(command,"r"); 
 
	if(!pf)
	{
	  fprintf(stderr, "Could not open pipe for output.\n");
	  free(command);
	  return '\0';
	}
 
	fgets(data, DIR_SIZE , pf);
	pclose(pf);

	if (strcmp(data, dir) == 0)
	{
		free(command);
		return 'd';
	}

	else
	{
		pf = popen(command,"r");
		char data1[REG_SIZE];

		fgets(data1, REG_SIZE , pf);

		if (strcmp(data1, reg) == 0)
		{
			return 'r';
		}

		else
		{
			free(command);
			return '\0';
		}
	}

	if (pclose(pf) != 0)
	{
		fprintf(stderr," Error: Failed to close command stream \n");
		free(command);
		return '\0';
	}
 
}

int file_size(char **file, int m){

	FILE *pf;
	char ch;
	int size = 0,i;
	
	for (i=0; i<m; i++){
		if (shell_outputFile(file[i]) == 'r'){
			pf = fopen(file[i], "r");
			while (fgetc(pf) != EOF)
				size++;

			fclose(pf);
		}
	}
	
	return size;
}