#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

void impstruct(int i){
	printf("%d\n", i);
}

void searchNode(char * address, char * next_hop, Node * no, int pos){
	if(address[pos] == '0'){
		printf("1apos é zero\n");

		if(no->zero == NULL){
			no->zero = (Node *) malloc(sizeof(Node));
			no->zero->nexthop = 0;
			printf("criei um no para zero\n");
		}
		
		if(address[pos+1] == '\0'){
			no->zero->nexthop = atoi(next_hop);
			printf("pus um next hop bem\n");
		}else{
			searchNode(address, next_hop, no->zero, pos+1);
		}

	}
	
	if(address[pos] == '1'){
		printf("éum\n");

		if(no->one == NULL){
			no->one = (Node *) malloc(sizeof(Node));
			no->one->nexthop = 0;
			printf("criei um no para one\n");
		}

		if(address[pos+1] == '\0'){
			no->one->nexthop = atoi(next_hop);
			printf("pus 1 next hop bem\n");
		}else{
			searchNode(address, next_hop, no->one, pos+1);
		}

	}

	return;
}
/*pre order*/
void imprime( Node * no){
	if(no != NULL){
		printf("%d\n",no->nexthop);
		imprime(no->zero);
		imprime(no->one);
	}

	return;
}