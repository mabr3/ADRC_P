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
			no->zero->one = NULL;
			no->zero->zero = NULL;
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
			no->one->one = NULL;
			no->one->zero = NULL;
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

	if(nhop == 0){
		printf("There's no nexthop for that address.\n");
	}else{
		printf("For the given address (%s), the next hop is: %d\n\n", address, nhop);
	}

	return;
}

/********************************************
* DeletePrefix():
* 
* 
*********************************************/

Tree * DeletePrefix(Tree * arvore, char * prefix){

	Node * search = arvore->first;
	Node * aux = search;
	int i=0;
	int it_stop =0;

	while(prefix[i] != '\0'){
		if(search == NULL){
			printf("That prefix is not on the tree yet.\n");
			return arvore;
		}

		if((prefix[i] != '0') && (prefix[i] != '1') && (prefix[i] != '\0')){
			printf("Wrong format for the prefix: %s.\n", prefix);
			return arvore;
		}

		if(prefix[i] == '0'){
			if(search->nexthop !=0){
				aux = search;
				it_stop = i;
			}
			search = search->zero;
			i++;
		}else{
			if(search->nexthop !=0){
				aux = search;
				it_stop = i;
			}
			search = search->one;
			i++;
		}

		/*se tiver filhos então é porque há nexthops em algum deles.*/
		if(prefix[i] == '\0' && (search->zero != NULL || search->one != NULL)){
			printf("Delete sem ser folha.\n");
			search->nexthop = 0;
			break;
		}

		if(prefix[i] == '\0' && search->zero == NULL && search->one == NULL){
			printf("Delete folha e coisas para cima se necessário.\n");
			search->nexthop = 0;
			DeleteNodes(aux, prefix, it_stop);
			if(it_stop == 0){
				printf("olelele\n");
			}else{
				printf("erro\n");
				aux->one = NULL;
			}
			break;
		}
	}

	/*if(aux->zero->zero == NULL){printf("tem de ser \n");}
	if(aux->one == NULL){printf("ola caralo\n");}
	if(aux->zero == NULL){printf("fds\n");}*/
	printf("Prefix %s deleted.\n\n", prefix);
	return arvore;
}

/********************************************
* DeleteNodes():
* 
* 
*********************************************/

void DeleteNodes(Node *no, char * prefix, int stop){

	if(no!=NULL){
		if(prefix[stop] == '0'){
			if(no->zero!= NULL){
				if(no->zero->nexthop == 0 && no->zero->zero == NULL && no->zero->one == NULL){
					free(no->zero);
					no->zero = NULL;
				}else{
					DeleteNodes(no->zero, prefix, stop++);
				}
			}
		}else{
			if(no->one != NULL){
				if(no->one->nexthop == 0 && no->one->zero == NULL && no->one->one == NULL){
					free(no->one);
					no->one = NULL;
				}else{
					DeleteNodes(no->one, prefix, stop++);
				}
			}
		}
	}
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
				search->nexthop = 0;
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
				search->nexthop = 0;
				search->zero = NULL;
				search->one = NULL;
				i++;
			}
		}
	}

	search->nexthop = atoi(nexthop);
	printf("Prefix inserted.\n\n");
	return arvore;
}

/********************************************
* FreeTree():
* 
* 
*********************************************/

void FreeTree(Node * no){
	Node * aux1;
	Node * aux2;

	if(no !=NULL){
		aux1 = no->zero;
		aux2 = no->one;
		free(no);
		printf("++\n");
		FreeTree(aux1);
		FreeTree(aux2);
	}

}
