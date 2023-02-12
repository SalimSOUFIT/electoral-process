#include "mecanismeConsensus.h"

//// Partie 4

//Ex7 Q1

//écrit un bloc dans un fichier 
void block_to_file(Block * b, char * nomF){
	if (!b || nomF == NULL){
		printf("\nblock_to_file : parametre(s) NULL\n\n") ;
		return;
	}

	FILE * f = fopen(nomF,"w") ;
	if (!f){
		printf("\nblock_to_file : Erreur d'ouverture du fichier\n\n") ;
		return;
	}

	//écriture de l'auteur
	char* aut = key_to_str(b->author);
	if (aut == NULL) {
		fprintf(f, "null\n") ;
	} else {
		fprintf(f, "%s\n", aut) ;
	}
	free(aut);

	//écriture du hash, on écrit les codes ascii héxadécimaux séparés par un espace
	if (b->hash == NULL){
		fprintf(f, "null\n") ;
	} else {
		unsigned int i;
		for (i = 0; i < strlen((char*)b->hash); ++i){
			fprintf(f, "%02x ", b->hash[i]) ;
		}
		fprintf(f, "\n");
	}

	//écriture du hash précédent, on écrit les codes ascii héxadécimaux séparés par un espace
	if (b->previous_hash == NULL){
		fprintf(f, "null\n") ;
	} else {
		unsigned int i;
		for (i = 0; i < strlen((char*)b->previous_hash); ++i){
			fprintf(f, "%02x ",b->previous_hash[i]) ;
		}
		fprintf(f,"\n");
	}

	//écriture de la preuve de travail
	fprintf(f, "%d\n",b->nonce) ;

	//écriture des déclarations de vote
	CellProtected * cl = b->votes ; //déclaration courante
	while(cl){
		char* s = protected_to_str(cl->data);
		fprintf(f, "%s\n", s);
		free(s);
		cl = cl->next;
	}

	fclose(f) ;
}


//Ex7 Q2

// lit un bloc depuis un fichier (écrit avec block_to_file) et le retourne
Block * file_to_block(char * nomF){
	FILE * f = fopen(nomF,"r") ;
	if (!f){
		printf("file_to_block : Erreur d'ouverture du fichier\n") ;
		return NULL;
	}

	Block * b = (Block*)malloc(sizeof(Block)) ; //bloc résultat
	if (b == NULL) {
		printf("file_to_block : Erreur d'allocation du Block'\n\n") ;
	}
	
	char buffer[256] ;


	//on récupère l'auteur
	b->author = str_to_key(fgets(buffer, 256, f));
	


	//on récupère le hash
	char* hash_line = fgets(buffer, 256, f); //on récupère la ligne contenant les codes ascii du hash
	b->hash = malloc(33); // = SHA_DIGEST_LENGTH + 1
	unsigned char* hash = b->hash; //pointeur "itérateur" sur b->hash

	//on relève chaque code ascii présent sur la ligne puis on l'écrit en char dans le bloc (dans la limite de 32 codes ascii)
	int j = 0;
	while((hash_line != NULL) && (*hash_line != '\n') && (j < 32)) {
		sscanf(hash_line, "%02hhx ", hash);
		j++;
		hash++;
		hash_line += 3; //on avance de 3 : le code héxadécimal compte pour 2 et l'espace pour 1
	}
	b->hash[j] = '\0';


	//on récupère previous_hash
	char* previous_hash_line = fgets(buffer, 256, f); //on récupère la ligne contenant les codes ascii de previous_hash
	b->previous_hash = malloc(33); // = SHA_DIGEST_LENGTH + 1
	unsigned char* prev_hash = b->previous_hash; //pointeur "itérateur" sur b->previous_hash
	b->previous_hash[0] = '\0';

	if(strcmp(buffer, "null\n") == 0) {
		b->previous_hash = NULL;
	} else {
		//on relève chaque code ascii présent sur la ligne puis on l'écrit (en char) dans le bloc (dans la limite de 32 codes ascii)
		j = 0;
		while((previous_hash_line != NULL) && (*previous_hash_line != '\n') && (j < 32)) {
			sscanf(previous_hash_line, "%02hhx ", prev_hash);
			j++;
			prev_hash++;
			previous_hash_line += 3; //on avance de 3 : le code héxadécimal compte pour 2 et l'espace pour 1
		}
		b->previous_hash[j] = '\0';
	}
	

 
	//on récupère nonce
	fgets(buffer, 256, f) ;
	sscanf(buffer, "%d\n", &b->nonce);



	//on récupère la liste de votes (l'ordre va être inversé)
	CellProtected* mauvaisOrdre = NULL;
	while(fgets(buffer, 256, f)) {
		ajoute_protected_tete(&mauvaisOrdre, str_to_protected(buffer));
	}

	//on inverse l'ordre des cellules de la liste (l'ajout en tête les a inversé, donc on les re-inverse pour revenir à l'odre initial)
	b->votes = NULL;
	CellProtected* cour = mauvaisOrdre;
	while(cour != NULL) {
		ajoute_protected_tete(&b->votes, cour->data);
		cour = cour->next;
	}

	//on libère les cellules de mauvaisOrdre (sans free les Protected qui n'ont pas été dupliqués)
	CellProtected* temp = NULL;
	while(mauvaisOrdre != NULL) {
		temp = mauvaisOrdre->next;
		free(mauvaisOrdre);
		mauvaisOrdre = temp;
	}
	

	fclose(f);
	return b ;
}


