/*
 * mergesort.c
 * Author: Ryan Hamamoto
 * Took the algorithm from Assignment2 -sorting PDF
 * CMPS 12B: Sprint 2017
 */

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# include "mergesort.h"

void mergeSort(uint32_t a[], uint32_t length)
{
	if(length > 1)
	{
		extern uint32_t compares, moves; //declare compare and move count
		uint32_t middle = length >> 1; //divide the length in half
		uint32_t *leftList = (uint32_t *) calloc(middle + 1, sizeof(uint32_t)); //create left list
		uint32_t *rightList = (uint32_t *) calloc((length - middle) + 1, sizeof(uint32_t)); //create right list
		for (uint32_t k = 1; k <= middle; k++) //fill left list starting at index 1
		{	
			moves++;
			leftList[k] = a[k];
		}

		for (uint32_t j = middle + 1; j <= length; j++) //fill right list starting at index 1
		{
			moves++;
			rightList[j - middle] = a[j];
		}
		mergeSort(leftList, middle); //sort the left list, pass size up to middle of a[]
		mergeSort(rightList, (length - middle)); //sort the right list, pass the rest of the size of a[]

		compares += middle; //compares 'middle' amount of times during the loop as it exchanges values
		uint32_t left = 1, right = 1; //start at index 1 and compare each item in each list until sorted
		for(uint32_t i = 1; i <= length; i++) 
		{
			if((left <= middle) && (right <= length - middle)) //if both lists hold elements
			{
				if(leftList[left] < rightList[right]) //if the left item is less than the right item
				{
					moves++;
					a[i] = leftList[left]; //put it in the list
					left++; //increment through left list
				}
				else if(leftList[left] > rightList[right])//if left item is greater than right item
				{
					moves++;
					a[i] = rightList[right]; //put right item in the list
					right++; //increment through right list
				}
			}
			else if(left <= middle)
			{
				moves++;
				a[i] = leftList[left]; //put it in the list
				left++; //increment through left list
			}
			else if(right <= length - middle)
			{
				moves++;
				a[i] = rightList[right]; //put right item in the list
				right++; //increment through right list
			}
		}
		//always free!
		free(leftList);
		free(rightList);
		leftList = NULL;
		rightList = NULL;
	
	} 
	else if (length <= 1)
	{
			return; //now that the list is size 1, return and sort the previous lists
	}
}

