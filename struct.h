#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node{
	int nexthop;
	struct Node * zero;
	struct Node * one;

}Node;

typedef struct Tree{
	struct Node * first;

}Tree;

typedef struct Node_Bi{
	int nexthop;
	struct Node_Bi * z_z;
	struct Node_Bi * z_o;
	struct Node_Bi * o_z;
	struct Node_Bi * o_o;
}Node_Bi;

typedef struct Tree_Bi{
	struct Node_Bi * first;
}Tree_Bi;

void searchNode(char * address, char * next_hop, Node * no, int pos);
void imprime(Node * no);
void PrintTable(Node * no, char * address);
void LookUp(Tree * arvore, char * address);
Tree * DeletePrefix(Tree * arvore, char * prefix);
void DeleteNodes(Node *no, char * prefix, int stop);
Tree * InsertPrefix(Tree * arvore, char * prefix, char * nexthop);
void FreeTree(Node * no);

/*Extra */

void BinaryToTwoBit(Node * no, Node_Bi * no2);
void PrintTableEven(Node_Bi * no, char * address);
void FreeTreeEven(Node_Bi * no);

#endif