//Ex7 Q3

//genere une chaine de caracteres representant un bloc
char* block_to_str(Block* b){
	if (b == NULL) {
		printf("block_to_str : block NULL\n\n");
		return NULL;
	}

	char* aut = key_to_str(b->author);

	//on construit une chaîne votes contenant tous les votes concaténés
	char* votes = malloc(sizeof(char)*100000); //on choisit la taille arbitrairement mais suffisament grande
	if (votes == NULL) {
		printf("block_to_str : erreur d'allocation\n\n");
		return NULL;
	}
	votes[0] = '\0';

	char* voteCour = NULL; //vote courant
	CellProtected* cour = b->votes;
	while(cour != NULL) {
		voteCour = protected_to_str(cour->data);
		strcat(votes, voteCour); //on concatène le vote courant à la chaîne
		free(voteCour);
		cour = cour->next;
	}
	strcat(votes, "\0");

	char* res = malloc(100000); //chaîne résultat
	if (res == NULL) {
		printf("block_to_str : erreur d'allocation\n\n");
		return NULL;
	}

	//on écrit tout le bloc dans la chaîne résultat
	sprintf(res, "%s\n%s\n%d\n%s\n", aut, b->previous_hash, b->nonce, votes);

	free(votes);
	free(aut);
	return res;

}


//Ex7 Q5

//retourne la valeur hachée par SHA256 de la chaine
unsigned char* hash_SHA256(char * s) {
	if (s == NULL) {
		printf("hash_SHA256 : chaine vide\n\n");
		return NULL;
	}

	//on calcule la valeur hachée
	unsigned char* h = SHA256((const unsigned char*)s, strlen(s), 0);
	unsigned char* res = malloc(257);
	if (res == NULL) {
		printf("hash_SHA256 : erreur d'allocation du résultat\n\n");
		return NULL;
	}

	//on la copie dans une nouvelle chaîne pour rajouter un marqueur de fin
	int i;
	for (i=0; i<256; i++) {
		res[i] = h[i];
	}
	res[256] = '\0';

	return res;
}


//Ex 7 Q6

//trouve nonce pour le bloc passé en paramètre
void compute_proof_of_work(Block *B, int d) {
	if (B == NULL) {
		printf("compute_proof_of_work : parametre(s) invalide(s)\n\n");
		return;
	}

	char* s = block_to_str(B);
	unsigned char* h = hash_SHA256(s);

	//on construit une chaîne témoin remplie de 0
	char* temoin = malloc(d+1);
	int i;
	for(i = 0; i<d; i++) {
		temoin[i] = '0';
	}
	temoin[d] = '\0';

	while (strncmp((char*)h, temoin, d) != 0) { //on compare le hash à une chaîne témoin ayant le bon nombre de 0
		B->nonce++;
		free(s);
		free(h);
		s = block_to_str(B);
		h = hash_SHA256(s);
	}
	B->hash = h ;
	free(temoin);
}

//Ex 7 Q7

