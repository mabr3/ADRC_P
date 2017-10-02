#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

/********************************************
* searchNode():
* 
* 
*********************************************/

void searchNode(char * address, char * next_hop, Node * no, int pos){
	if(address[pos] == '0'){

		if(no->zero == NULL){
			no->zero = (Node *) malloc(sizeof(Node));
			no->zero->nexthop = 0;
		}
		
		if(address[pos+1] == '\0'){
			no->zero->nexthop = atoi(next_hop);
		}else{
			searchNode(address, next_hop, no->zero, pos+1);
		}
	}
	
	if(address[pos] == '1'){

		if(no->one == NULL){
			no->one = (Node *) malloc(sizeof(Node));
			no->one->nexthop = 0;
		}

		if(address[pos+1] == '\0'){
			no->one->nexthop = atoi(next_hop);
		}else{
			searchNode(address, next_hop, no->one, pos+1);
		}
	}

	return;
}

/********************************************
* Liga_Servidores():
* 
* 
*********************************************/

/*pre order*/
void imprime( Node * no){
	if(no != NULL){
		printf("%d\n",no->nexthop);
		imprime(no->zero);
		imprime(no->one);
	}

	return;
}

/********************************************
* PrintTable():
* 
* 
*********************************************/

void PrintTable(Node * no, char * address){

	if(no!=NULL){
		if(no->nexthop != 0){
			printf("%s\t %d\n",address, no->nexthop);
		}
		if(no->zero != NULL){
			strcat(address,"0");
			PrintTable(no->zero, address);
		}
		if(no->one != NULL){
			strcat(address, "1");
			PrintTable(no->one, address);
		}
		address[strlen(address)-1] = '\0';
	}
	return;
}

/********************************************
* LookUp():
* 
* 
*********************************************/

void LookUp(Tree * arvore, char * address){
	int i = 0;
	int nhop = 0;
	Node * search = arvore->first;
	
	while(address[i] != '\0'){

		if((address[i] != '0') && (address[i] != '1') && (address[i] != '\0')){
			printf("Wrong format for the address: %s.\n", address);
			return;
		}

		if(address[i] == '0'){
			if(search->zero !=NULL){
				search = search->zero;
				i++;
				if(search->nexthop != 0){
					nhop = search->nexthop;
				}
			}else{
				break;
			}

		}else{
			if(search->one !=NULL){
				search = search->one;
				i++;
				if(search->nexthop != 0){
					nhop = search->nexthop;
				}
			}else{
				break;
			}
		}
	}

	printf("For the given address (%s), the next hop is: %d\n", address, nhop);
	return;
}

/********************************************
* DeletePrefix():
* 
* 
*********************************************/

Tree * DeletePrefix(Tree * arvore, char * prefix){

	/*Node * search = arvore->first;
	Node * aux = search;

	while(prefix[i] != '\0'){

		if((prefix[i] != '0') && (prefix[i] != '1') && (prefix[i] != '\0')){
			printf("Wrong format for the prefix: %s.\n", prefix);
			return;
		}

		if(prefix[i] == '0'){
			search = search->zero;
			i++;

		}else{
			search = search->one;
			i++;
		}

	}*/

	return arvore;
}

/********************************************
* InsertPrefix():
* 
* 
*********************************************/

Tree * InsertPrefix(Tree * arvore, char * prefix, char * nexthop){

	Node * search = arvore->first;
	int i = 0;

	while(prefix[i] != '\0'){

		if((prefix[i] != '0') && (prefix[i] != '1') && (prefix[i] != '\0')){
			printf("Wrong format for the prefix: %s.\n", prefix);
			return arvore;
		}

		if(prefix[i] == '0'){
			if(search->zero != NULL){
				search = search->zero;
				i++;
			}else{
				search->zero = (Node *) malloc(sizeof(Node));
				search = search->zero;
				search->zero = NULL;
				search->one = NULL;
				i++;
			}

		}else{

			if(search->one != NULL){
				search = search->one;
				i++;
			}else{
				search->one = (Node *) malloc(sizeof(Node));
				search = search->one;
				search->zero = NULL;
				search->one = NULL;
				i++;
			}
		}
	}

	search->nexthop = atoi(nexthop);
	return arvore;
}