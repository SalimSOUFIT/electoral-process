#include "mecanismeConsensus.h"


int main(){


	//Bloc de test
	//NE PAS METTRE EN COMMENTAIRE 
	CellProtected* listPr = read_public_protected("10declarations.txt");

	Block * b = (Block*)malloc(sizeof(Block)) ; 
	Key * k = (Key*)malloc(sizeof(Key)) ;
	b->author = k ;
	init_key(b->author, 67, 117) ;
	b->votes = listPr ;
	b->hash = (unsigned char *)strdup("hash") ;
	b->previous_hash = (unsigned char *)strdup("hash precedent") ;
	b->nonce = 3;





	/*
	//test de block_to_file
	block_to_file(b, "test_block_to_file.txt");
	*/
	
	
	



	/*
	//test de la fonction block_to_str
	char * s1 = block_to_str(b) ;
    printf("%s", s1) ;
	free(s1);
	*/
	
	




	/*
	//test de la fonction file_to_block, 1ère partie
	//l'autre partie des tests de cette fonction se trouve avec les tests de verify_block, plus bas dans ce fichier
	Block * b1 ;	
    b1 = file_to_block("test_block_to_file.txt") ;

	
	char* aut = key_to_str(b1->author);
    printf("Affichage du block :\n%s\n%s\n%s\n%d\n", aut, b1->hash, b1->previous_hash, b1->nonce) ;
    print_list_protected(b1->votes);

	free(aut);
	delete_list_protected(&b1->votes);
	free(b1->hash);
	free(b1->previous_hash);
	free(b1->author);
	free(b1);
	*/
	
	
	
    

	


	/*
    //Ex 7 Q4

	const char * s = "Rosetta code" ;
	unsigned char * d = SHA256((const unsigned char*)s, strlen(s), 0) ;
	int i ;
	for ( i = 0; i < SHA256_DIGEST_LENGTH ; i ++) {
		printf("%02x " , d[i]) ;
	}
	putchar('\n');
	*/




	/*
	//Test de hash_SHA256
	//on affiche d'abord les codes ascii en héxadécimal, puis la valeur hachée elle-même
	//le hash peut s'afficher en deux lignes si l'un des caractères hachés est un saut de ligne
	//les 0 en héxadecimal sont affichés comme des 30
	
	unsigned char* e = hash_SHA256("Rosetta code");

	//affichage des codes ascii héxadécimaux
	putchar('\n');
	int j;
	for (j = 0; j < SHA256_DIGEST_LENGTH ; j++) {
		printf ("%02x ", e[j]) ;
	}
	printf("\n\n");

	//affichage en chaîne de caractères
	printf("%s\n\n", (char*)e);

	free(e);
	*/
	
	
	
	
	




	/*
	//Test de compute_proof_of_work
	//on affiche d'abord les codes ascii en héxadécimal, puis la valeur hachée elle-même
	//le hash peut s'afficher en deux lignes si l'un des caractères hachés est un saut de ligne
	//les 0 en héxadecimal sont affichés comme des 30
	
	compute_proof_of_work(b, 1);
	printf("\nnonce trouve : %d\n\n", b->nonce);
	
	char* sb = block_to_str(b);
	unsigned char* res = hash_SHA256(sb);
	
	//affichage héxadécimal
	int j;
	for (j = 0; j < SHA256_DIGEST_LENGTH ; j++) {
		printf ("%02x ", res[j]) ;
	}
	putchar('\n'); putchar('\n');
	
	//affichage chaîne de caractères
	printf("%s\n\n", res);
	
	free(res);
	free(sb);
	*/
	

	




	/*
	//Test de verify_block et 2ème partie des tests de file_to_block

	//test avec un bloc non valide
	printf("verify_block : %d\n", verify_block(b, 1));

	//test avec un bloc valide
	compute_proof_of_work(b, 1);
	printf("verify_block : %d\n", verify_block(b, 1));

	//on vérifie que l'écriture et la lecture du bloc dans un fichier ne changent pas sa validité
	block_to_file(b, "test_block_to_file.txt");
	Block* blo = file_to_block("test_block_to_file.txt");
	printf("verify_block : %d\n", verify_block(blo, 1));
	*/
	
	

	
	




	/*
	//Ex 7 Q8
	//Etude du temps mis pour l'éxécution de compute_proof_of_work selon la valeur de son paramètre d
	//les résultats seront dans le fichier sortie_compute_PoW.txt ainsi que dans un graphique visible dans le compte rendu
	FILE* f = fopen("sortie_compute_PoW.txt", "w");
	if (f == NULL) {
		printf("sortie_compute_PoW.txt : erreur d'ouverture du fichier\n\n");
		return 1;
	}
	
	clock_t tDeb, tFin;
	double temps_cpu;
	int dMax = 4;
	int d;

	for (d = 0; d<dMax; d++) {
		tDeb = clock();
		compute_proof_of_work(b, d);
		tFin = clock();
		temps_cpu = ((double)(tFin - tDeb)) / CLOCKS_PER_SEC;
		fprintf(f, "%d %lf\n", d, temps_cpu);
	}
	fclose(f);
	*/





	
	//Test de create_node, add_child, update_height, print_tree
	//NE PAS COMMENTER, arbre utilisé pour plusieurs tests ci-dessous
	//un schéma de l'arbre utilisé est disponible dans le compte-rendu afin de vérifier facilement les résultats des tests

	Block * b0 = (Block*)malloc(sizeof(Block)) ; 
	b0->author = k ;
	b0->votes = listPr ;
	b0->hash = (unsigned char *)strdup("hash0") ;
	b0->previous_hash = (unsigned char *)strdup("hash precedent0") ;
	b0->nonce = 99;

	Block * b1 = (Block*)malloc(sizeof(Block)) ; 
	b1->author = k ;
	b1->votes = listPr ;
	b1->hash = (unsigned char *)strdup("hash1") ;
	b1->previous_hash = (unsigned char *)strdup("hash precedent1") ;
	b1->nonce = 4;

	Block * b2 = (Block*)malloc(sizeof(Block)) ; 
	b2->author = k ;
	b2->votes = listPr ;
	b2->hash = (unsigned char *)strdup("hash2") ;
	b2->previous_hash = (unsigned char *)strdup("hash precedent2") ;
	b2->nonce = 5;

	Block * b3 = (Block*)malloc(sizeof(Block)) ; 
	b3->author = k ;
	b3->votes = listPr ;
	b3->hash = (unsigned char *)strdup("hash3") ;
	b3->previous_hash = (unsigned char *)strdup("hash precedent3") ;
	b3->nonce = 6;

	Block * b4 = (Block*)malloc(sizeof(Block)) ; 
	b4->author = k ;
	b4->votes = listPr ;
	b4->hash = (unsigned char *)strdup("hash4") ;
	b4->previous_hash = (unsigned char *)strdup("hash precedent4") ;
	b4->nonce = 7;

	Block * b5 = (Block*)malloc(sizeof(Block)) ; 
	b5->author = k ;
	b5->votes = listPr ;
	b5->hash = (unsigned char *)strdup("hash5") ;
	b5->previous_hash = (unsigned char *)strdup("hash precedent5") ;
	b5->nonce = 25;

	Block * b6 = (Block*)malloc(sizeof(Block)) ; 
	b6->author = k ;
	b6->votes = listPr ;
	b6->hash = (unsigned char *)strdup("hash6") ;
	b6->previous_hash = (unsigned char *)strdup("hash precedent6") ;
	b6->nonce = 32;

	Block * b7 = (Block*)malloc(sizeof(Block)) ; 
	b7->author = k ;
	b7->votes = listPr ;
	b7->hash = (unsigned char *)strdup("hash7") ;
	b7->previous_hash = (unsigned char *)strdup("hash precedent7") ;
	b7->nonce = 41;


	//on crée les noeuds à partir des blocs
	CellTree* r = create_node(b0);
	CellTree* n1 = create_node(b1);
	CellTree* n2 = create_node(b2);
	CellTree* n3 = create_node(b3);
	CellTree* n4 = create_node(b4);
	CellTree* n5 = create_node(b5);
	CellTree* n6 = create_node(b6);
	CellTree* n7 = create_node(b7);

	
	//on ajoute les noeuds à l'arbre
	add_child(r, n1);
	add_child(r, n2);
	add_child(r, n3);
	add_child(n2, n4);
	add_child(n3, n5);
	add_child(n3, n6);
	add_child(n4, n7);



	/*
	//Test de print_tree
	print_tree(r, 0);
	*/




	/*
	//Test de highest_child
	printf("\n\nTest de highest_child :\n\n");

	CellTree* hc = highest_child(r);
	printf("%s\n", hc->block->hash);

	hc = highest_child(n1);
	printf("%p\n", (void*)hc);

	hc = highest_child(n2);
	printf("%s\n", hc->block->hash);

	hc = highest_child(n3);
	printf("%s\n", hc->block->hash);
	*/




	/*
	//Test de last_node
	printf("\n\nTest de last_node :\n\n");

	CellTree* lh = last_node(r);
	printf("\n%s\n", lh->block->hash);

	lh = last_node(n1);
	printf("\n%s\n", lh->block->hash);

	lh = last_node(n2);
	printf("\n%s\n", lh->block->hash);

	lh = last_node(n3);
	printf("\n%s\n", lh->block->hash);
	*/





	/*
	//Test de liste_protected_longest_chain
	//pour vérifier que ce sont les bonnes listes qui sont fusionnées on peut décommenter dans la boucle de liste_protected_longest_chain un printf qui écrit sur quel noeud est fait l'appel de la fusion
	printf("\n\nliste_protected_longest_chain :\n\n");

	CellProtected* lc = liste_protected_longest_chain(r);
	print_list_protected(lc);
	//delete_list_protected(&lc);
	*/
	
	




	/*
	//Test de fusion_listes_protected
	CellProtected* listPr2 = read_public_protected("10declarations.txt");
	CellProtected* listPr3 = fusion_listes_protected(listPr, listPr2);
	print_list_protected(listPr3);
	delete_list_protected(&listPr3);
	*/






	/*
	//Test de sumbit_vote, create_block et add_block
	//pour voir le résultat, ouvrir le fichier Pending_votes.txt
	CellProtected * p = listPr ;
	while(p){
		submit_vote(p->data) ;	
		p = p->next ;
	}
	


	//pour voir le résultat, ouvrir le fichier Pending_block.txt
	create_block(r, k, 1);
	*/

	/*
	Block* bt = file_to_block("Pending_block.txt");
	printf("vb : %d\n", verify_block(bt, 1));
	block_to_file(bt, "essaiD.txt");
	*/

	
	//ouvrir le fichier Blockchain/test_add_block.txt pour voir le résultat de la fonction
	//add_block(1, "test_add_block.txt");
	





	//Test de delete_node et delete_tree
	free(k);
	//printf("salut\n");
	delete_block(b);
	//printf("salut\n");
	//delete_tree(&r);
	//print_tree(r, 0);
	//printf("salut\n");


	/*
	delete_node(r);
	delete_node(n1);
	delete_node(n2);
	delete_node(n3);
	delete_node(n4);
	delete_node(n5);
	delete_node(n6);
	delete_node(n7);
	*/
	
	

	return 0;

}