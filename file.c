#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "struct.h"

/********************************************
* PrefixTree():
* 
* 
*********************************************/

Tree * PrefixTree(char * nome){

	char buffer1[20] = "";
	char buffer2[3] = "";

	FILE * fp;

	struct Tree * arvore = NULL; 

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

		searchNode(buffer1, buffer2, arvore->first, 0);
	}

	fclose(fp);

	return(arvore);
}

/********************************************
* AddTable():
* 
* 
*********************************************/

void AddTable(){

}