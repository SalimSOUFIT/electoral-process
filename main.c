#include "mecanismeConsensus.h"

//Ex 9 Q6

int main() {

    printf("==========================================================================Debut des Elections================================================================================\n\n\n");
	
	//Générations des données pour la simulation de vote
	//on a déjà généré les données au préalable, car cela prend énormément de temps 
	//generate_random_data(1000, 5) ;


	//Lecture des candidats, des citoyens et des votes
	CellProtected * listPr = read_public_protected("declarations.txt") ;
	CellKey * listCt = read_public_keys("keys.txt") ;
	CellKey * candidat = read_public_keys("candidates.txt") ;


	//Construction des blocs et de la blockchain
	CellProtected * courP = listPr ; //vote courant
	CellProtected * pTemp ; //vote précédant le vote courant
	CellTree * racine = NULL ; //arbre résultat 
	CellTree* tmp = NULL;
	char name[30];

	printf("Construction de la blockchain en cours ...............\n\n");

	int j = 0 ;
	int i = 0 ;
	while(courP && j<100){

		//Envoi de 10 votes
		while(courP && i < 10){
			submit_vote(courP->data) ;
			pTemp = courP ;
			courP = courP->next ;
			i++;
		}
		
		//Création d'un bloc
		//delete_node(tmp);
		tmp = create_block(tmp, pTemp->data->pKey, 1) ;

		//Ajout du bloc dans la blockchain
		sprintf(name, "block_%d.txt", j);
		add_block(1, name) ;
		j++ ;
		i = 0 ;
	}

	printf("Construction de la blockchain terminee\n\n");


	//construction et affichage de l'abre
	printf("Construction de l'arbre en cours ............................\n\n");
	racine = read_tree() ;
	//print_tree(racine, 100) ;

	
	//Calcul du vainqueur
	printf("Calcul du vainqueur des elections en cours .................................. \n");
	char * gagnant = key_to_str(compute_winner_BT(racine, candidat, listCt, 5, 1000)) ;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Le  vainqueur est : %s ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", gagnant);
	free(gagnant);
	//printf("coucou\n");
	


	return 0;
}

/*
	//creation du premier bloc
	for (int i = 0; i < 10; i++){
		submit_vote(courP->data) ;
		pTemp =courP ;
		courP = courP->next ;
	}
	Block * b = malloc(sizeof(Block)) ;
	b->author = pTemp->data->pKey ;
	b->votes = read_public_protected("Pending_votes.txt") ;
	b->previous_hash = NULL ;
	b->nonce = 0 ;
	compute_proof_of_work(b, 2) ;
	cl = create_node(b) ;
	block_to_file(cl->block, "Pending_block.txt") ;
	remove("Pending_votes.txt") ;
	char name[20];
	sprintf(name, "name_%d.txt", 1);
	add_block(2, name) ;
	remove("Pending_block.txt") ;
	*/