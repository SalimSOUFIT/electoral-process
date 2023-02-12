#include "baseCentralisee.h"

//// Partie 3

//Ex 5 Q1

//alloue et initialise une cellule de liste chaînée de Key
CellKey* create_cell_key(Key* key) {
	if (key == NULL) {
		printf("create_cell_key : parametre NULL\n\n");
		return NULL;
	}

	CellKey* cell = malloc(sizeof(CellKey)); //cellule résultat
	if (cell == NULL) {
		printf("create_cell_key : erreur d'allocation du resultat\n\n");
		return NULL;
	}

	cell->data = key;
	cell->next = NULL;
	return cell;
}

//Ex 5 Q2

//ajoute une clé en tête de liste, retourne NULL en cas d'erreur lors de l'ajout
CellKey* ajoute_key_tete(CellKey** pListe, Key* key) {
	if (key == NULL || pListe == NULL) {
		printf("ajoute_key_tete : key ou liste n'est pas alloue\n\n");
		return NULL;
	}
	CellKey* new = create_cell_key(key);
	if (new == NULL) {
		printf("ajoute_key_tete : erreur de creation de la cellule\n\n");
		return NULL;
	}

	new->next = *pListe;
	*pListe = new;
	return new;
}

//Ex 5 Q3

//retourne une liste chaînée contenant toutes les clés publiques contenues dans le fichier
CellKey* read_public_keys(char* nomFichier) {
	FILE* f = fopen(nomFichier, "r");
	if (f == NULL) {
		printf("read_public_keys : erreur d'ouverture du fichier\n\n");
		return NULL;
	}

	char buffer[256];
	Key* key; //clé courante
	CellKey* liste = NULL; //liste résultat

	while (fgets(buffer, 256, f) != NULL) {
		key = str_to_key(buffer); //s'il s'agit du fichier keys.txt, le programme ne lira que la 1ère clé sur chaque ligne et ignorera la 2ème
		if(key == NULL) {
			printf("read_public_keys : erreur de lecture de la cle\n\n");
			return liste;
		} else {
			ajoute_key_tete(&liste, key);
		}
	}

	fclose(f);
	return liste;
}

//Ex 5 Q4

//affiche une liste chaînée de clés
void print_list_keys(CellKey* LCK) {
	CellKey* l = LCK ;

	if (l == NULL) {
		printf("La liste est vide\n\n");
		return;
	}

	while (l != NULL) {
		char* s = key_to_str(l->data);
		printf("%s\n", s);
		free(s);
		l = l->next;
	}
}

//Ex 5 Q5

//supprime une cellule CellKey
void delete_cell_key(CellKey* c) {
	if (c != NULL) {
		free(c->data);
	}
	free(c);
}

//supprime une liste chaînée de clés
void delete_list_key(CellKey** pLCK) {
	if(pLCK == NULL || *pLCK == NULL) { //si la liste est inexistante ou si elle est vide
		return;
	}
	
	CellKey* temp;
	CellKey* cour = *pLCK; //élément courant

	while(cour != NULL) {
		temp = cour->next;
		delete_cell_key(cour);
		cour = temp;
	}

	*pLCK = NULL; //on remet le pointeur sur le premier élément à NULL, pour ne pas qu'il pointe sur un espace mémoire libéré
}

//Ex 5 Q6

//alloue et initialise une cellule de liste chaînée de Protected
CellProtected* create_cell_protected(Protected* pr){
	if (pr == NULL){
		printf("create_cell_protected : parametre NULL\n\n");
		return NULL;    
	}

	CellProtected* cell = (CellProtected*)malloc(sizeof(CellProtected));
	if (cell == NULL) {
		printf("create_cell_protected : erreur d'allocation de la cellule\n\n");
		return NULL;
	}

	cell -> data = pr ;
	cell->next = NULL ;
	return cell ;
}

//Ex 5 Q7

//ajoute une déclaration en tête de liste
CellProtected* ajoute_protected_tete(CellProtected ** pListe, Protected* pr){
	 if (pr == NULL || pListe == NULL) { 
		printf("ajoute_protected_tete : parametre(s) NULL\n\n");
		return NULL;
	}

	CellProtected* new = create_cell_protected(pr);
	if (new == NULL) {
		printf("ajoute_protected_tete : erreur de creation de la cellule\n\n");
		return NULL;
	}

	new->next = *pListe;
	*pListe = new;
	return new;
}

//Ex 5 Q8

//retourne une liste chaînée contenant toutes les déclarations signées contenues dans le fichier
CellProtected* read_public_protected(char* nomFichier) {
	FILE* f = fopen(nomFichier, "r");
	if (f == NULL) {
		printf("read_public_protected : erreur d'ouverture du fichier\n\n") ;
		return NULL ;
	}

	char buffer[256] ;
	Protected* pr ; //Protected courant
	CellProtected* liste = NULL ; //liste résultat

	while (fgets(buffer, 256, f) != NULL) {
		pr = str_to_protected(buffer);
		if(pr == NULL) {
			printf("read_public_protected : erreur de lecture \n\n") ;
			return liste ;
		} else {
			ajoute_protected_tete(&liste, pr) ;
		}
	}
	fclose(f);

	return liste ;
}

