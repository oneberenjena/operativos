/*
  process.c

  Archivo que contiene la funcion de procesamiento principal de los
  archivos y directorios, y una funcion que permite obtener lo que
  se encuentra dentro de un archivo regular.

  Autores: - Benjamin Amos #12-10240
           - Roberto Camara #11-10235
  
  Ult Modificacion: 16/06/15
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "random_number.h"
#include <fcntl.h>

#define MAX_M 19
#define PIPE_BUFFER 1024

char * file_cat(char *file, int size) {
 
	FILE *pf;
	char ch;
	int nChar = 0, index = 0;

	pf = fopen(file, "r");
	
	char *text = (char *)malloc(size*sizeof(char));

	while((ch = fgetc(pf)) != EOF){
		text[index] = ch;
		++index;
	}
	text[index] = '\0';

	fclose(pf);
	return text;
}

void process_data(int* directoriesToDo, int n, int m, char* dir, char* output)
{	
	pid_t *PID = (pid_t *) malloc(sizeof(pid_t)*n);
	int i,j;
	int fd[2];
	pipe(fd);
	char *text;
	int nbytes;
	char readbuff[PIPE_BUFFER];
	char nil[] = "null";

	for (i = 0; i < n; ++i)
	{
    	if ((PID[i] = fork()) == 0)
    	{
    		// Se cierra la lectura de los procesos hijos en el pipe
    		close(fd[0]);

    		int len;
    		struct dirent *pDirent;
    		char *dirToDo = malloc(sizeof(char)*2);
    		DIR *pDir, *pDir1;
    		int nFiles = 0;
    		

    		dirToDo[0] = directoriesToDo[i] + '0';
    		dirToDo[1] = '/';

    		// Concatenar el nombre del directorio con su respectivo directorio
    		strcat(dir, dirToDo);
   			pDir = opendir(dir);
   			
   			// En caso de que el directorio sea invalido o no se pueda acceder
   			if (pDir == NULL) 
    		{
    			printf ("No se puede abrir el directorio '%s' o no existe\n", dir);
    			exit(0);
    		}
    		// Se seleccionan aleatoriamente los archivos a abrir
    		int *files_toDo; 
    	    files_toDo = random_number(m, MAX_M);
    	    
    	    char *dirfile;
    	    // Verificamos que estamos abriendo un directorio
    	    if (shell_outputFile(dir) == 'd')
    	    {	    		
	    		// Obtendremos la cantidad de archivos regulares que hay en el directorio
	    		while ((pDirent = readdir(pDir)) != NULL) 	
	    		{
	    			// Identificamos el archivo actual en el directorio 
	    			dirfile = malloc(sizeof(char*)*(sizeof(dir)+sizeof(pDirent->d_name)));    	 		
    	 			strcpy(dirfile, dir);
    	 			strcat(dirfile, pDirent->d_name);

    	 			// Contamos cuantos archivos regulares tiene el directorio
    	 			if (shell_outputFile(dirfile) == 'r')	
    	 				nFiles++;

    	 			free(dirfile);
    			}    		

    			rewinddir(pDir); // Regresamos el apuntador del directorio al primer archivo

    			/*
    			*
    			* PROCESO DE ESCRITURA EN CADA PIPE PROCESO HIJO-PADRE
    			*
    			*/
    	    	
    	    	char *dirRand;

    	    	dirRand = malloc(sizeof(char)*(sizeof(dir)+3));
    	    	char **filesRandom;
				filesRandom = malloc(sizeof(char*)*((strlen(dir)+2)*m));
    	    	char filenow[2];
 
    	    	for(j = 0; j < m; j++)
    	    	{
    	    		strcpy(dirRand, dir);
    	    		sprintf(filenow,"%d",files_toDo[j]);
    	    		strcat(dirRand, filenow);
    	    		filesRandom[j] = (char *)malloc(strlen(dirRand));
    	    		strcpy(filesRandom[j],dirRand);    	    	
    	    	}
	
    	    	int sizetext;

    			// Caso en el que se piden mas archivos de los que hay
    			if (m > nFiles)
    			{
    				while ((pDirent = readdir(pDir)) != NULL)
    				{	
    					
    					dirfile = malloc(sizeof(char)*(sizeof(dir)+sizeof(pDirent->d_name)));    	 		
    	 				strcpy(dirfile, dir);
    	 				strcat(dirfile, pDirent->d_name);	
						
    					if (shell_outputFile(dirfile) == 'r')
    					{
    						
    						sizetext = file_size(dirfile);
    						//text = (char *)malloc(sizeof(char)*sizetext);
    						text = file_cat(dirfile, sizetext);    				
    						printf("envio al padre %s\n", text);
    						write(fd[1], text, strlen(text)+1);
    					}

    					free(dirfile);
    				}
    				exit(nFiles);
    			}

    			
    			// Caso en el que se puede cumplir 	con la exigencia de archivos
    			else
    			{	
    				int sizefiles = 0;

    				while ((pDirent = readdir(pDir)) != NULL)
    				{
    					
    					dirfile = malloc(sizeof(char)*(sizeof(dir)+sizeof(pDirent->d_name)));    	 		
    	 				strcpy(dirfile, dir);
    	 				strcat(dirfile, pDirent->d_name);
    	 				printf("\n");
    					if (shell_outputFile(dirfile) == 'r')
    					{
    						for(j = 0; j < m; ++j)
    						{
    							//printf("files %s vs dir %s\n", filesRandom[j], dirfile );
    							if (strcmp(filesRandom[j], dirfile) == 0)
    							{
    								sizetext = file_size(dirfile);
    								text = (char *)malloc(sizeof(char)*sizetext);
    								text = file_cat(dirfile, sizetext);
    								//printf("envio al padre %s\n", text);
    								write(fd[1], text, strlen(text)+1);
    								//printf("termine vuelta en directorio %s\n", dirfile);
    								free(dirfile);
    								break;
    							}
    						}
    					}

    					else{
    						//printf("NO SOY REGULAR SOY CHIGUIRE y termine vuelta en directorio %s\n", dirfile);
    						free(dirfile);
    					}

    				}
    			}
    		}

    		else 
    		{
    			printf("Directorio invalido: %s\n", dir);
    			exit(0);
    		}

    		closedir (pDir);	
    	
    	exit(0);
    	}

    	else if (PID[i] < 0) perror("fork: ");
    }

    // Se cierra la escritura del proceso padre en el pipe
    close(fd[1]);
    
    int status;
	//for (i = 0; i < n; ++i)
    	//wait(&status);

    for (i = 0; i < n; i++){
    	waitpid(PID[i], &status, 0);
    	printf("lei al hijo %ld\n", (long)PID[i]);
    	nbytes = read(fd[0], readbuff, sizeof(readbuff));
    	printf("lo que lei al final %s\n", readbuff);	
    	
    }

    //fopen
}

