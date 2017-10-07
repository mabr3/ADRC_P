#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "struct.h"

void menu(){
	char buffer[512];

		snprintf(buffer,sizeof buffer, "%s",
			"\n\n\t\tPrefix Tree and Longest Prefix Matching - 1st ADRC Mini-Project"
			"\n\tChoose an option using the corresponding number:\n"
			"- 1)\t print - Print the table on the screen.\n"
			"- 2)\t lookup - Search for the next hop for a given address.\n"
			"- 3)\t insert - Insert a given prefix and the associated next-hop in the table.\n"
			"- 4)\t delete - Delete a chosen prefix from the table.\n"
			"- 5)\t exit: Terminate the application.\n\n\n"
			"- 6)\t Extra: Print the table of even length prefixes for the two-bit prefix tree.\n\n");
		printf("%s",buffer);
}


int main(int argc, char * argv[]){

	struct Tree * arvore;
	struct Tree_Bi* arvore_bi;
	char option[7] = "";
	char buffer[18] = "";
	char prefixo[18] = "";
	char nexthop[18] = "";
	char address[18] = "";

	if(argc != 2){
		printf("Wrong number of arguments. Try again.\n");
		exit(0);
	}

	arvore = PrefixTree(argv[1]);

	menu();

	while(1){
		fgets(option, 7, stdin); /*... mudar isto*/

		switch(atoi(option)){
			case 1:
				printf("Prefix\t Next Hop\n");
				PrintTable(arvore->first, address);
				printf("\n\n");
				break;

			case 2:
				printf("What's the address you want to search?\n");
				fgets(buffer,16, stdin);
				buffer[strlen(buffer)-1] = '\0'; /*Terminar astring sem o \n*/
				LookUp(arvore, buffer);
				break;

			case 3:
				printf("What's the address you want to insert?\n");
				fgets(prefixo, 16, stdin);
				printf("What's the next hop you want to insert?\n");
				fgets(nexthop, 16, stdin);
				prefixo[strlen(prefixo)-1] = '\0'; /*Terminar astring sem o \n*/
				nexthop[strlen(nexthop)-1] = '\0'; /*Terminar astring sem o \n*/

				arvore = InsertPrefix(arvore, prefixo, nexthop);
				break;

			case 4:

				printf("What's the address you want to delete?\n");
				fgets(prefixo, 16, stdin);
				prefixo[strlen(prefixo)-1] = '\0'; /*Terminar astring sem o \n*/
				arvore = DeletePrefix(arvore, prefixo);
				break;

			case 5:
				printf("Exiting.\n");
				FreeTree(arvore->first);
				free(arvore);
				exit(0);

			case 6:
				arvore_bi = (Tree_Bi *) malloc(sizeof(Tree_Bi));
				arvore_bi->first = (Node_Bi *) malloc(sizeof(Node_Bi));
				arvore_bi->first->nexthop = 0;
				arvore_bi->first->z_z = NULL;
				arvore_bi->first->z_o = NULL;
				arvore_bi->first->o_z = NULL;
				arvore_bi->first->o_o = NULL; 
				//Create2Prefix(arvore->first, arvore_bi->first);
				BinaryToTwoBit(arvore->first, arvore_bi->first);
				printf("Prefix\t Next Hop\n");
				PrintTableEven(arvore_bi->first, address);
				FreeTreeEven(arvore_bi->first);
				free(arvore_bi);
				//PrintTable2(arvore_bi->first);
				printf("\n\n");
				break;
				
			default:
				printf("Invalid command.\n");
		}
	}

	exit(0);
}