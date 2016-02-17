# MAKEFILE proyecto numero 2
# Realizado por Benjamin Amos, Roberto Camara

all: miCuento main.o process.o shell_output.o

miCuento: main.o process.o shell_output.o 
	gcc -c main.c process.c shell_output.c 
	gcc main.o process.o shell_output.o -o miCuento

main.o: main.c random_number.h
	gcc -c main.c

process.o: process.c random_number.h
	gcc -c process.c

shell_output.o: shell_output.c
	gcc -c shell_output.c

clean:
	rm -f *.o
