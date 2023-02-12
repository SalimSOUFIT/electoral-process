#include "nbPremiers.h"

//// Partie 1

//Ex 1 Q1

//retourne 1 si p est un nombre premier, retourne 0 sinon
int is_prime_naive(long p) {
	if (p < 2) {
		return 0;
	}
	else if (p == 2) { 
		return 1;
	}
	else if (p%2 == 0) { //si p est pair et que ce n'est pas 2, alors il n'est pas premier (évite p itérations inutiles)
		return 0;
	}
	else {
		long i; //dès qu'on trouve un diviseur de p dans l'intervalle [3, p-1], on sait que p n'est pas premier
		for (i=3; i<p; i++) {
			if (p%i == 0) {
				return 0;
			}
		}
	}
	return 1;
}

//Ex 1 Q3

//retourne la valeur de a^m mod n, retourne -1 en cas de paramètre(s) invalide(s)
long modpow_naive(long a, long m, long n) {
	if (n < 1 || a < 0 || m < 0 || (m == 0 && a == 0)) { //on veut éviter la division par 0, les paramètres strictement négatifs ainsi que le "0 puissance 0" qui est indéfini en mathématiques
		return -1;
	}
	if (a == 0) { //on évite potentiellement plein d'itérations inutiles, car 0^m = 0 et 0 mod n = 0, pour tous entiers naturels m et n
		return 0;
	}

	long res = 1;
	long i;
	for (i=0; i<m; i++) {
		res = (res*a)%n;
	}
	return res;
}

//Ex 1 Q4

//retourne la valeur de a^m mod n, retourne -1 en cas de paramètres(s) invalide(s)
long modpow(long a, long m, long n) {
	if (n < 1 || a < 0 || m < 0 || (m == 0 && a == 0)) { //on veut éviter la division par 0, les paramètres négatifs ainsi que le "0 puissance 0" qui est indéfini en mathématiques
		return -1;
	}
	if (a == 0) { //on évite potentiellement plein d'itérations inutiles, car 0^m = 0 et 0 mod n = 0, pour tous entiers naturels m et n
		return 0;
	}

	long temp = a;
	long res = 1;
	while (m > 0) { //simultanément : on décompose m en base 2, on calcule les élévations au carré, on met à jour le résultat si nécessaire
		if (m%2 == 1) {
			res = (temp*res)%n;
		}
	m = m/2;
	temp = (temp*temp)%n;
	}
	return (int)res;
}

//Ex 1 Q6

//retourne 1 si a est un témoin de Miller pour p, sinon retourne 0
int witness(long a, long b, long d, long p) {
	long x = modpow(a, d, p);
	if (x == 1) {
		return 0;
	}

	long i;
	for (i=0; i<b; i++) {
		if (x == p-1) {
			return 0;
		}
		x = modpow(x, 2, p);
	}

	return 1;
}

//retourne un long aléatoire compris entre low et up inclus
long rand_long(long low, long up) {
	return rand()%(up - low + 1) + low;
}

//retourne 1 si p est probablement premier (si p n'est pas premier, avec certitude, retourne 0), en utilisant la méthode de Miller-Rabin avec k tests
int is_prime_miller(long p, int k) {
	if (p == 2) {
		return 1;
	}
	if (!(p & 1) || (p <= 1)) { //on vérifie que p est impair et différent de 1
		return 0;
	}

	//on détermine b et d
	long b = 0;
	long d = p-1;
	while (!(d & 1)) { //tant que d n'est pas impair
		d = d/2;
		b = b+1;
	}

	//on génère k valeurs pour a, et on teste si c'est un témoin
	long a;
	int i;
	for (i=0; i<k; i++) {
		a = rand_long(2, p-1);
		if (witness(a, b, d, p)) {
			return 0;
		}
	}

	return 1;
}

//Ex 1 Q8

