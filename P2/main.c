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
	

	int C[3];
	C[0] = 0;
	C[1] = 0;
	C[2] = 0;

	if(argc != 2){
		printf("Erro nos argumentos a usar. Saíndo.\n");
		exit(0);
	}

	menu();

	G = ReadNetwork(argv[1], T);

	
	if(VerifyCycle(G->Nodes, T) !=1 ){/*Se não existirem ciclos*/
		if(VerifyCommerc(G->Nodes,T) != 1){/*se estiver comercialmente conexa*/
			printf("Tudo ok\n");
		}
	}

	cleanVisits(G->Nodes, C);
	C[0]=C[1]=C[2]=0;
	for(i=0;i<70000;i++){
		if(G->Nodes[i] != NULL){
			Path4(G->Nodes, G->Nodes[i]);
			G->Nodes[i]->path = 0;
			for(j=0; j<100; j++){
				if(G->Nodes[j] != NULL && j!=i){
					printf("Do nó %d para o nó %d vou por caminho %d por %d hops\n", j, i, G->Nodes[j]->path, G->Nodes[j]->nhops);
				}
			}

			cleanVisits(G->Nodes, C);
		}
	}



	printf("\nNumeros: C = %d , R = %d , P = %d.\n",C[0],C[1], C[2]);
	printf("Total de caminhos: %d.\n", C[0] + C[1] + C[2]);
	printf("Percentagem de caminhos C: %f%%\n", (100.0 * C[0])/(C[0] + C[1] + C[2]));
	printf("Percentagem de caminhos R: %f%%\n", (100.0 * C[1])/(C[0] + C[1] + C[2]));
	printf("Percentagem de caminhos P: %f%%\n", (100.0 * C[2])/(C[0] + C[1] + C[2]));
	int S =0;
	int T=0;


	/*for(i=0;i<70000;i++){
		if(G->Nodes[i] != NULL){
			if(G->Nodes[i]->n_p==0){
				T++;
			}
			if(G->Nodes[i]->n_c==0){
				S++;
			}
		}
	}*/

	FreeGraph(G);
	free(G);
	exit(0);
}


