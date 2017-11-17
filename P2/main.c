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
	int j = 0;
	

	int C[4];
	C[0] = 0;
	C[1] = 0;
	C[2] = 0;
	C[3] = 0;
	int NH[100]= {0};

	if(argc != 2){
		printf("Erro nos argumentos a usar. Saíndo.\n");
		exit(0);
	}

	menu();

	G = ReadNetwork(argv[1], T);

	
	if(VerifyCycle(G->Nodes, T) !=1 ){/*Se não existirem ciclos*/
		if(VerifyCommerc(G->Nodes,T) != 1){/*se estiver comercialmente conexa*/
		cleanVisits(G->Nodes, C, NH);
		
		
		C[0]=C[1]=C[2]=C[3]=0;	
		for(i=0;i<70000;i++){
			if(G->Nodes[i] != NULL){
				G->Nodes[i]->path = 0;
				G->Nodes[i]->nhops = 0;
				printf("%d\n", i);	
				//PathF(G->Nodes, G->Nodes[i]);
				Path4(G->Nodes, G->Nodes[i]);
			cleanVisits(G->Nodes, C, NH);
		}
	}



		printf("\nNumeros: C = %d , R = %d , P = %d.\n",C[0],C[1], C[2]);
		printf("Total de caminhos: %d.\n", C[0] + C[1] + C[2]);
		printf("Percentagem de caminhos C: %f%%\n", (100.0 * C[0])/(C[0] + C[1] + C[2]));
		printf("Percentagem de caminhos R: %f%%\n", (100.0 * C[1])/(C[0] + C[1] + C[2]));
		printf("Percentagem de caminhos P: %f%%\n", (100.0 * C[2])/(C[0] + C[1] + C[2]));
		}
	}


	FreeGraph(G);
	free(G);
	exit(0);
}


