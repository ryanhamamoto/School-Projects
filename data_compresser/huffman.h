/*
 * huffman.h
 * CMPS 12B: Sprint 2017
 */
 
# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# ifndef NIL
# define NIL (void *)0
# endif

# include "code.h"

typedef struct DAH treeNode;
struct DAH
{
	uint8_t symbol;
	uint64_t count;
	bool leaf;
	treeNode *left, *right;
};

// New node , with symbols , leaf or not , a count associated with it
treeNode *newNode (uint8_t s, bool l, uint64_t c);

// Dump a Huffman tree onto a file
void dumpTree (treeNode *t, int file);

// Build a tree from the saved tree
treeNode * loadTree (uint8_t savedTree [], uint16_t treeBytes);

// Step through a tree following the code
int32_t stepTree (treeNode *root, uint8_t code, char outFile []);

// Parse a Huffman tree to build codes
void buildCode (treeNode *n, code s , code table [256]);

// Delete a tree
void delTree (treeNode *t);

static inline void delNode (treeNode *h) {free (h); return;}

static inline int8_t compare( treeNode *l, treeNode *r)
{
	return l->count - r->count; // l < r if negative , l = r if 0 , ...
}

treeNode *join(treeNode *l, treeNode *r); // Join two subtrees

void printTree(treeNode *t, int depth);
# endif
