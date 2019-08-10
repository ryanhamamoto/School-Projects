/*
 * quicksort.c
 * Author: Ryan Hamamoto
 * CMPS 12B: Spring 2017
 */
 
# include <stdint.h>
# include <stdbool.h> 

//swap function taken from piazza post 258; Author: Prof. Darrell Long
# define SWAP(x,y) { uint32_t t = x; x = y; y = t;}

//helper function that divides the list around the pivot
uint32_t partition(uint32_t a[], uint32_t head, uint32_t length)
{
	extern uint32_t moves, compares; //count moves and compares
	uint32_t pivot = a[head]; //choose the head of the list to be the pivot
	uint32_t i = head + 1, j = length; //initialize front and end of list
	compares++;
	while(true)
	{
		moves++;
		while(a[i] <= pivot) //increment from bottom to top until pivot is reached
		{
			moves++;
			compares++;
			i++;
		}
		while(a[j] > pivot) //decrement from top to bottom until pivot is reached
		{
			moves++;
			compares++;
			j--;
		}
		if(i >= j) //once indexes cross each other, break out of the loop
		{
			compares++;
			break;
		}
		SWAP(a[i], a[j]); //otherwise swap values
		moves += 3; //each swap costs 3 moves
	}
	SWAP(a[head], a[j]); //swap the pivot value with the new partition
	moves += 3;
	return j; //return the new partition index
}

void quickSort(uint32_t a[], uint32_t head, uint32_t length)
{
	uint32_t part;
	extern uint32_t compares;
	if(head < length)
	{
		//divide into two lists before and after the partition
		//not including the partition
		part = partition(a, head, length);
		quickSort(a, head, part - 1);
		quickSort(a, part + 1, length);
	}
}