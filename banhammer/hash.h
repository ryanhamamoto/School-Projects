# ifndef NIL
# define NIL ( void *) 0
# endif
# ifndef _HASH_H
# define _HASH_H

# include <stdint.h>
# include "ll.h"

typedef struct hashTable hashTable;

struct hashTable
{
	uint32_t s [4]; // Salt
	uint32_t l; // Length
	listNode **h; // Array of pointers to linked lists
};

hashTable *newHT(uint32_t l, uint32_t salt[]);

void delHT(hashTable *h);

listNode *findHT(hashTable *h, const char *key);

void insertHT(hashTable *h, const char *key, const char *transfer);

uint32_t hash(hashTable *h, const char *key);

void printHT(hashTable *h, const char *key);
# endif