//Ex 5 Q9

//affiche une liste chaînée de déclarations
void print_list_protected(CellProtected* LCP) {
	CellProtected* l = LCP ;

	if (l == NULL) {
		printf("La liste est vide\n\n") ;
		return ;
	}

	while (l != NULL) {
		char* s = protected_to_str(l->data);
		printf("%s\n", s);
		free(s);
		l = l->next ;
	}
}

//Ex 5 Q10

//supprime une cellule
void delete_cell_protected(CellProtected* c){
	   if (c) {
		free(c->data->pKey) ;
		free(c->data->mess) ;
		free(c->data->sgn->content) ;
		free(c->data->sgn) ;
		free(c->data) ;
	}
	free(c) ;
}

//supprime une liste chaînée de déclaration
void delete_list_protected(CellProtected** pLCP) {
	if(pLCP == NULL || *pLCP == NULL) { //si la liste est inexistante ou si elle est nulle
		return;
	}

	CellProtected* temp;
	CellProtected* cour = *pLCP; //élément courant

	while(cour != NULL) {
		temp = cour;
		cour = cour->next;
		delete_cell_protected(temp);
	}
	
	*pLCP = NULL; //on remet le pointeur sur le premier élément à NULL, pour ne pas qu'il pointe sur un espace mémoire libéré
}

//Ex 6 Q1

//supprime un élement dans la liste chainée
void delete_elem_protected(CellProtected** pListe, Protected* pr){
	if (!pListe){
		 printf("delete_elem_protected : liste inexistante\n\n") ;
		return ;
	}

	CellProtected* cour = *pListe; //élément courant

	//cas où la cellule à supprimer est en tête de liste
	if (cour->data == pr){
		CellProtected* temp = cour ;
		cour = cour->next ;
		delete_cell_protected(temp) ;
		return;
	}

	//cas où la cellule est quelque part au milieu ou si elle est en dernière position
	CellProtected* temp2 ;
	temp2 = cour->next ; //temp2 représente l'élément suivant l'élément courant

	while(temp2 && temp2->data != pr){
		cour = temp2 ;
		temp2 = temp2->next ;
	}

	if (temp2){ //si temp2 != NULL après la boucle, c'est qu'il pointe sur l'élément à supprimer
		cour->next = temp2->next ;
		delete_cell_protected(temp2) ;
	}
}

// supprime toutes les déclarations dont la signature n’est pas valide, retourne le nombre de suppressions faites, retourne -1 en cas d'erreur
int delete_invalided_protected(CellProtected** pListe) {
	if (pListe == NULL){
		printf("delete_invalided_protected : liste inexistante\n\n") ;
		return -1 ;
	}

	printf("Suppression des declarations invalides en cours...\n\n") ;
	CellProtected* temp = *pListe ; //élément courant
	int n = 0; //compte des déclarations invalides supprimées

	while(temp){
		if (verify(temp->data) == 0){
			delete_elem_protected(pListe, temp->data) ; //supprime la fausse signature
			n++;
			temp = *pListe ; 
		}
		else {
			temp = temp->next ;
		}
	}

	printf("Suppression terminee : %d declaration(s) invalide(s) supprimee(s)\n\n", n) ;
	return n;
}

//Ex 6 Q2

//alloue et initialise une cellule HashCell
HashCell* create_hashcell(Key* key) {
	if (key == NULL) {
		printf("create_hashcell : parametre NULL\n\n");
		return NULL;
	}

	HashCell* cell = malloc(sizeof(HashCell)); //cellule résultat
	if (cell == NULL) {
		printf("create_hashcell : erreur d'allocation du resultat\n\n");
		return NULL;
	}

	cell->key = (Key*)malloc(sizeof(Key));
	cell->key->val = key->val ;
	cell->key->n = key->n ;
	cell->val = 0;
	return cell;
}

//Ex 6 Q3

//retourne la clé hachée, qui indique la position de l'élément dans la table de hachage (-1 en cas d'erreur)
//pour une explication plus détaillée sur cette fonction et ses tests, consulter le compte-rendu
int hash_function(Key* key, int size) { 
	if (key == NULL) {
		printf("hash_function : key n'est pas alloue\n\n");
		return -1;
	}

	//Transformation de key en un entier
	long cle = key->val + (key->n)%10; 

	//Transformation de l'entier pour qu'il soit sur la bonne plage
	float A = (sqrt(5)-1) / 2; //nombre d'or diminué de 1
	int cleH = (int)size * (cle*A - (int)(cle*A));

	return cleH;
}

//Ex 6 Q4

