/********************************************
* IST - MEEC
* ADRC 1º semestre 2016/2017
* 2ªMini-Projecto: InterDomainRouting
*
* Turno de 2ª, 17h Grupo 6
* 
* Miguel Rodrigues, nº 76176 
* Pedro Esteves, nº 77060
* 
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "struct.h"

/*global variables*/
int p[60001];
int C;

void menu(){
	char buffer[512];

		snprintf(buffer,sizeof buffer, "%s",
			"\n\n\t\tInterDomainRouting - 2nd ADRC Mini-Project\n\n");
		printf("%s",buffer);
}


int main(int argc, char * argv[]){

	Graph * G;

	int T[100] ={};
	int i = 0;

	if(argc != 2){
		printf("Erro nos argumentos a usar. Saíndo.\n");
		exit(0);
	}

	menu();

	G = ReadNetwork(argv[1]);

	for(i=0; i<70000; i++){
		if(G->Nodes[i]!= NULL){
			C += G->Nodes[i]->n_c;
		}
	}
	printf("Ñº de links C -> %d\n", C);
	
	VerifyCommerc(G->Nodes,T);
	
	VerifyCycle(G->Nodes, T);



	FreeGraph(G);
	free(G);
	exit(0);
}