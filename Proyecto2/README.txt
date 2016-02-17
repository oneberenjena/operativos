NAME
    miCuento — Busca aleatoriamente en un conjunto de directorios,
     		   un conjunto aleatorio de archivos de texto que se concatenan en un archivo de texto de salida

SYNOPSIS
    miCuento [-d DIRECTORIO] <n> <m> <SALIDA> 

DESCRIPTION
	miCuento busca aleatoriamente en N directorios M archivos regulares aleatorios que contienen texto, concatena los textos de cada archivo regular en uno solo y genera una historia distinta en cada uso, en un solo archivo de SALIDA.

OPTIONS
	
	-d directorio
			Busca los N directorios en el directorio especificado. Si no se especifica, se busca en el directorio actual.

Exit status:
       0      si todo se ejecutó correctamente,

       1      si existen problemas menores (i.e., no se hizo un buen uso del comando),

       2      si el directorio es invalido.

AUTHOR
       Escrito por Benjamin Amos y Roberto Camara.

Sistemas de Operacion I      Junio 2015                  miCuento