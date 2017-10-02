#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "struct.h"



void impfile(int i){
	printf("%d\n", i*10);
}

Tree * readFile(char * nome){

	char buffer1[20];
	char buffer2[3];

	FILE * fp;

	struct Tree * arvore; 

	fp = fopen(nome, "r");

	if(fp == NULL){
		printf("Error while opening the file!\n");
		exit(0);
	}

	arvore = (Tree *) malloc(sizeof(Tree));
	arvore->first = (Node *) malloc(sizeof(Node));
	arvore->first->zero = NULL;
	arvore->first->one = NULL;
	arvore->first->nexthop = 0;


	while((fscanf(fp,"%s %s", buffer1, buffer2 )) == 2){
		printf("vou por --%s --%s\n", buffer1, buffer2);

		searchNode(buffer1, buffer2, arvore->first, 0);


		printf("ja pus!\n");



	}

	printf("nome é: %s\n", nome);

	return(arvore);

	//while()


}