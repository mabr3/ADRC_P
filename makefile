all: main file struct

main: main.c file.o struct.o
	gcc -g -Wall main.c -o main

struct.o: struct.c struct.h
	gcc -g -Wall struct.c

file.o: file.c file.h
	gcc -g -Wall file.c