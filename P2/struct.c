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

#include "struct.h"


/********************************************
* PrefixTree():
* 
* 
*********************************************/

void AddEdge(int type, int head, int tail, Node * No){
	NodeAdj * aux = NULL;
	aux = (NodeAdj *) malloc(sizeof(NodeAdj));
	aux->next = NULL;
	aux->AS = 0;

	switch (type){

		case 1: /* tail é provider da head;*/
			aux->next = No->AdjList_C;
			aux->AS = head;	
			No->AdjList_C = aux;
			No->n_c ++;
			break;

		case 2: /* head e tail são peers*/
			aux->next = No->AdjList_R;
			aux->AS = head;	
			No->AdjList_R = aux;
			No->n_r ++;
			break;

		case 3: /* tail é costumer da head*/
			aux->next = No->AdjList_P;
			aux->AS = head;	
			No->AdjList_P = aux;
			No->n_p ++;
			break;

		default:
			printf("Error in creating the adjacency list.");
			exit(0);
	}
}

/********************************************
* FreeAdjList(): Recebe uma lista de adjacência
* e procede à sua libertação.
* 
* 
*********************************************/

void FreeAdjList(NodeAdj * No){
	NodeAdj * aux = NULL;
	NodeAdj * aux1 = NULL;

	aux1 = No;
	while(aux1 != NULL){
		aux = aux1;
		aux1 = aux1->next;
		free(aux);
	}
	return;
}

/********************************************
* FreeGraph(): Recebe o grafo criado e 
* liberta-o, com recurso à função FreeAdjList.
* 
* 
*********************************************/

void FreeGraph(Graph * G){

	int i = 0;	

	for(i=0;i<70000; i++){
		if(G->Nodes[i] != NULL){/*se o nó com este número existe*/
			if(G->Nodes[i]->AdjList_P != NULL){ /* free das ligações Provider - se existirem*/
				FreeAdjList(G->Nodes[i]->AdjList_P);
			}
			if(G->Nodes[i]->AdjList_R != NULL){/*free das ligações Peer - se existirem*/
				FreeAdjList(G->Nodes[i]->AdjList_R);
			}
			if(G->Nodes[i]->AdjList_C != NULL){/*free das ligações Costumer - se existirem*/
				FreeAdjList(G->Nodes[i]->AdjList_C);
			}
			free(G->Nodes[i]);
		}
	}
}

/********************************************
* VerifyCicle(): Verifica se existe um ciclo
* de clientes, fazendo uma pesquisa DFS pelos
* nós, usando apenas os links costumer.
* 
*********************************************/

int VerifyCycle(Node * Nodes[], int T[]){
	int i =0;
	int ciclo = 0;
	
	for(i=0; T[i] != 0; i++){/*Começar DS nos T1s*/		
		ciclo = DFS(Nodes , Nodes[T[i]]);
		if(ciclo == 1){
			printf("Existe um costumer cycle. Saíndo.\n");
			return 1;
		}
	}
	printf("Não existe costumer cycle!\n");

	return 0;
}

/********************************************
* DFS(): Pesquisa em profundiade para apurar
* a existência de um ciclo de consumidores.
*
* 
*********************************************/
int DFS(Node * Nodes[], Node * No){
	int ciclo = 0;

	NodeAdj * search = NULL;
	search = No->AdjList_C;
	No->ciclo = 1;

	while(search != NULL){
		if(Nodes[search->AS]->ciclo == 1){/*Já faz parte do caminho, logo existe um ciclo*/
			ciclo = 1;
			return 1;
		}else{
			if(Nodes[search->AS]->visit == 0){ /* Não faz parte do ciclo e ainda não foi visitado, DFS passa para esse nó.*/
				ciclo =DFS(Nodes, Nodes[search->AS]);
				if(ciclo ==1){
					return ciclo;
				}
			}
		}
		search = search->next;
	}

	/*volta para trás, já não faz parte do ciclo e já foi visitado, não é preciso voltar a vir aqui*/
	No->ciclo = 0;
	No->visit = 1;
	return ciclo;
}

/********************************************
* VerifyCommerc(): Verifica se é comercialmente
* conexa, recorrendo à análise dos nós que são
* Tier1s e as suas conexões Peer.
* 
* 
*********************************************/

int VerifyCommerc(Node * Nodes[], int T[]){
	int i = 0;
	int j = 0;
	int c = 0;
	NodeAdj * p = NULL;

	for(i=0;T[i]!=0;i++){
		j++;
	}

	for(i=0; i<j; i++){
		c=0;
		p = Nodes[T[i]]->AdjList_R; /*Peers*/
		while(p != NULL){
			if(Nodes[p->AS]->n_p == 0){
				c++;
			}
			p=p->next;
		}

		if(c != j-1){/* cada T1 tem de ter j-1 lgações Peer a Tier1s*/
			printf("Não é comercialmente conexa, pois nem todos os Tier1s tẽm ligações Peer entre si.\n");
			return 1;
		}
	}

	printf("É comercialmente conexa!\n");
	return 0;
}