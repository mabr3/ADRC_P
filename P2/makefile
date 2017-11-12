#all: main file struct

main: main.c file.o struct.o
	gcc -g -Wall -o main main.c file.o struct.o

struct.o: struct.c struct.h
	gcc -g -c -Wall struct.c

file.o: file.c file.h
	gcc -g -c -Wall file.c