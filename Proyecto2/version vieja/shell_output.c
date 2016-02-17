/*
  shell_output.c

  Archivo que contiene un metodo que permite obtener
  la salida estandar de un comando UNIX y almacenarlo en
  una variable, asi como un metodo que permite obtener la
  cantidad de caracteres que contiene un archivo.

  Autores: - Benjamin Amos #12-10240
           - Roberto Camara #11-10235
  
  Ult Modificacion: 16/06/15
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DIR_SIZE 10
#define REG_SIZE 11
#define TEXT_SIZE 512

char shell_outputFile(char* directory) {
	FILE *pf;
	char *command;
	command = malloc(sizeof(char)*(sizeof(directory)+8));
	char data[DIR_SIZE];
	char dir[] = "directory";
	char reg[] = "ASCII text";  
	
	char fileCommand[] = "file -b ";
	strcat(fileCommand, directory);
	// Execute a process listing
	sprintf(command, "%s" ,fileCommand); 

	// Setup our pipe for reading and execute our command.
	pf = popen(command,"r"); 
 
	if(!pf)
	{
	  fprintf(stderr, "Could not open pipe for output.\n");
	  free(command);
	  return '\0';
	}
 
	// Grab data from process execution
	fgets(data, DIR_SIZE , pf);
	pclose(pf);

	// Print grabbed data to the screen.
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
			//free(command);
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

int file_size(char *file){

	FILE *pf;
	char ch;
	int size = 0;

	pf = fopen(file, "r");

	while (fgetc(pf) != EOF)
		size++;

	fclose(pf);
	return size;
}