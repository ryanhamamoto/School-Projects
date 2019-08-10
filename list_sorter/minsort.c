/*
 * minsort.c
 * Author: Darrell Long
 * CMPS 12B: Spring 2017
 */

# include <stdint.h>
# include <stdio.h>

# include "minsort.h"

//swap function taken from Assignment2 - sorting PDF; Author: Prof. Darrell Long
# ifdef _INSTRUMENTED
# define SWAP(x,y) { uint32_t t = x; x = y; y = t;}
# else
# define SWAP(x,y) { uint32_t t = x; x = y; y = t;}
# endif

// minIndex : find the index of the least element.
uint32_t minIndex(uint32_t a[], uint32_t first , uint32_t last)
{
	extern uint32_t compares;
	uint32_t smallest = first ; // Assume the first is the least
	for (uint32_t i = first; i < last; i += 1)
	{
		compares++;
		smallest = a[i] < a[smallest] ? i : smallest;
	}
	return smallest;
}

// minSort : sort by repeatedly finding the least element.
void minSort(uint32_t a[], uint32_t length)
{
	extern uint32_t compares, moves;
	for (uint32_t i = 0; i < length - 1; i += 1)
	{
		compares++;
		uint32_t smallest = minIndex (a, i, length);
		if (smallest != i) // It ’s silly to swap with yourself!
		{
			SWAP (a[smallest], a[i]);
			moves += 3;
		}
	}
	return;
}
