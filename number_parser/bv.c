# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "bv.h"
# include "sieve.h"

bitV *newVec(uint32_t l)
{
	//Code from DDEL 4/20/17
	//allocates memory for bit vector and stores the given length
	bitV *v = (bitV *)malloc(sizeof(bitV));
    	v->v = (uint8_t *) calloc(l, sizeof(uint8_t));
    	v->l = l;
    	return v; 
}

void delVec(bitV *v)
{
	//frees memory after it is allocated
	free(v->v); free(v);
	return;
}

void oneVec(bitV *v)
{
	//sets all bits to 1
	for(uint32_t i = 0; i <= lenVec(v); i++)
	{
		v->v[i] |= 1;
	}
	return;
}

void setBit(bitV *v, uint32_t position)
{
	//sets a specific bit to 1
  v->v[position] |= 1;
	return;
}

void clrBit(bitV *v, uint32_t position)
{ 
	//sets a specific bit to 0
	v->v[position] &= 0;
	return;
}

uint8_t valBit(bitV *v, uint32_t l)
{
	//returns the value at specific location in bit vector
	return v->v[l];
}

uint32_t lenVec(bitV *v)
{
	//returns the length of the bit vector
	return v->l;
}
