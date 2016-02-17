/*********************************************
**********************************************

  Proyecto 2 - Sistemas de Operacion 1

  Cuerpo principal del programa

  Autores: - Andrés Guerrero  	10-10330
           - Daniel Marín		10-10419

*********************************************  
*********************************************/

#include "random_number.h"
#include <string.h>
#include <unistd.h>
#define MAX_NUM 9
#define ACTUAL "./"

int main(int argc, char const *argv[])
{
	/* Declaracion de Variables */
	int n, m, *dirToWork;
	char *dir, *resolve;

	/* Inicializacion de variables */
	dir = (char *)malloc(sizeof(char)*strlen(argv[2]));
	
	/*Valida que la entrada sea correcta (cumpla con el minimo de requerimientos para ejecutar el programa)*/
	if (argc < 4 && argc > 6) {
		if (argc > 6){
		  	printf(">> Muchos argumentos, fin del programa.\n");
		}
		else{
		  	printf(">> Pocos argumentos, fin del programa.\n");
			return EXIT_FAILURE;
		}
	} 
	else if (argc == 5 && (strcmp(argv[1], "-d") == 0) ) {
		printf(">> Error en la entrada. Flag -d usado, pero directorio no especificado\n");
		return EXIT_FAILURE;
	} 
	else if (argc == 6 && (strcmp(argv[1], "-d") != 0)) {
		printf(">> %s no se reconoce como un flag. Fin del programa.\n", argv[1]);
		return EXIT_FAILURE;
	}

	/*Comprobar si se especifico o no un directorio*/
	if (strcmp(argv[1], "-d") == 0){
		strcpy(dir, argv[2]);
		strcpy(resolve, argv[5]);

		m = atoi(argv[4]);
		n = atoi(argv[3]); 
		dirToWork = random_number(n, MAX_NUM);

		process_data(dirToWork, n, m, dir, resolve);
	}
	else{
		strcpy(dir, ACTUAL);
		strcpy(resolve, argv[3]);
		
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		dirToWork = random_number(n, MAX_NUM);
		
		process_data(dirToWork, n, m, &dir, resolve);
	}

	/*Salida de datos*/
	return 1;
}