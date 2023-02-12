#include "nbPremiers.h"

int main() {

	
	srand(time(NULL));

	/*

	//Generation de cle :
	long p = random_prime_number (3 ,7 , 5000);
	long q = random_prime_number (3 ,7 , 5000);

	while (p == q){
	 	q = random_prime_number (3 ,7 , 5000);
	}

	long n, s, u;
	generate_key_values (p, q, &n, &s, &u);
	printf("s:%ld, n:%ld, u:%ld\nq:%ld\n", s, n, u, q);

	//Pour avoir des cles positives :
	if (u <0) {
		long t = (p-1)*(q -1);
		u = u + t; //on aura toujours s*u mod t = 1
	}

	//Afichage des cles en hexadecimal
	printf("cle publique = (%lx, %lx) \n", s, n);
	printf("cle privee = (%lx, %lx) \n", u, n);

	//Chiffrement:
	char mess [10] = "Hello";
	int len = strlen(mess);
	long * crypted = encrypt(mess, s, n);

	printf("Initial message : %s \n", mess);
	printf("Encoded representation : \n");
	print_long_vector(crypted, len);

	//Dechiffrement
	char * decoded = decrypt (crypted, len, u, n);
	printf ("Decoded : %s \n", decoded);

	free(crypted);
	free(decoded);

	*/

	//test de is_prime_naive

	/*
	printf("\n\nTest de is_prime_naive (1 = est premier, 0 = n'est pas premier) :\n\n");

	printf("p = %d : %d\n", -5, is_prime_naive(-5));
	printf("p = %d : %d\n", 1, is_prime_naive(1));
	printf("p = %d : %d\n", 2, is_prime_naive(2));
	printf("p = %d : %d\n", 3, is_prime_naive(3));
	printf("p = %d : %d\n", 22, is_prime_naive(22));
	printf("p = %d : %d\n", 17, is_prime_naive(17));
	printf("p = %d : %d\n", 1003, is_prime_naive(1003));
	printf("p = %d : %d\n", 2003, is_prime_naive(2003));
	*/

	
	//mesure du temps mis pour tester la primalité d'un nombre avec is_prime_naive

	/*
	printf("\n\nTest du plus grand nb premier pouvant etre teste en moins de 2 millisecondes :\n\n");

	long p = 403063;
	
	clock_t tDeb0 = clock();
	int res = is_prime_naive(p);
	clock_t tFin0 = clock();

	double temps_cpu0 = ((double)(tFin0 - tDeb0)) / CLOCKS_PER_SEC;
	printf("p = %ld : %d, temps mis : %lf\n", p, res, temps_cpu0);
	*/


	/*
	//recherche du plus grand nb pouvant être testé en moins de 2 millisecondes avec is_prime_naive
	
	printf("\n\nTest du plus grand nb premier pouvant etre teste en moins de 2 millisecondes :\nOuvrez le ficher listeNbPremTemps.txt pour voir les résultats\n\n");

	FILE* f_lecture = fopen("listeNbPrem.txt", "r");
	FILE* f_ecriture = fopen("listeNbPremTemps.txt", "w");
	if (f_ecriture == NULL || f_lecture == NULL) {
		printf("erreur d'ouverture du fichier\n\n");
		return 1;
	}

	char buffer[20];
	long nb;
	clock_t tDeb;
	clock_t tFin;
	double temps_cpu;
	
	while (fgets(buffer, 20, f_lecture) != 0) {
		if (sscanf(buffer, "%ld\n", &nb) == 1) {
			tDeb = clock();
			is_prime_naive(nb);
			tFin = clock();

			temps_cpu = ((double)(tFin - tDeb)) / CLOCKS_PER_SEC;
			fprintf(f_ecriture, "%ld %lf\n", nb, temps_cpu);
		}
	}

	fclose(f_ecriture);
	fclose(f_lecture);
	*/


	
	//test de modpow_naive
	/*
	printf("\n\nTest de modpow_naive :\n\n");
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 5, 1063, 2159, modpow_naive(5, 1063, 2159));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 48, 94, 65, modpow_naive(48, 94, 65));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 5, 3, 13, modpow_naive(5, 3, 13));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 2, 10, 3, modpow_naive(2, 10, 3));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 4, 6, 9, modpow_naive(4, 6, 9));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", -4, 6, 9, modpow_naive(-4, 6, 9));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 4, -6, 9, modpow_naive(4, -6, 9));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 4, 6, 0, modpow_naive(4, 6, 0));
	printf("a = %d, m = %d, n = %d, resultat = %ld\n", 0, 0, 9, modpow_naive(0, 0, 9));
	*/


	//test de modpow
	/*
	printf("\n\nTest de modpow :\n\n");
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 5, 1063, 2159, modpow(5, 1063, 2159));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 48, 94, 65, modpow(48, 94, 65));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 5, 3, 13, modpow(5, 3, 13));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 2, 10, 3, modpow(2, 10, 3));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 4, 6, 9, modpow(4, 6, 9));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", -4, 6, 9, modpow(-4, 6, 9));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 4, -6, 9, modpow(4, -6, 9));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 4, 6, 0, modpow(4, 6, 0));
	printf("a = %d, m = %d, n = %d, resultat = %d\n", 0, 0, 9, modpow(0, 0, 9));
	*/


	/*
	//comparaison de modpow_naive et modpow
	
	long a = 3;
	long n = 9;
	long m;
	clock_t tDeb1, tDeb2, tFin1, tFin2;
	double temps_cpu1, temps_cpu2; 

	FILE* f_comp = fopen("sortie_comp_modpow.txt", "w");
	if (f_comp == NULL) {
		printf("erreur d'ouverture du fichier");
		return 1;
	}

	for (m=0; m<220; m++) {
		tDeb1 = clock();
		modpow_naive(a, m, n);
		tFin1 = clock();

		tDeb2 = clock();
		modpow(a, m, n);
		tFin2 = clock();
		
		temps_cpu1 = ((double)(tFin1 - tDeb1)) / CLOCKS_PER_SEC;
		temps_cpu2 = ((double)(tFin2 - tDeb2)) / CLOCKS_PER_SEC;
		fprintf(f_comp, "%ld %lf %lf\n", m, temps_cpu1, temps_cpu2);
	}

	fclose(f_comp);
	*/


	//test de random_prime_number
	/*
	int i;
	for (i=0; i<20; i++) {
		long p = random_prime_number(1, 31, 8);
		printf("p = %ld : %d\n", p, is_prime_naive(p));
	}
	*/

	return 0;
}