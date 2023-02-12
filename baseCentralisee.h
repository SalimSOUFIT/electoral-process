#ifndef BASECENTRALISEE_H
#define BASECENTRALISEE_H

#include "declarationsSecu.h"

typedef struct cellKey {
    Key* data;
    struct cellKey* next;
} CellKey;

CellKey* create_cell_key(Key* key);

CellKey* ajoute_key_tete(CellKey** pListe, Key* key);

CellKey* read_public_keys(char* nomFichier);

void print_list_keys(CellKey* LCK);

void delete_cell_key(CellKey* c);

void delete_list_key(CellKey** pLCK);

typedef struct cellProtected {
    Protected * data ;
    struct cellProtected * next ;
 } CellProtected ;

CellProtected* create_cell_protected(Protected* pr) ;

CellProtected* ajoute_protected_tete(CellProtected ** pListe,Protected* pr) ;

CellProtected* read_public_protected(char* nomFichier) ;

void print_list_protected(CellProtected* LCP) ;

void delete_cell_protected(CellProtected* c) ;

void delete_list_protected(CellProtected** pLCP) ;

void delete_elem_protected(CellProtected** pListe, Protected* pr) ;

int delete_invalided_protected(CellProtected** pListe) ;

typedef struct hashcell {
    Key* key;
    int val;
} HashCell;

typedef struct hashtable {
    HashCell** tab;
    int size;
} HashTable;

HashCell* create_hashcell(Key* key);

int hash_function(Key* key, int size);

int find_position(HashTable* t, Key* key);

HashTable * create_hashtable(CellKey* keys, int size) ;

void delete_hashtable(HashTable* t) ;

Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) ;


#endif