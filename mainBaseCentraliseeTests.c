#include "nbPremiers.h"
#include "declarationsSecu.h"
#include "baseCentralisee.h"

int main() {

	srand(time(NULL));
	

	
	//test create_cell_key, ajoute_key_tete, read_public_keys, print_list_keys
	printf("\n\nTest create_cell_key, ajoute_key_tete, read_public_keys, print_list_keys :\n\n");

	CellKey* liste1 = read_public_keys("candidates.txt");
	CellKey* liste2 = read_public_keys("keys.txt");
	//print_list_keys(liste1);
	//print_list_keys(liste2);





	//Test create_cell_protected, ajoute_protected_tete, read_public_protected, de print_list_keys
	printf("\n\nTest create_cell_protected, ajoute_protected_tete, read_public_protected, print_list_keys :\n\n");

	CellProtected* listPr = read_public_protected("declarations.txt");
	//print_list_protected(listPr);

	


	/*
	//test_ create_hashtable et delete_hashtable
	printf("\n\nTest de create_hashtable et delete_hashtable :\n\n");
	HashTable * t = create_hashtable(liste1, 10) ;
	//HashTable *t2 = create_hashtable(liste2, 147) ;
	for (int i = 0; i < 10; i++){
		if (t->tab[i]) {
			printf("%ld %ld\n",t->tab[i]->key->val, t->tab[i]->key->n);
		}
		
	}

	delete_hashtable(t);
	*/
	
   


	
    //test de compute_winner
	printf("\n\nTest de compute_winner :\n\n");
	Key* k = compute_winner(listPr, liste1, liste2, 10, 160);
	char* s = key_to_str(k);
	printf("le candidat ayant remporté les élections est : %s\n", s) ;
	free(k);
	free(s);
	





	//test de delete_cell_key et delete_list_keys
	
	delete_list_key(&liste1);
	delete_list_key(&liste2);
	//delete_list_key(&liste1);
	//delete_list_key(&liste2);

	//printf("\n\nAffichage apres suppression :\n\n");
	//print_list_keys(liste1);
	//print_list_keys(liste2);




	
	//Test de delete_elem_protected et delete_invalided_protected, et delete_list_protected
	printf("\n\nTest de delete_elem_protected, delete_invalided_protected,  delete_list_protected :\n\n");

	delete_invalided_protected(&listPr);
	//print_list_protected(listPr);
	delete_list_protected(&listPr);
	//delete_list_protected(&listPr);
	//print_list_protected(listPr);
	



	/*
	//Test de hash_function
	printf("\n\nTest de hash_function :\n\n");
	Key* k1 = malloc(sizeof(Key));
	Key* k2 = malloc(sizeof(Key));
	init_pair_keys(k1, k2, 3, 7);
	printf("%d\n", hash_function(k1, 200));
	printf("%d\n", hash_function(k2, 200));
	free(k1);
	free(k2);
	//Tests supplémentaires à faire !!!
	*/
	

	return 0;
}