/********************************************
* IST - MEEC
* ADRC 1º semestre 2016/2017
* 1ªMini-Projecto: Prefix Trees and Longest 
* Prefix Matching

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
			search->nexthop = 0;
			break;
		}

		if(prefix[i] == '\0' && search->zero == NULL && search->one == NULL){
			search->nexthop = 0;
			DeleteNodes(aux, prefix, it_stop);
			break;
		}
	}
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
	printf("Prefix %s inserted with %s as nexthop.\n\n", prefix, nexthop);
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
		FreeTree(aux1);
		FreeTree(aux2);
	}

}

/*Extra */

/********************************************
* BinaryToTwoBit():
* 
* 
*********************************************/

void BinaryToTwoBit(Node * no, Node_Bi * no2){

	/*lado esquerdo*/
	if(no->zero != NULL){
		if(no->zero->zero != NULL){
			if(no2->z_z == NULL){
				no2->z_z = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->z_z->z_z = NULL;
				no2->z_z->o_z = NULL;
				no2->z_z->z_o = NULL;
				no2->z_z->o_o = NULL;
				no2->z_z->nexthop = 0;
			}
			if(no->zero->zero->nexthop != 0){
				no2->z_z->nexthop = no->zero->zero->nexthop;
			}else{
				no2->z_z->nexthop = no->zero->nexthop;
			}
			if(no->zero->one == NULL && no->zero->nexthop != 0){/*caso em que só um dos pointers está para null*/
				no2->z_o = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->z_o->z_z = NULL;
				no2->z_o->o_z = NULL;
				no2->z_o->z_o = NULL;
				no2->z_o->o_o = NULL;
				no2->z_o->nexthop = no->zero->nexthop;

			}
			BinaryToTwoBit(no->zero->zero, no2->z_z);
		}
		if(no->zero->one != NULL){
			if(no2->z_o == NULL){
				no2->z_o = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->z_o->z_z = NULL;
				no2->z_o->o_z = NULL;
				no2->z_o->z_o = NULL;
				no2->z_o->o_o = NULL;
				no2->z_o->nexthop = 0;
			}
			if(no->zero->one->nexthop != 0){
				no2->z_o->nexthop = no->zero->one->nexthop;
			}else{
				no2->z_o->nexthop = no->zero->nexthop;
			}
			if(no->zero->zero == NULL && no->zero->nexthop != 0){/*caso em que só um dos pointers está para null*/
				no2->z_z = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->z_z->z_z = NULL;
				no2->z_z->o_z = NULL;
				no2->z_z->z_o = NULL;
				no2->z_z->o_o = NULL;
				no2->z_z->nexthop = no->zero->nexthop;
			}

			BinaryToTwoBit(no->zero->one, no2->z_o);
		}
		if(no->zero->nexthop !=0 && no->zero->zero == NULL && no->zero->one == NULL){/* caso em que os dois pointers são null*/
			if(no2->z_z == NULL){
				no2->z_z = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->z_z->z_z = NULL;
				no2->z_z->o_z = NULL;
				no2->z_z->z_o = NULL;
				no2->z_z->o_o = NULL;
			}
			if(no2->z_o == NULL){
				no2->z_o = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->z_o->z_z = NULL;
				no2->z_o->o_z = NULL;
				no2->z_o->z_o = NULL;
				no2->z_o->o_o = NULL;
			}

			no2->z_z->nexthop = no->zero->nexthop;
			no2->z_o->nexthop = no->zero->nexthop;
		}
	}
	
	/*lado direito*/

	if(no->one != NULL){
		if(no->one->zero != NULL){
			if(no2->o_z == NULL){
				no2->o_z = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->o_z->z_z = NULL;
				no2->o_z->o_z = NULL;
				no2->o_z->z_o = NULL;
				no2->o_z->o_o = NULL;
				no2->o_z->nexthop = 0;
			}

			if(no->one->zero->nexthop != 0){
				no2->o_z->nexthop = no->one->zero->nexthop;
			}else{
				no2->o_z->nexthop = no->one->nexthop;
			}
			if(no->one->one == NULL && no->one->nexthop != 0){/*caso em que só um dos pointers está para null*/
				no2->o_o = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->o_o->z_z = NULL;
				no2->o_o->o_z = NULL;
				no2->o_o->z_o = NULL;
				no2->o_o->o_o = NULL;
				no2->o_o->nexthop = no->one->nexthop;

			}

			BinaryToTwoBit(no->one->zero, no2->o_z);
		}

		if(no->one->one != NULL){
			if(no2->o_o == NULL){
				no2->o_o = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->o_o->z_z = NULL;
				no2->o_o->o_z = NULL;
				no2->o_o->z_o = NULL;
				no2->o_o->o_o = NULL;
				no2->o_o->nexthop = 0;
			}

			if(no->one->one->nexthop != 0){
				no2->o_o->nexthop = no->one->one->nexthop;
			}else{
				no2->o_o->nexthop = no->one->nexthop;
			}

			if(no->one->zero == NULL && no->one->nexthop != 0){/*caso em que só um dos pointers está para null*/
				no2->o_z = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->o_z->z_z = NULL;
				no2->o_z->o_z = NULL;
				no2->o_z->z_o = NULL;
				no2->o_z->o_o = NULL;
				no2->o_z->nexthop = no->one->nexthop;

			}

			BinaryToTwoBit(no->one->one, no2->o_o);
		}

		if(no->one->nexthop !=0 && no->one->zero == NULL && no->one->one == NULL){/*caso em que os dois pointers estão para NULL*/
			if(no2->o_z == NULL){
				no2->o_z = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->o_z->z_z = NULL;
				no2->o_z->o_z = NULL;
				no2->o_z->z_o = NULL;
				no2->o_z->o_o = NULL;
			}
			if(no2->o_o == NULL){
				no2->o_o = (Node_Bi *) malloc(sizeof(Node_Bi));
				no2->o_o->z_z = NULL;
				no2->o_o->o_z = NULL;
				no2->o_o->z_o = NULL;
				no2->o_o->o_o = NULL;
			}

			no2->o_z->nexthop = no->one->nexthop;
			no2->o_o->nexthop = no->one->nexthop;
		}
	}

	return;
}

/********************************************
* PrintTableEven():
* 
* 
*********************************************/
void PrintTableEven(Node_Bi * no, char * address){

	if(no != NULL){
		if(no->nexthop != 0){
			printf("%s\t %d\n",address, no->nexthop);
		}
		if(no->z_z != NULL){
			strcat(address, "00");
			PrintTableEven(no->z_z, address);
		}
		if(no->z_o != NULL){
			strcat(address, "01");
			PrintTableEven(no->z_o, address);
		}
		if(no->o_z != NULL){
			strcat(address, "10");
			PrintTableEven(no->o_z,address);
		}
		if(no->o_o != NULL){
			strcat(address, "11");
			PrintTableEven(no->o_o, address);
		}
		address[strlen(address)-2] = '\0';
	}

	return;
}

/********************************************
* FreeTreeEven():
* 
* 
*********************************************/
void FreeTreeEven(Node_Bi * no){
	Node_Bi * aux1;
	Node_Bi * aux2;
	Node_Bi * aux3;
	Node_Bi * aux4;

	if(no !=NULL){
		aux1 = no->z_z;
		aux2 = no->z_o;
		aux3 = no->o_z;
		aux4 = no->o_o;
		free(no);
		FreeTreeEven(aux1);
		FreeTreeEven(aux2);
		FreeTreeEven(aux3);
		FreeTreeEven(aux4);
	}

	return;
}