//retourne 1 si le bloc est valide, 0 sinon, -1 en cas de problème
int verify_block(Block* B, int d) {
	if (B == NULL || d<0) {
		printf("\n\nverify_block : parametre(s) invalide(s)\n\n");
		return -1;
	}

	char* s = block_to_str(B);
	unsigned char* h = hash_SHA256(s);

	//on construit une chaîne témoin remplie de 0
	char* temoin = malloc(d+1);
	if (temoin == NULL) {
		printf("verify_block : erreur d'allocation\n\n");
		free(s);
		free(h);
		return -1;
	}
	
	int i;
	for(i = 0; i<d; i++) {
		temoin[i] = '0';
	}
	temoin[d] = '\0';

	//on compare la chaîne témoin à notre valeur hachée sur les d premiers caratères
	int res = strncmp((char*)h, temoin, d);
	free(temoin);
	free(s);
	//free(h);

	if (res == 0) {
		return 1;
	} else {
		return 0;
	}
}

//Ex 7 Q9

//supprime un Block, sans supprimer son auteur ni les Protected
void delete_block(Block* b) {
	if (b != NULL) {
		free(b->hash);
		free(b->previous_hash);

		CellProtected* pr = b->votes; //cellule courante
		CellProtected* temp;
		while (pr != NULL) {
			temp = pr;
			pr = pr->next;
			free(temp);
		}

		free(b);
	}
}



//Ex 8 Q1

//crée et initialise un noeud CellTree
CellTree* create_node(Block* b) {
	if (b == NULL) {
		printf("create_node : Block parametre NULL\n\n");
		return NULL;
	}

	CellTree* cell = (CellTree*)malloc(sizeof(CellTree));
	if (cell == NULL) {
		printf("create_node : erreur d'allocation de la cellule\n\n");
		return NULL;
	}

	cell->block = b;
	cell->father = cell->firstChild = cell->nextBro = NULL;
	cell->height = 0;

	return cell;
}



//Ex 8 Q2

//met à jour la hauteur du noeud father lorsqu'un de ses fils a été modifié
int update_height(CellTree* father, CellTree* child) {
	if (father == NULL) {
		printf("update_height : father vaut NULL\n\n");
		return -1;
	}

	if (child == NULL) {
		return 0 ;
	}

	//cas général
	if (father->height >= child->height + 1) {
		return 0;
	} else {
		father->height = child->height + 1;
		return 1;
	}
}




//Ex 8 Q3

//ajoute un fils à un noeud et met à jour la hauteur de ses ascendants
void add_child(CellTree* father, CellTree* child) {
	if (father == NULL || child == NULL){
		printf("add_child : father et/ou child vaut NULL\n\n");
			return;
	}
	
	//ajout du fils
	if (father->firstChild == NULL) { //cas ou father est une feuille
		father->firstChild = child;
		child->father = father;
	} else if (father->nextBro == NULL) { //cas où father n'a qu'un fils
		father->nextBro = child;
		child->father = father;
	} else { //cas où father a au moins 2 fils
		CellTree* bro = father->nextBro;
		while (bro->nextBro != NULL) {
			bro = bro->nextBro;
		}
		bro->nextBro = child;
		child->father = father;
	}

	//mise à jour des hauteurs des ascendants
	CellTree* ancetres = father;
	while (ancetres != NULL) {
		update_height(ancetres, child);
		child = ancetres;
		ancetres = ancetres->father;
	}
}



//Ex 8 Q4

//affiche un arbre
//dans le main, appeler la fonction avec i = 0
void print_tree(CellTree* t, int i) {
	if (t == NULL) {
		return;
	}

	//on décale l'affichage
	int j;
	for(j=0; j<i; j++) {
		printf("   ");
	}

	//on affiche le noeud courant
	if (t->block != NULL) {
		printf("%d %s\n\n", t->height, t->block->hash);
	}
		
	print_tree(t->firstChild, i+1);
	print_tree(t->nextBro, i+1);
}



//Ex 8 Q5

//supprime un noeud CellTree
void delete_node(CellTree* node) {
	if (node != NULL) {
		delete_block(node->block);
		free(node);
	}
}


