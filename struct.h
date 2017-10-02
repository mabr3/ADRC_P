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

void impstruct(int i);
void searchNode(char * address, char * next_hop, Node * no, int pos);
void imprime(Node * no);

#endif