//cherche dans la table de hachage s'il existe un élément dont la clé publique est key et retourne sa position (ou la position qu'il aurait dû avoir si on ne le trouve pas, ou -1 en cas d'erreur)
int find_position(HashTable* t, Key* key) {
	if (t == NULL || key == NULL) {
		printf("find_position : parametre(s) NULL\n\n");
		return -1;
	}
	if (t->tab == NULL) {
		printf("find_position : la table de hachage est inexistante\n\n");
		return -1;
	}

	HashCell** table = t->tab;
	int indice = hash_function(key, t->size); //calcul de l'indice
	int i = indice;
	int compte = 0; //compte le nombre de cases visitées

	while (table[i] != NULL && !(table[i]->key->n == key->n && table[i]->key->val == key->val)) {
		if (i == t->size - 1) { //cas où on arrive au bout de la table : on continue le probing au début de la table
			i = 0;
		} else { //cas moyen : on passe à la case suivante
			i++;
		}
		compte++;

		if (compte == t->size) { //cas où on a essayé toutes les cases de la table, sans succès
			return indice;
		}
	}

	return i;
}

//Ex 6 Q5

//crée et initialise une table de hachage de taille size contenant une cellule pour chaque clé de la liste chainnée keys
 HashTable * create_hashtable(CellKey* keys, int size){
 	if (!keys){
 		printf("create_hashtable : parametre(s) NULL\n\n") ;
 		return NULL ;
 	}

 	//création de la table de hachage 
 	HashTable * t = (HashTable*)malloc(sizeof(HashTable)) ;
	if (t == NULL) {
		printf("create_hashtable : erreur d'allocation de la table\n\n");
		return NULL;
	}

 	t->tab = (HashCell**)malloc(sizeof(HashCell*)*size) ;
	if (t->tab == NULL) {
		printf("create_hashtable : erreur d'allocation de la table\n\n");
		free(t);
		return NULL;
	}
 	t->size = size ;

 	//initialisation des cases à NULL
 	for (int i = 0; i < size; ++i){
 		t->tab[i] = NULL ;
 	}

	//insertion des clés dans la table
 	int i = 0 ;
 	while (keys && (i < size)) { // on ne peut pas mettre plus de i éléments dans la table
 		int pos = find_position(t, keys->data) ;
 		if (pos == -1){
 			printf("create_hashtable : pos == -1\n\n");
			keys = keys->next;
 			i++;
 			break; //on ne pourra pas insérer cette clé à l'indice -1 donc on passe à l'itération suivante
 		}

		HashCell* cell = create_hashcell(keys->data) ;
 		t->tab[pos] = cell ;
 		keys = keys->next ;
 		i++;
 	}

 	return t ;
 }

//Ex 6 Q6

//supprime une table de hachage
void delete_hashtable(HashTable* t){
	if (!t) {
		return;
	}

	if(t->tab == NULL) {
		free(t);
		return;
	}

	for (int i = 0; i < t->size; i++){
		if (t->tab[i]){
			if (t->tab[i]->key){
				free(t->tab[i]->key) ;
			}
			free(t->tab[i]) ;
		}
	}
	free(t->tab);
	free(t);
}

//Ex 6 Q7

//calcule le vainqueur de l’élection, étant donnés une liste de déclarations avec signatures valides (decl),
//une liste de candidats (candidates), et une liste de personnes autorisées à voter (voters)
Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){

	HashTable * Hc = create_hashtable(candidates, sizeC) ;
	HashTable * Hv = create_hashtable(voters, sizeV) ;
	CellProtected *  temp = decl ; //déclaration courante

	while(temp){

		//on vérifie que le candidat est dans la liste des candidats, et que le votant est dans la liste des votants
		Key* k = str_to_key(temp->data->mess);
		int j = find_position(Hc, k) ; 
		int i = find_position(Hv, temp->data->pKey) ;
		free(k);

		if(i == -1 || j == -1){
			printf("\n\ncompute_winner : Erreur dans la liste des votants/candidats\n\n");
			return NULL;
		}

		//on comptabilise le vote (mais seulement si le votant n'a pas déjà voté)
		if (Hv->tab[i]->val == 0) {
			Hc->tab[j]->val ++ ;
			Hv->tab[i]->val = 1 ;
		}
	
		temp = temp->next ;
	}

	//on cherche le candidat qui a le nombre max de votes
	//on initialise ce candidat avec le 1er candidat de la table (1ère case non nulle)
	int i = 0 ;
	while(Hc->tab[i] == NULL){
		i++ ;
	}
	HashCell * hMax = Hc->tab[i];

	//on cherche le candidat qui a le nombre max de votes, si plusieurs candidats sont à égalité on retourne le 1er que l'on a trouvé
	i++ ;
	while(i < sizeC ){
		if (Hc->tab[i] && (hMax->val < Hc->tab[i]->val)){
			hMax = Hc->tab[i];
		}
		i++ ;
	}

	Key* res = malloc(sizeof(Key));
	res->val = hMax->key->val;
	res->n = hMax->key->n;
	delete_hashtable(Hv);
	delete_hashtable(Hc);

	return res ;


}

