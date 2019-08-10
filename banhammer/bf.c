/*
 * bf.c
 * Author: Ryan Hamamoto
 * CMPS12B: Spring 2017
 */

# include <stdint.h>
# include "bv.h"
# include "bf.h"

uint32_t hashBF(bloomF *x, char *key)
{
	hashTable *firstTable = newHT(x->l, x->s); //hash the key
	uint32_t index = hash(firstTable, key) % x->l; //generate hash index
	setBF(x, index); //set respective bit
	delHT(firstTable);
	return index;
}
