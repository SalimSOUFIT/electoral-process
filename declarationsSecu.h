#ifndef DECLARATIONSSECU_H
#define DECLARATIONSSECU_H

#include "nbPremiers.h"

typedef struct key {
    long val;
    long n;
} Key;

void init_key(Key* key, long val, long n);

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);

char* key_to_str(Key* key);

Key* str_to_key(char* str);

typedef struct signature {
    int size;
    long* content;
} Signature;

Signature* init_signature(long* content, int size);

Signature* sign(char* mess, Key* sKey);

char * signature_to_str ( Signature * sgn ) ;

Signature * str_to_signature ( char * str ) ;

typedef struct protected{
    Key * pKey ;
    char * mess ;
    Signature * sgn ;
} Protected ;

Protected* init_protected(Key* pKey, char* mess, Signature* sgn) ;

int verify(Protected* pr) ;

char * protected_to_str(Protected * pr) ;

Protected * str_to_protected(char * ps) ;

int if_exists(int n, Key * c, Key * k) ;

void generate_random_data(int nv, int nc) ;


#endif