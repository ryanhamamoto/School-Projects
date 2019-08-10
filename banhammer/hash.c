# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include "aes.h"
# include "hash.h"
# include "ll.h"

//creates new hash table
hashTable *newHT( uint32_t l, uint32_t salt[]) //might need each key and transfer
{
	hashTable *h = (hashTable *) malloc(sizeof(hashTable));
	//allocate memory for the linked lists
	h->h = (listNode **)calloc(l, sizeof(listNode *));
	h->h[l] = (listNode *) calloc(l, sizeof(listNode));
	h->l = l; //length
	for (uint32_t i = 0; i < 4; i++) //salt
	{
		memcpy(&h->s[i], &salt[i], 4);
	}
	return h; //return the pointer
}

//deletes the hash table (probably more stuff)
void delHT(hashTable *h)
{ 
	free(h->h); //free the array of pointers
	free(h); //then free the hash table data struct
	h = NIL;
	return;
}

listNode *findHT(hashTable *h, const char *key)
{
	extern uint32_t seeks;
	seeks++;
	uint32_t index = hash(h, key) % h->l;
	listNode *find = findLL(&h->h[index], key);
	return find;
}

void insertHT (hashTable *h, const char *key, const char *transfer)
{
	uint32_t index = hash(h, key) % h->l; //generate index
    listNode *node = newNode(key, transfer);
	h->h[index] = node;
	//printLL(h->h[index]);
	return;
}


void printHT(hashTable *h, const char *key)
{
	uint32_t index = hash(h, key) % h->l;
	if (h->h != NIL)
	{
		printf("\nh[%u]: ", index); 
		printLL(h->h[index]);
	}
	printf("\n");
	return;
}

//Author: Darrell Long
static inline int realLength(int l)
{
	return 16 * (l / 16 + (l % 16 ? 1 : 0));
}

//Author: Darrell Long
uint32_t hash(hashTable *h, const char *key)
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum = 0x0;
	int keyL = strlen(key);
	uint8_t *realKey = (uint8_t *)calloc(realLength(keyL), sizeof(uint8_t));

	memcpy(realKey, key, keyL); //copy keyL bytes of key into realKey

	for (int i = 0; i < realLength(keyL); i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) h->s, 	    // Salt
                           (uint8_t *) realKey + i,	// Input
						   (uint8_t *) output);	    // Output
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	free(realKey);
	return sum;
}
