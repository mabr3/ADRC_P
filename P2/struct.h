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
********************************************/
#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node{
		int number;
		int visit;
		int path;
		int ciclo;
		int nhops;
		int n_c;
		int n_r;
		int n_p;

		struct NodeAdj * AdjList_C;
		struct NodeAdj * AdjList_R;
		struct NodeAdj * AdjList_P;
}Node;

typedef struct NodeAdj{
	int AS;
 	struct NodeAdj * next;

}NodeAdj;

typedef struct Graph{
	struct Node * Nodes[70000];
	int first;
	int n;
}Graph;

void AddEdge(int type, int head, int tail, Node * No);
void FreeAdjList(NodeAdj * No);
void FreeGraph(Graph * G);


int VerifyCommerc(Node * Nodes[], int T[]);
int VerifyCycle(Node * Nodes[], int T[]);
int DFS(Node * Nodes[], Node * No);
void Path4(Node * Nodes[], Node * No);
void cleanVisits(Node * Nodes[], int C[]);
void AddCpaths(Node * Nodes[], Node * No);

#endif