//retourne un nombre premier de taille comprise entre low_size et up_size, testé avec k tests de Miller
long random_prime_number(int low_size, int up_size, int k) {
	int flag1 = 0; 
	int flag2;
	long p;

	if ((low_size < 1) || (up_size > 31)) {
		printf("random_prime_number : parametres incorrects\n");
		return -1;
	}

	while (flag1 == 0) { //flag1 n'est jamais mis à jour, la boucle pourrait théoriquement être infinie mais le théorème des nombres premiers dit qu'on finit par trouver un p qui est premier après un nombre fini d'essais
		p = rand_long(1<<(low_size-1), (1<<up_size) - 1); //on génère un entier p au hasard de la bonne taille

		flag2 = 1;
		int i;
		for (i=0; i<k; i++) { //on le teste k fois avec le test de Miller
			if (is_prime_miller(p, k) == 0) {
				flag2 = 0;
				break; //si p n'est pas premier on sort de la boucle for pour recommencer avec un nouvel entier p
			}
		}
		if (flag2 == 1) { //si flag2 est resté à 1 alors tous les tests ont réussi et p est probablement premier, donc on le retourne
			return p;
		}
	}

	return -1;
}

//Ex 2 Q1

//calcule la valeur PGCD(s,t) et on détermine les entiers u (x ici) et v (y ici) vérifiant l’équation de Bezout
long extended_gcd(long a, long b, long *x, long *y){
    if (a == 0){
        *x = 0;
        *y = 1;
        return b;
    }
 	long _x, _y;
    long gcd = extended_gcd(b % a, a, &_x, &_y);
 	*x = _y - (b/a) * _x;
    *y = _x;
 
    return gcd;
}

//génère la clé_public(s,n) et la clé_secrète(u,n), à partir des nombres premiers p et q, en suivant le protocole RSA
void generate_key_values(long p, long q, long *n, long *s, long *u) {
	if (is_prime_miller(p, p-1) == 0 || is_prime_miller(q, q-1) == 0){ //si p(ou q) n'est pas premier, retoune un message d'erreur
		printf("generate_key_values : les entiers p,q ne sont pas premiers\n") ;
		return ;
	}

	*n = p * q ;
	long t = (p - 1) * (q - 1) ;
	long  v_temp = 0 ;
	*s= rand_long(2, t - 1) ;

	while(extended_gcd(*s, t, u, &v_temp) != 1){
		*s = rand_long(2, t - 1) ;	
	}
}

//Ex 2 Q2
//chiffre la chaine de caractère chaine avec la clé_public(s,n), en convertissant chaque caractère en un entier de type int, retourne un tableau de long
long * encrypt(char * chaine, long s, long n) {
	if (!chaine){// si chaine est NULL, on retourne NULL
		printf("encrypt : la chaine de caractères est vide\n") ;
		return NULL ;
	}

	long * tab_encrypt = (long*)malloc(sizeof(long) * strlen(chaine)) ;
	int m;

	for (int i = 0; i < (int)strlen(chaine); i++){
		m = chaine[i] ;//convertit chaque caractère en un entier de type int
		tab_encrypt[i] = modpow(m, s, n) ;//chiffre l'entier m avec la clé_public(s,n)
	}

	return tab_encrypt ;
}

//Ex 2 Q3
//déchiffre un message à l'aide de la clé_secrète(u,n) en connaissant la taille du tableau d'entiers et renvoie une chaine de caractères
char * decrypt(long * crypted, int size, long u, long n) {
	if (!crypted){ //si le tableau crypted est vide, on renvoie NULL
		printf("decrypt : le tableau est vide\n") ;
		return NULL;
	}

	char * s_decrypted = (char*)malloc(sizeof(char)*size + 1) ; //+1 pour le marqeur de fin de chaine
	for (int i = 0; i < size; i++){
		s_decrypted[i] = (char)modpow(crypted[i], u, n); //déchiffre l'entier crypted[i] avec la clé_secrète(u,n), puis le convertit en un caractère
	}
	s_decrypted[size] = '\0';
	return s_decrypted;
}

//affiche le tableau contenant les valeurs de type long en hexadécimal
void print_long_vector(long * result, int size) {
	printf("Vector : [    " );
	for (int i=0; i < size; i ++) {
		printf("%lx\t", result[i]);
	}
	printf("] \n");
}