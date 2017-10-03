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

void searchNode(char * address, char * next_hop, Node * no, int pos);
void imprime(Node * no);
void PrintTable(Node * no, char * address);
void LookUp(Tree * arvore, char * address);
Tree * DeletePrefix(Tree * arvore, char * prefix);
void DeleteNodes(Node *no, char * prefix, int stop);
Tree * InsertPrefix(Tree * arvore, char * prefix, char * nexthop);
void FreeTree(Node * no);

#endif