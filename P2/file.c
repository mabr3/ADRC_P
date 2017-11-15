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

#include "file.h"
#include "struct.h"

/********************************************
* ReadNetwork(): Ler os caminhos do ficheiro
* de texto e criar as respetivas estruturas, 
* adicionando as ligações com recurso à função
* AddEdge().
* 
*********************************************/

Graph * ReadNetwork(char * nome, int T[]){

	int head = 0;
	int tail = 0;
	int type = 0;
	int i = 0;
	int j = 0;
	Graph * G;

	FILE * fp;

	fp = fopen(nome, "r");
	if(fp == NULL){
		printf("Error reading the file. Exiting.\n");
		exit(0);
	}

	G = (Graph *) malloc(sizeof(Graph));
	G->first = -1;
	G->n = 0;

	for(i=0;i<70000; i++){
		G->Nodes[i] = NULL;
	}

	while((fscanf(fp,"%d %d %d", &tail, &head, &type )) == 3){
		if(G->Nodes[tail] == NULL){
			G->Nodes[tail] = (Node *) malloc(sizeof(Node));
			G->Nodes[tail]->number = tail;
			G->Nodes[tail]->n_c = 0;
			G->Nodes[tail]->n_r = 0;
			G->Nodes[tail]->n_p = 0;
			G->Nodes[tail]->visit = 0;
			G->Nodes[tail]->path = 0;
			G->Nodes[tail]->ciclo = 0;
			G->Nodes[tail]->AdjList_C = NULL;
			G->Nodes[tail]->AdjList_R = NULL;
			G->Nodes[tail]->AdjList_P = NULL;
			G->n++;
		}

		AddEdge(type, head, tail, G->Nodes[tail]);
	}

	fclose(fp);

	for(i=0; i<70000; i++){ /*verificar quais são os Tier1s existentes (não têm providers)*/
		if(G->Nodes[i]!= NULL){
			if(G->Nodes[i]-> n_p == 0){
				T[j] = i;
				j++;
			}
		}
	}

	return G;
}