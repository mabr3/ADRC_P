#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "struct.h"


int main(int argc, char * argv[]){

	struct Tree * arvore;

	if(argc != 2){
		printf("Wrong number of arguments. Try again.\n");
		exit(0);
	}

	impfile(2);
	impstruct(2);
	
	arvore = readFile(argv[1]);
	printf("vou imprimir\n");
	imprime(arvore->first);




	exit(0);


}