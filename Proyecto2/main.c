/*
  miCuento.c

  Archivo que contiene la funcion principal de miCuento

  Autores: - Benjamin Amos #12-10240
           - Roberto Camara #11-10235
  
  Ult Modificacion: 22/06/15
*/

#include "random_number.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int n, m;
	int *directoriesToDo;
	char *dir;
	char *output;
	const char actual[3] = "./";
	dir = (char *)malloc(sizeof(char)*strlen(argv[2]));
	
	// Si el programa es invocado sin el flag '-d'
	if (atoi(argv[1]) < 10 && 0 < atoi(argv[1]))
	{
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		strcpy(dir, actual);
		strcpy(output, argv[3]);
		directoriesToDo = random_number(n, MAX_N);
		process_data(directoriesToDo, n, m, dir, output);

	}
	// Si el programa es invocado con el flag '-d'
	else if (strcmp(argv[1], "-d") == 0)
	{
		n = atoi(argv[3]); 
		m = atoi(argv[4]);
		strcpy(dir, argv[2]);
		if (dir[strlen(dir)-1] != '/')
		{	
			printf(" before %s\n", dir);
			char r[] = "/\0";
			dir = realloc(dir, strlen(argv[2])+2);
			strcat(dir, r);
			printf("after %s\n", dir );
		}
			
		strcpy(output, argv[5]);
		directoriesToDo = random_number(n, MAX_N);
		process_data(directoriesToDo, n, m, dir, output);
	}

	// En el caso de que la opcion sea invalida
	else
	{
		printf("miCuento: opcion invalida -- '%c'\nLa sintaxis es: \
miCuento [-d directorio] <n> <m> <output>\n<n> debe ser positivo y\
 menor que 10\n<m> debe ser positivo y menor que 20", argv[1][1]);
		return 1;
	}

	return 0;
}