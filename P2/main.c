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

	G = ReadNetwork(argv[1], T);

	//printf("Ñº de links C -> %d\n", C);
	
	
	if(VerifyCycle(G->Nodes, T) !=1 ){/*Se não existirem ciclos*/
		if(VerifyCommerc(G->Nodes,T) != 1){/*se estiver comercialmente conexa*/
			printf("hello\n");
		}

	}



	FreeGraph(G);
	free(G);
	exit(0);
}


