/*
 * parfait.c
 * Author: Ryan Hamamoto
 * CMPS 12B: Spring 2017
 */
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
#include <math.h>
# include "bv.h"
# include "sieve.h"

//function that finds prime divisors
void primeDivisor(bitV *v, uint32_t num);
//function that finds proper divisors
void properDivisor(uint32_t num);


int main(void)
{
	uint32_t maxNatural = 100000; //initialize count to default
	//printf("Enter a max natural number:");
	//scanf("%u", &maxNatural);
	bitV *vec = newVec(maxNatural); //initialize a bit vector
	//printf("\n");
	sieve(vec); //mark primes
	for(uint32_t number = 2; number <= lenVec(vec); number++)
	{
		printf("%u", number);
		if (vec->v[number] == 0) //if not prime
		{
			printf(" C:");
			primeDivisor(vec, number);
			properDivisor(number);
			printf("\n");
		}
		else if (vec->v[number] == 1) //if prime
		{
			printf(" P\n");
		}
	}
	delVec(vec); //free memory
}

void properDivisor(uint32_t num)
{
	//array to store proper divisors taken
	uint32_t *proper = (uint32_t *) calloc(num, sizeof(uint32_t));
	uint32_t increment = 0;//store number for comparison to sum
	for (uint32_t j = 1; j < num; j++)
	{
		if (num % j == 0) //if its a proper divisor
		{	
			proper[increment] = j; //store to output
			increment++; //increment the array
		}
	}
	uint32_t sum = 0;
	for (uint32_t k = 0; k < increment; k += 1) //sum proper divisors
	{
		sum += proper[k];
		//printf("\nsum:%u\n", sum);
	}
	if (sum == num) //if the number equals the sum of its proper divisors
	{
		//it is a perfect number
		printf("\n%u E:", num);
		for (uint32_t m = 0; m < increment; m += 1)
		{
		printf(" %u", proper[m]); //prints subsequent proper divisors
		}
	}
	free(proper); //frees memory
}
void primeDivisor(bitV *v, uint32_t num)
{
	for (uint32_t j = 2; j <= num; j++)
	{
		if(v->v[j]) //if it is prime
		{
			while (num % j == 0) //until prime no longer factors
			{	
				printf(" %u", j);
				num /= j;
			}
		}
	}
	return;
}
