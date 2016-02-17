/*

*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include "random_number.h"

char *file_cat(char **file, int size, int m) {
 
    FILE *pf;
    char ch, *text;
    int nChar = 0, index = 0, j, sizeOf = 100000;

    text = (char *)malloc(size*sizeof(char));
    
    for (j=0; j<m; j++){
        if (shell_outputFile(file[j]) == 'r'){
            pf = fopen(file[j], "r");
         
            while((ch = fgetc(pf)) != EOF){
                text[index] = ch;
                ++index;
            }
            
            fclose(pf);
            
        }
    }
    return text;
}

void process_data(int* directoriesToDo, int n, int m, char* dir, char* output) {    
    
    // Inicializaciones
    pid_t *PID = (pid_t *) malloc(sizeof(pid_t)*n);
    int i, j, nbytes;
    int fd[2];
    pipe(fd);
    char *text;
    char readbuff[PIPE_BUFFER];
    FILE* salida;

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
                exit(1);
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
                           
                           sizetext = file_size(filesRandom, m);
                           text = (char *)malloc(sizeof(char)*sizetext);
                           text = file_cat(filesRandom, sizetext, m); 
                           write(fd[1], text, strlen(text)+1);
                        }

                        else
                        {
                            char nothing[] = "  ";
                            write(fd[1], nothing, strlen(nothing)+1);
                        }

                        free(dirfile);
                    }
                    printf("nfiles %d\n", nFiles );
                    exit(nFiles);
                }

                
                // Caso en el que se puede cumplir  con la exigencia de archivos
                else
                {   
                    int sizefiles = 0;

                    while ((pDirent = readdir(pDir)) != NULL)
                    {
                        
                        dirfile = malloc(sizeof(char)*(sizeof(dir)+sizeof(pDirent->d_name)));               
                        strcpy(dirfile, dir);
                        strcat(dirfile, pDirent->d_name);
                        if (shell_outputFile(dirfile) == 'r')
                        {
                            for(j = 0; j < m; ++j)
                            {
                                if (strcmp(filesRandom[j], dirfile) == 0)
                                {
                                    sizetext = file_size(filesRandom, m);
                                    text = (char *)malloc(sizeof(char)*sizetext);
                                    text = file_cat(filesRandom, sizetext, m);
                                    write(fd[1], text, strlen(text)+1);
                                    free(dirfile);
                                    break;
                                }

                                else
                                {
                                    char nothing[] = "  ";
                                    write(fd[1], nothing, strlen(nothing)+1);
                                }

                            }
                        }

                        else{
                            free(dirfile);
                        }

                    }
                }
            }

            else 
            {
                printf("Directorio invalido: %s\n", dir);
                exit(1);
            }

            closedir (pDir);    
            exit(0);
        }

        else if (PID[i] < 0) perror("fork: ");
    }

    // Se cierra la escritura del proceso padre en el pipe
    close(fd[1]);
    
    int status;
    salida = fopen(output, "w+");

    
    for (i = 0; i < n; i++){
        waitpid(PID[i], &status, 0);
        if (status != 1)
        {
            nbytes = read(fd[0], readbuff, sizeof(readbuff));
            fprintf(salida, "%s", readbuff);
        }   
    }


    fclose(salida);
}