//supprime un arbre de CellTree
void delete_tree(CellTree** pT) {
	if (pT == NULL || *pT == NULL) {
		return;
	}

	CellTree* noeud = *pT;
	delete_tree(&(noeud->firstChild));
	delete_tree(&(noeud->nextBro));
	delete_node(noeud);
	*pT = NULL;
}



//Ex 8 Q6

//renvoie le noeud fils ayant la plus grande hauteur 
//(si plusieurs fils ont la même hauteur on renvoie le premier qu'on a trouvé)
CellTree* highest_child(CellTree* cell) {
	if (cell == NULL) {
		printf("highest_child : cell vaut NULL\n\n");
		return NULL;
	}

	int hMax = 0;
	CellTree* max = NULL;

	if (cell->firstChild != NULL) {
		hMax = cell->firstChild->height;
		max = cell->firstChild;
	}

	CellTree* bro = cell->nextBro;
	while (bro != NULL) {
		if(bro->height > hMax) {
			hMax = bro->height;
			max = bro;
		}
		bro = bro->nextBro;
	}

	return max;
}



//Ex 8 Q7

//retourne le dernier bloc de la plus longue chaîne de tree
//(en particulier, si tree est une feuille, la fonction retourne tree)
CellTree* last_node(CellTree* tree) {
	if (tree == NULL) {
		return NULL;
	}

	//cas de base où tree est la feuille de la plus longue chaine
	if (tree->firstChild == NULL) {
		return tree;
	}

	//cas récursif, on cherche la feuille de la plus longue chaîne
	return last_node(highest_child(tree));
}



//Ex 8 Q8

//retourne une nouvelle liste qui est la fusion de deux listes chaînées de Protected
//duplique les CellProtected mais pas les Protected à l'intérieur
CellProtected* fusion_listes_protected(CellProtected* l1, CellProtected* l2) {
	CellProtected* res = NULL;

	CellProtected* cour = l1;
	while (cour != NULL) {
		ajoute_protected_tete(&res, cour->data);
		cour = cour->next;
	}

	cour = l2;
	while (cour != NULL) {
		ajoute_protected_tete(&res, cour->data);
		cour = cour->next;
	}

	return res;
}


//Ex 8 Q9

//retourne la liste des déclarations contenues dans tous les noeuds de la plus longue chaîne de tree
CellProtected* liste_protected_longest_chain(CellTree* tree) {
	if (tree == NULL) {
		return NULL;
	}

	CellTree* ln = last_node(tree); //on récupère la feuille de la plus longue chaîne
	//printf("last node : %s\n", ln->block->hash);

	//on fusionne sa liste de votes avec celles de ses prédécesseurs
	CellTree* ancetres = ln->father;
	CellProtected* res = ln->block->votes;
	
	while (ancetres != NULL) {
		//printf("appel fusion sur : %s\n", ancetres->block->hash);
		res = fusion_listes_protected(ancetres->block->votes, res);
		ancetres = ancetres->father;
	}
	
	return res;


	/*
	if (tree == NULL) {
		printf("base0 %s\n", tree->block->hash);
		return NULL;
	}
	
	//cas de base où tree est une feuille, on retourne sa liste de votes
	if (tree->firstChild == NULL) {
		if (tree->block != NULL) {
			printf("base %s\n", tree->block->hash);
			return tree->block->votes;
		}
	}

	printf("rec %s\n", tree->block->hash);
	//cas récursif, on descend vers la feuille de la plus longue chaîne, en fusionnant la liste du noeud courant à la liste résultat
	return fusion_listes_protected(tree->block->votes, liste_protected_longest_chain(highest_child(tree)));
	*/
}


//Ex 9 Q1

// permet à un citoyen de soumettre un vote, autrement dit d’ajouter son vote à la fin du fichier "Pending_votes.txt"
void submit_vote(Protected* p){
	if (!p) {
		printf("\nsubmit_vote : parametre valant NULL\n\n") ;
		return;
	}
	
	FILE * f = fopen("Pending_votes.txt", "a") ;
	if (f == NULL) {
		printf("\nsubmit_vote : erreur d'ouverture du fichier\n\n") ;
		return;
	}

	char * pr = protected_to_str(p) ;
	fprintf(f,"%s\n", pr) ;
	free(pr) ;
	fclose(f) ;
}


//Ex 9 Q2

