#ifndef MECANISMECONSENSUS_H
#define MECANISMECONSENSUS_H

#include "baseCentralisee.h"
#include <openssl/sha.h>


typedef struct block {
	Key * author ;
	CellProtected * votes ;
	unsigned char * hash ;
	unsigned char * previous_hash ;
	int nonce ;
 } Block ;


void block_to_file(Block * b, char * nomF) ;

Block * file_to_block(char * nomF) ;

char* block_to_str(Block* block) ;

unsigned char* hash_SHA256(char * s);

void compute_proof_of_work(Block *B, int d);

int verify_block(Block* B, int d);

void delete_block(Block* b);

typedef struct block_tree_cell {
	Block* block;
	struct block_tree_cell* father;
	struct block_tree_cell* firstChild;
	struct block_tree_cell* nextBro;
	int height;
} CellTree;

CellTree* create_node(Block* b);

int update_height(CellTree* father, CellTree* child);

void add_child(CellTree* father, CellTree* child);

void print_tree(CellTree* t, int i);

void delete_node(CellTree* node);

void delete_tree(CellTree** pT);

CellTree* highest_child(CellTree* cell);

CellTree* last_node(CellTree* tree);

CellProtected* fusion_listes_protected(CellProtected* l1, CellProtected* l2);

CellProtected* liste_protected_longest_chain(CellTree* tree);

void submit_vote(Protected* p) ;

CellTree* create_block(CellTree* tree, Key* author, int d) ;

void add_block(int d, char* name) ;

CellTree* read_tree() ;

Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) ;

#endif