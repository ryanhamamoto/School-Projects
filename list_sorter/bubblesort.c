/*
 * bubblesort.c
 * Author: Ryan Hamamoto
 * Took the algorithm from Assignment2 -sorting PDF
 * CMPS 12B: Spring 2017
 */
 
# include <stdint.h>
# include <stdbool.h>

# include "bubblesort.h"

//swap function taken from piazza post 258; Author: Prof. Darrell Long 
# define SWAP(x,y) { uint32_t t = x; x = y; y = t;}
 
void bubbleSort(uint32_t a[], uint32_t length)
{
	extern uint32_t compares, moves;
	uint32_t n = length; //copy the length of the array, start at the end
	int swapFlag = true; //initialize swapped flag
	while(swapFlag == true) //while swapping is still occuring
	{
		swapFlag = false; //reset swap flag
		for(uint32_t i = 1; i <= n - 1; i++)
		{
			if(a[i - 1] > a[i]) //if previous int is greater than current int
			{	
				compares++; //every triggered if statement costs 1 compare
				SWAP(a[i - 1], a[i]); //swap the integers
				moves += 3; //every swap costs 3 moves
				swapFlag = true; //set swap flag
			}
		}
		n = n - 1; //decrement the bubble within the array
	}
}
