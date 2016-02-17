#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc, char *argv[]) {
	struct stat statbuf;
	if (argc != 2) {
	  fprintf(stderr, "Usage: %s nombre_de_archivo\n", argv[0]);
	  exit(1);
	}
	
	if (stat([argv[1]), &statbuf) == ­1) {
	   fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", argv[1], strerror(errno));
	   exit(1);
	}

	if (statbuf.st_mode & S_IFDIR)
	  printf("%s es un directorio\n", argv[1]);
	else
	  printf("%s no es un directorio\n", argv[1]);
	exit(0);
	}
}	
