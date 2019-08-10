// Author: Prof. Darrell Long

# ifndef NIL
# define NIL (void *) 0
# endif
# ifndef _BF_H
# define _BF_H

# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# include "bv.h"
# include "hash.h"

typedef struct bloomF {
	uint8_t *v; // Vector
	uint32_t l; // Length
	uint32_t s [4]; // Salt
} bloomF;

// Each function has its own hash function , determined by the salt .
uint32_t hashBF ( bloomF *x, char *key);

// Create a new Bloom Filter of a given length and hash function.
static inline bloomF *newBF(uint32_t l, uint32_t b[])
{
	bloomF *x = (bloomF *) malloc(sizeof(bloomF)); //struct
    x->v = (uint8_t *) calloc(l / 8 + 1, sizeof(uint8_t)); //vector
    x->l = l; //length
	for (uint32_t i = 0; i < 4; i++) //salt
	{
		memcpy(&x->s[i], &b[i], 4);
	}
    return x;
}

// Delete a Bloom filter
static inline void delBF(bloomF *x)
{
	//free all previously allocated memory
	free(x->v);
	free(x);
	return;
}


// Return the value of position k in the Bloom filter
static inline uint32_t valBF ( bloomF *x, uint32_t k)
{
	//ANDing with 1 does not change value of x->v
	if((x->v[k / 8] & (0x1 << k % 8)) != 0)
	{
		return 1; //if true, valBF is a 1
	}
	else
	{
		return 0; //if false, valBF is a 0
	}
}

//returns the length portion of the data struct
static inline uint32_t lenBF ( bloomF *x) { return x->l; }

// Count bits in the Bloom filter
static inline uint32_t countBF ( bloomF *x)
{
	uint32_t count = 0;
	for (uint32_t i = 0; i < x->l; i++)
	{
		//increment count every time x has a set bit
		if(valBF(x, i))
		{
			count += 1;
		}
	}
	return count; //return amount of set bits
}

// Set an entry in the Bloom filter
static inline void setBF (bloomF *x, uint32_t index)
{
	x->v[index / 8] |=  (0x1 << index % 8);
	return;
}

// Clear an entry in the Bloom filter

static inline void clrBF (bloomF *x, uint32_t index)
{
	x->v[index / 8] &= ~(0x1 << index % 8);
	return;
}

// Check membership in the Bloom filter
static inline uint32_t memBF (bloomF *x, uint32_t index)
{
	if(valBF(x, index))
	{
		return true;
	} 
	else
	{
		return false;
	}
} 

static inline void printBF ( bloomF *x)
{
	printf("\n");
	for (uint32_t i = 0; i < x->l; i++)
	{
		printf("%u", valBF(x, i));
	}
	printf("\n");
	return;
}

# endif
