all: main file struct

main: main.c file.h struct.h
	gcc -g -Wall main.c -o main

struct: struct.c struct.h
	gcc -g -Wall struct.c

file: file.c file.h
	gcc -g -Wall file.c