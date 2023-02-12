#include "declarationsSecu.h"


//// Partie 2

//Ex 3 Q2

//initialise une clé déjà allouée avec le couple (val,n) (val = s ou u selon la clé)
void init_key(Key* key, long val, long n) {
    if (key == NULL) {
        printf("init_key : key n'est pas alloue\n");
        return;
    }

    key->val = val;
    key->n = n;
}

//Ex 3 Q3

//initialise un couple (clé publique, clé secrète) déjà alloué avec le protocole RSA
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size) {
    if (pKey == NULL || sKey == NULL) {
        printf("init_pair_key : pKey ou sKey n'est pas alloue\n");
        return;
    }

    //génération des clés
    long p = random_prime_number(low_size, up_size, 5000);
	long q = random_prime_number(low_size, up_size, 5000);

	while (p == q){
	 	q = random_prime_number(low_size, up_size, 5000);
	}

	long n, s, u;
	generate_key_values(p, q, &n, &s, &u);

    if (u <0) { // pour avoir des clés positives
		long t = (p-1)*(q-1);
		u = u + t; //on aura toujours s*u mod t = 1
	}

    //initialisation des clés
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

//Ex 3 Q4

//retourne la clé sous forme de caractères
char* key_to_str(Key* key) {
    if (key == NULL) {
        printf("key_to_str : key n'est pas alloue\n");
        return NULL;
    }

    char* cle = malloc(sizeof(char)*12); //un long est sur 32 bits, sous forme héxadecimale il prend au maximum 8 caractères (plus la place pour le marqueur de fin, les parenthèses, la virgule)
    if (cle == NULL) {
        printf("key_to_str : erreur d'allocation de la chaine\n");
        return NULL;
    }
    sprintf(cle, "(%lx,%lx)", (unsigned long)key->val, (unsigned long)key->n); //les clés sont des long toujours positifs alors on peut les caster vers des unsigned long sans aucun problème
    return cle;
}

//retourne la clé sous forme d'une structure Key
Key* str_to_key(char* str) {
    if (str == NULL) {
        printf("str_to_key : str est vide\n");
        return NULL;
    }

    Key* key = malloc(sizeof(Key)); //clé résultat
    if (key == NULL) {
        printf("str_to_key : erreur d'allocation de la cle\n");
        return NULL;
    }

    unsigned long val, n;
    if (sscanf(str, "(%lx,%lx)\n", &val, &n) == 2) { //on ne retourne le résultat que si les 2 valeurs ont été relevées correctement
        init_key(key, (long)val, (long)n);
    } else {
        printf("str_to_key : erreur de lecture de la cle\n");
        return NULL;
    }

    return key;
}

//Ex 3 Q6

//alloue et initialise une signature. Le paramètre content doit être déjà initialisé !
Signature* init_signature(long* content, int size) {
    Signature* signature = malloc(sizeof(Signature));  //signature résultat
    if (signature == NULL) { 
        printf("init_signature : erreur d'allocation\n\n");
        return NULL;
    }

    signature->size = size;
    signature->content = content;

    return signature;
}

//Ex 3 Q7

//crée une signature à partir du message et de la clé secrète
Signature* sign(char* mess, Key* sKey) {
    if (mess == NULL || sKey == NULL) {
        printf("sign : parametre(s) valant NULL\n\n");
        return NULL;
    }

    Signature* signature = init_signature(encrypt(mess, sKey->val, sKey->n), strlen(mess));

    return signature;
}

//Ex 3 Q8

//retourne une signature sous forme de caractères
char * signature_to_str (Signature * sgn) {
    char * result = malloc(10*sgn -> size * sizeof(char));
    result [0]= '#';
    int pos = 1;
    char buffer [156];
    for (int i =0; i < sgn -> size; i++) {
        sprintf(buffer, "%lx", sgn -> content[i]);
        for(int j=0; j < (int)strlen(buffer); j++){
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos = pos+1;
    }
    result[pos] = '\0';
    result = realloc(result, (pos+1)* sizeof(char));
    return result;
}

//retourne la structure signature correspondant à la chaine passée en paramètres
Signature * str_to_signature(char * str){
    int len = strlen(str);
    long * content = (long*)malloc(sizeof(long)*len);
    int num = 0 ;
    char buffer [256] ;
    int pos = 0 ;
    for ( int i =0; i < len ; i ++) {
        if ( str [ i ] != '#' ) {
            buffer [ pos ] = str [ i ] ;
            pos = pos +1 ;
        } else {
            if ( pos != 0) {
                buffer[pos] =  '\0'  ;
                sscanf (buffer , "%lx" , (long unsigned int*)&(content[num])) ;
                num = num + 1 ;
                pos = 0 ;
            }
        }
    }
    content = realloc ( content , num * sizeof ( long ) ) ;
    return init_signature ( content , num ) ;
}


//Ex 3 Q10

//alloue et initialise une signature
Protected * init_protected(Key* pKey, char* mess, Signature* sgn) {
    if (!pKey || !mess || !sgn){
        printf("init_protected : parametre(s) valant NULL\n\n") ;
        return NULL ;
    }
    Protected * p = (Protected*)malloc(sizeof(Protected)) ;
    if  (p == NULL) {
        printf("init_protected : erreur d'allocation du resultat\n\n");
        return NULL;
    }

    p->pKey = pKey ;
    p->mess = strdup(mess) ;
    p->sgn = sgn ;
    return p ;
}

//Ex 3 Q11

//retourne 1 si la signature est valide, 0 sinon
int verify(Protected* pr){
    if (!pr){
        printf("verify : parametre valant NULL\n\n") ;
        return 0;
    }
    char * decrypted = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);
    if (strcmp(decrypted, pr->mess) == 0){
        free(decrypted);
        return 1 ;
    } else {
        free(decrypted);
        return 0 ;
    }

}

//Ex 3 Q12

//renvoie une chaine de caractères représentant le Protected
char * protected_to_str(Protected * pr){
    if (!pr){
        printf("protected_to_str : parametre valant NULL\n\n");
        return NULL ;
    }

    char* c = key_to_str(pr->pKey);
    char* s = signature_to_str(pr->sgn);
    char* res = malloc(3 + strlen(c) + strlen(pr->mess) + strlen(s));
    sprintf(res, "%s %s %s", c, pr->mess, s);
    free(c);
    free(s);

    return res ;
}

//renvoie le Protected correspondant à la chaine passée en paramètre
Protected * str_to_protected(char * ps){
    if (!ps){
        printf("str_to_protected : parametre NULL\n\n");
        return NULL ;
    }

    char * skey, * mess, *ssgn ;
    int size[]={0,0,0} ;
    int j = 0, i = 0 ;

    //on calcule les tailles des trois composants de la chaine et on les stocke dans size[]
    while(i < (int)strlen(ps)){
        size[j]++;
        if (ps[i] == ')'){
            size[j] += 2; //pour compter la parenthèse fermante et le marqueur de fin
            j++ ;
        }
        i++;
    }

    skey = (char*)malloc(sizeof(char)*size[0]) ; 
    mess = (char*)malloc(sizeof(char)*size[1]) ; 
    ssgn = (char*)malloc(sizeof(char)*size[2]) ;

    if (sscanf(ps, "%s %s %s\n", skey, mess, ssgn) == 3) { //on ne retourne le résultat que si les 3 composants ont été relevés correctement
        Key * k = str_to_key(skey);
        Signature * sgn = str_to_signature(ssgn) ;
        Protected* res = init_protected(k, mess, sgn);
        free(mess);
        free(skey);
        free(ssgn);
        return res;
    }

    printf("str_to_protected : erreur de lecture de la chaine\n\n");
    return NULL;
}

//Ex 4 Q1

//verifie l'existence d'une valeur dans un tableau
int if_exists(int n, Key * c, Key * k){
    for (int i = 0; i < n; i++){
        if (c[i].val == k->val && c[i].n == k->n){
            return 1 ;
        }
    }
    return 0 ;
} 

//crée des fichiers de données pour simuler le vote (liste de votants, liste de Candidats, liste de votes)
void generate_random_data(int nv, int nc){
    if (nv < nc ){
        printf("generate_random_data : parametres incorrects, il y a moins de citoyens que de candidatss\n\n");
        return; 
    }

    Key keysCitoyen[nv][2] ; //tableau contenant toutes les paires de clés de tous les citoyens
    Key listeCandidats[nc]; //tableau contenant les clés publiques de tous les candidats
    Signature* signatureCourante;
    FILE *f1, *f2, *f3 ;
    Protected * prCourant;

    //génération du fichier contenant les cartes électorales de tous les citoyens
    f1 = fopen("keys.txt", "w") ;
    for (int i = 0; i < nv; i ++){
        init_pair_keys(&keysCitoyen[i][0], &keysCitoyen[i][1], LOW_SIZE, UP_SIZE) ;

        char* s1 = key_to_str(&keysCitoyen[i][0]);
        char* s2 = key_to_str(&keysCitoyen[i][1]);
        fprintf(f1, "%s %s\n", s1, s2) ;
        free(s1);
        free(s2);
    }

    //génération du fichier contenant les clés publiques des Candidats
    f2 = fopen("candidates.txt", "w") ;
    for (int i = 0; i < nc; i ++){
        int j = (int) rand_long(0, nv) ;
        while(if_exists(nc, listeCandidats, &keysCitoyen[j][0]) == 1){
            j = (int) rand_long(0, nv) ;
        }
        listeCandidats[i].val = keysCitoyen[j][0].val ; 
        listeCandidats[i].n = keysCitoyen[j][0].n ;

        char* s = key_to_str(&listeCandidats[i]);
        fprintf(f2, "%s\n", s) ;
        free(s);
    }

    //génération du fichier contenant les déclarations de vote signées
    f3 = fopen("declarations.txt", "w") ;
    for (int i = 0; i < nv; ++i){
        int j = (int)rand_long(0,(nc-1)) ;

        char* s2 = key_to_str(&listeCandidats[j]);
        //signatures[i] = sign(s2, &keysCitoyen[i][1]);
        signatureCourante = sign(s2, &keysCitoyen[i][1]);

        prCourant = init_protected(&keysCitoyen[i][0], s2, signatureCourante) ;
        free(s2);

        char* s = protected_to_str(prCourant);
        fprintf(f3, "%s\n", s) ;
        free(s);
        free(signatureCourante->content);
        free(signatureCourante);
        free(prCourant->mess);
        free(prCourant);
    }

    fclose(f1) ; fclose(f2) ; fclose(f3) ;
}


