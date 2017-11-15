Coisas não utilizadas, mas feitas.

void VerifyCommerc(Node * Nodes[], int T[]){
	int i = 0;
	int j = 0;
	int k = 0;
	int not = 0;
	//int T[100] = {}; /*para guardar o identificador de cada Tier1*/

	NodeAdj * search = NULL;

	for(i=0; i<70000; i++){ /*verificar quais são os Tier1s existentes (não têm providers)*/
		if(Nodes[i]!= NULL){
			if(Nodes[i]-> n_p == 0){
				T[j] = i;
				j++;
			}
		}
	}
	printf("J é %d\n\n", j);
	printf("Os Tier1s são: \n");
	i=0;
	while(T[i]!= 0){
		printf("%d; Nº de Peers: %d; Peers->",T[i], Nodes[T[i]]->n_r);
		search = Nodes[T[i]]->AdjList_R;
		while(search != NULL){
			printf(" %d", search ->AS);
			search = search->next;
		}
		i++;
		printf("\n");
	}
	printf("\n");

	

	for(i=0; i<j; i++){
		if(Nodes[T[i]]->n_r < j-1){ /* tem de ter pelo menos (Nº de Tier1s -1) Peers.*/
			printf("Não é Commercially Connected.1\n");
			return;
		}

		for(k=0;k<j;k++){/*percorrer os indices dos Tier1s armazenados*/
			search = Nodes[T[i]]->AdjList_R; /* Percorrer os Peers do Tier1 em questão*/
			while(search != NULL){
				if(Nodes[search->AS]->n_p != 0){/*Se o Peer tiver providers, então não é Tier1, pode-se passar à frente*/
					search = search->next;
				}else{
					if(search->AS == T[k] || Nodes[T[i]]->number == T[k]){/* se foi encontrado o peer correpondente ao indice guardado ou se é o próprio nó*/
						not = 0;
						break;
					}else{
						not = 1;
						search = search->next;
					}
				}
			}

			if(not == 1){
				printf("Não está commercially connected, pois nem todos os Tier1s têm ligações do tipo Peer.\n");
				return;
			}
		}
	}
	printf("Todos os Tier1s são peers entre si, logo é comercialmente conexa.\n");
	return;
}



	printf("Entrei no nó %d. O meu visit é: %d, numero de visitas é : %d e n_p é : %d\n", No->number, No->visit, No->n_visitas, No->n_p);
	No->n_visitas++;

	if(No->visit == 1 && No->n_visitas <= No->n_p){/*ja foi visitado, mas não é o caso do ciclo*/
		return 0;
	}

	search = No->AdjList_C;
	No->visit = 1;
	
	if(search == NULL){
		printf("Nó %d é um stub.\n", No->number);
	}

	while(search != NULL){
		if(Nodes[search->AS]->visit == 1 && Nodes[search->AS]->n_visitas >= Nodes[search->AS]->n_p){/*ciclo!*/
			printf("%d tem 1 em v\n", search->AS);
			ciclo =1;
			break;
		}else{
			if(Nodes[search->AS]->visit == 0 || Nodes[search->AS]->n_visitas < Nodes[search->AS]->n_p){
				ciclo = DFS(Nodes, Nodes[search->AS]);
				printf("Voltei ao nó %d\n", No->number);
				if(ciclo == 1){
					break;
				}
			}
		}
		search = search->next;	
	}


\For{Every Node != NULL}
					\If{Number of Providers == 0}
						\State Save Node in T1 vector, T.
					\EndIf
				\EndFor