//crée un bloc valide contenant les votes en attente dans le fichier "Pending_votes.txt", supprime le fichier ”Pending votes.txt” après avoir créé le bloc,
//et écrit le bloc obtenu dans un fichier appelé "Pending_block.txt"
//retourne une cellule contenant le bloc créé
CellTree* create_block(CellTree* tree, Key* author, int d){
	CellTree * ln = last_node(tree);

	//création du bloc à partir de Pending_votes.txt
	Block* b = malloc(sizeof(Block));
	if (b == NULL) {
		printf("create_block : erreur d'allocation du bloc\n\n");
		return NULL;
	}
	b->author = author ;
	b->nonce = 0;
	b->votes = read_public_protected("Pending_votes.txt") ;
	remove("Pending_votes.txt");

	if (ln == NULL) { //cas ou l'arbre est vide et qu'il n'y a donc pas de previous_hash
		b->previous_hash = NULL;
	} else {
		b->previous_hash = (unsigned char *) strdup((char*)ln->block->hash);
	}
	compute_proof_of_work(b, d); //initialise b->hash et trouve b->nonce

	//écriture du bloc dans Pending_block.txt
	block_to_file(b, "Pending_block.txt");
	CellTree* res = create_node(b);
	return res;
	//delete_list_protected(&b->votes);
	//delete_block(b);
}


//Ex 9 Q3

//vérifie que le bloc représenté par le fichier "Pending block" est valide. Si c’est le cas, la fonction crée un fichier appelé name représentant
//le bloc, puis l’ajoute dans le répertoire "Blockchain". Dans tous les cas, le fichier ”Pending block” est ensuite supprimé
void add_block(int d, char* name) {
	Block * b = file_to_block("Pending_block.txt") ;
	if (!b) {
		printf("\nadd_block: Block vide\n\n");
		return;
	}

	if (verify_block(b, d) == 1) {
		char path[50] = "./Blockchain/" ;
		strcat(path, name) ;
		block_to_file(b, path);
	}

	remove("Pending_block.txt");
}


//Ex 9 Q4

//construit l’arbre correspondant aux blocs contenus dans le répertoire "Blockchain"
CellTree* read_tree() {
	CellTree* res = NULL;
	DIR * rep = opendir("./Blockchain/") ;
	if (rep == NULL) { 
		fprintf(stderr, "\nread_tree : erreur ouverture dossier\n"); 
	}
 	if (rep != NULL) {

		//construction du tableau de blocs
 		struct dirent * dir ;
 		CellTree ** t = (CellTree**)malloc(sizeof(CellTree*) * 100) ; //tableau des blocs
 		int i = 0 ;
 		while ((dir = readdir(rep)) && i<100) {
 			if ((strcmp(dir->d_name , "." ) != 0) && (strcmp(dir->d_name, "..") != 0)) {
 				char path[50] = "./Blockchain/";
 				strcat(path, dir->d_name) ;
 				t[i] = create_node(file_to_block(path)) ;
 				i++ ;
 			}
    	}
		
		//construction de l'arbre
    	int n = 100; 
		i = 0 ;
    	while(i < n){
    		int j = 0 ;
    		while(j < n){
				//printf("%s\n", t[i]->block->hash);
				//printf("%s\n", t[j]->block->previous_hash);
    			if (i != j && (t[j]->block->previous_hash != NULL) && strcmp((char*)t[i]->block->hash, (char*)t[j]->block->previous_hash) == 0){
					add_child(t[i], t[j]);
    			}
    			j++ ;
    		}
    		i++ ;
    	}
		
		//recherche de la racine
    	i = 0 ;
    	while(i < 100){
    		if (t[i]->father == NULL){
				res = t[i];
				break;   		}
    		i++ ;
    	}

    	free(t) ;
		closedir(rep);
	}
	return res;
}


//Ex 9 Q5

//détermine le gagnant de l’élection en se basant sur la plus longue chaîne de l’arbre
Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
	if (!tree){
		printf("compute_winner_BT : parametre valant NULL\n") ;
		return NULL ;
	}
	
	CellProtected * pr = liste_protected_longest_chain(tree) ; //liste des votes à comptabiliser
	delete_invalided_protected(&pr) ; 
	return compute_winner(pr, candidates, voters, sizeC, sizeV) ;
}
