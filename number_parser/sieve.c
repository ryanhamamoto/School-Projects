/*
 * sieve.c
 * Author: Darrell Long
 * CMPS 12B: Spring 2017
 */

# include <stdint.h>
# include <math.h>
# include <stdio.h>
# include "bv.h"
# include "sieve.h" 
void sieve(bitV *v)
{
	oneVec(v); // Assume all are prime
	clrBit(v, 0); // set 0 to 0
	clrBit(v, 1); // 1 is unity
	setBit(v, 2); // 2 is prime
	for (uint32_t i = 2; i <= sqrtl(lenVec(v)); i +=1)
	{
		if(valBit(v, i)) //it's prime
		{
			for (uint32_t k = 0; (k + i) * i <= lenVec(v); k += 1)
			{
				clrBit(v, (k + i) * i); // Its multiples are composite
			}
		}
	}
	return;
}
