#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMMAND_LEN 20
#define DIR_SIZE 10
#define REG_SIZE 11

char shell_output(char* directory) {
    FILE *pf;
    char command[COMMAND_LEN];
    char data[DIR_SIZE];
    char dir[] = "directory", reg[] = "ASCII text";
    
    char fileCommand[9] = "file -b ";
    strcat(fileCommand, directory);
    
    // Execute a process listing
    sprintf(command, fileCommand); 
 
    // Setup our pipe for reading and execute our command.
    pf = popen(command,"r"); 
 
    if(!pf)
    {
      fprintf(stderr, "Could not open pipe for output.\n");
      return '\0';
    }
 
    // Grab data from process execution
    fgets(data, DIR_SIZE , pf);
    pclose(pf);
    // Print grabbed data to the screen.
    //fprintf(stdout, "%s\n",data); 
    if (strcmp(data, dir) == 0)
    {
        printf("SOY DIR\n");
        return 'd';
    }

    else
    {
        pf = popen(command,"r");
        char data1[REG_SIZE];

        fgets(data1, REG_SIZE , pf);

        printf("marico %s\n", data1);
        if (strcmp(data1, reg) == 0){
            printf("SOY FILE\n");
            return 'r';
        }

        else
            return '\0';
    }

    if (pclose(pf) != 0)
    {
        fprintf(stderr," Error: Failed to close command stream \n");
        return '\0';
    }
 
}