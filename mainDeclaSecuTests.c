#include "declarationsSecu.h"
#include "nbPremiers.h"

int main() {
	
 	srand ( time ( NULL ) ) ;


 	//Testing Init Keys

	Key * pKey = malloc ( sizeof ( Key ) ) ;
	Key * sKey = malloc ( sizeof ( Key ) ) ;
	init_pair_keys ( pKey , sKey ,3 ,7) ;
	printf ( "pKey : %lx , %lx \n" , pKey -> val , pKey -> n ) ;
	printf ( "sKey : %lx , %lx \n" , sKey -> val , sKey -> n ) ;


	//Testing Key Serialization
	char * chaine = key_to_str ( pKey ) ;
	printf ( "key to str : %s \n" , chaine ) ;
	Key * k = str_to_key ( chaine ) ;
	printf ( "str to key : %lx,%lx \n" , k -> val , k -> n ) ;


	//Testing signature
	//Candidate keys:
	Key * pKeyC = malloc ( sizeof ( Key ) ) ;
	Key * sKeyC = malloc ( sizeof ( Key ) ) ;
	init_pair_keys(pKeyC, sKeyC, 3, 7);


	//Declaration:
	char * mess = key_to_str(pKeyC);
	char* s1 = key_to_str(pKey);
	printf("%s vote pour %s\n", s1, mess);
	free(s1);

	Signature * sgn1 = sign(mess, sKey);
	printf("signature : ");
	print_long_vector(sgn1 -> content, sgn1 -> size);

	char* s2 = signature_to_str(sgn1);
	printf("signature to str : %s\n", s2);

	Signature* sgn2 = str_to_signature(s2);
	printf("str to signature : ");
	print_long_vector( sgn2 -> content, sgn2 -> size);


	//Testing protected:
	Protected * pr1 = init_protected(pKey, mess, sgn1);


	//Verification:
	if (verify(pr1)) {
		printf("Signature valide \n");
	}else {
	 	printf("Signature non valide \n");
	}

	char* s3 = protected_to_str(pr1);
	printf("protected to str : %s \n", s3);

	
	Protected* pr2 = str_to_protected(s3);

	
	char* s4 = key_to_str(pr2 -> pKey);
	char* s5 = signature_to_str(pr2 -> sgn);
	printf("str to protected : %s %s %s \n", s4, pr2 -> mess, s5);



	free(pKey);
	free(sKey);

	free(chaine);
	free(k);

	free(pKeyC);
	free(sKeyC);

	free(mess);
	free(sgn1->content);
	free(sgn1);
	free(s2);
	free(sgn2->content);
	free(sgn2);

	free(pr1->mess);
	free(pr1);

	free(s3);
	free(s4);
	free(s5);
	free(pr2->mess);
	free(pr2->pKey);
	free(pr2->sgn->content);
	free(pr2->sgn);
	free(pr2);



	//test de generate_random_data
    generate_random_data(15, 3);
	
	return 0;
}