/*
  random_number.c

  Archivo que contiene la funcion creada para generar
  un numero aleatorio dado un rango y un maximo

  Autores: - Benjamin Amos #12-10240
           - Roberto Camara #11-10235
  
  Ult Modificacion: 13/06/15
*/

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
