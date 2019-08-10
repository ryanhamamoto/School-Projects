/*
 * sorting.c
 * Author: Ryan Hamamoto
 * CMPS 12B: Spring 2017
 */
 
//standard C libraries
# include <getopt.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

//current directory libraries
# include "minsort.h"
# include "bubblesort.h"
# include "insertionsort.h"
# include "quicksort.h"
# include "mergesort.h"
# include "bv.h" //taken from piazza post 474; Author: Prof. Darrell Long

# define MASK 0X1000000 //limits the random numbers to 24 bits
# define SEEDINIT 0X7B0446 //default seed in hex form
# define LISTINIT 0X64 //default list of 100

static void sortPrint(uint32_t *list, uint32_t size); //prints the given list

uint32_t moves, compares; //global storage for compares and moves

//enum containing the sorting options
typedef enum optionSelect
{
	emptySortOption,
	minSortOption,
	bubbleSortOption,
	insertionSortOption,
	quickSortOption,
	mergeSortOption
} optionSelect;


int main (int argc, char *argv[])
{
	//initialize seed, print and size numbers to default values
	int userOption = 0;
	uint32_t userRandom = SEEDINIT, userPrint = LISTINIT, userSize = LISTINIT;
	opterr = 0;
	bitV *options = newVec(1); //create bit vector of size 1 byte for options
	
	//receive arguments until user no longer inputs commands
	while ((userOption = getopt(argc , argv , "AmbiqMp:r:n:")) != -1)
	{	
		switch (userOption)
		{
			case 'A':
			oneVec(options); //set all bits
			break;
			
			case 'm':
			setBit(options, minSortOption); //set respective bit
			break;
			
			case 'b':
			setBit(options, bubbleSortOption); //set respective bit
			break;
			
			case 'i':
			setBit(options, insertionSortOption); //set respective bit
			break;
			
			case 'q':
			setBit(options, quickSortOption); //set respective bit
			break;
			
			case 'M':
			setBit(options, mergeSortOption); //set respective bit
			break;
			
			case 'p':
			userPrint = atoi(optarg); //reset print size
			break;
			
			case 'r':
			userRandom = atoi(optarg); //reset random seed
			break;
			
			case 'n':
			userSize = atoi(optarg); //reset array size
			break;
				
			case '?':
			//error check for user mistakes, such as entering a modifier with no argument
			if (optopt == 'p' || optopt == 'r' || optopt == 'n')
			{
				printf("ERROR: please enter an argument after the option (-%c)\n", optopt);
			}
			else
			{
				printf("ERROR: unrecognized input\n");
			}
			break;
		}
						
	}
	
	//initialize the seed and array
	srand(userRandom);
	uint32_t *array = (uint32_t *) calloc(userSize + 1, sizeof(uint32_t));
	for (uint32_t i = 0; i < userSize; i++) //create the list
	{
		array[i] = rand() % MASK;
	}
	//limit print task to what is given and allocated
	uint32_t printTask;
	if(userSize >= userPrint)
	{	
		printTask = userPrint;
	}
	else
	{
		printTask = userSize;
	}
	
	if (valBit(options, minSortOption)) //if minsort requested
	{
		moves = 0; compares = 0; //initialize count values
		uint32_t *minArray = (uint32_t *) calloc(userSize + 1, sizeof(uint32_t)); //allocate memory
		memcpy(minArray, array, sizeof(uint32_t) * (userSize + 1)); //copy the array
		minSort(minArray, userSize); //sort the list
		printf("Min Sort\n%d elements\n%d moves\n%d compares\n", userSize, moves, compares);
		sortPrint(minArray, printTask); //print the list
		free(minArray); //free the memory
		minArray = NULL; //set pointer to null
	}
	if (valBit(options, bubbleSortOption)) //if bubblesort requested
	{
		moves = 0; compares = 0; //initialize count values
		uint32_t *bubbleArray = (uint32_t *) calloc(userSize + 1, sizeof(uint32_t)); //allocate memory
		memcpy(bubbleArray, array, sizeof(uint32_t) * (userSize + 1)); //copy the array
		bubbleSort(bubbleArray, userSize); //sort the list
		printf("Bubble Sort\n%d elements\n%d moves\n%d compares\n", userSize, moves, compares);
		sortPrint(bubbleArray, printTask); //print the list
		free(bubbleArray); //free the memory
		bubbleArray = NULL; //set pointer to null
	}
	if (valBit(options, insertionSortOption)) //if insertionsort requested
	{
		moves = 0; compares = 0; //initialize count values
		uint32_t *insertionArray = (uint32_t *) calloc(userSize + 1, sizeof(uint32_t)); //allocate memory
		memcpy(insertionArray, array, sizeof(uint32_t) * (userSize + 1)); //copy the array
		insertionSort(insertionArray, userSize); //sort the list
		printf("Insertion Sort\n%d elements\n%d moves\n%d compares\n", userSize, moves, compares);
		sortPrint(insertionArray, printTask); //print the list
		free(insertionArray); //free the memory
		insertionArray = NULL; //set pointer to null
	}
	if (valBit(options, quickSortOption)) //if quicksort requested
	{
		moves = 0; compares = 0; //initialize count values
		uint32_t *quickArray = (uint32_t *) calloc(userSize + 1, sizeof(uint32_t)); //allocate memory
		memcpy(quickArray, array, sizeof(uint32_t) * (userSize + 1)); //copy the array
		quickSort(quickArray, 0, userSize - 1); //decrement size and sort the list
		printf("Quick Sort\n%d elements\n%d moves\n%d compares\n", userSize, moves, compares);
		sortPrint(quickArray, printTask); //print the list
		free(quickArray); //free the memory
		quickArray = NULL; //set pointer to null
	}
	if (valBit(options, mergeSortOption)) //if mergesort requested
	{
		moves = 0; compares = 0; //initialize count values
		uint32_t *mergeArray = (uint32_t *) calloc(userSize + 1, sizeof(uint32_t)); //allocate memory
		memcpy(mergeArray, array, sizeof(uint32_t) * (userSize + 1)); //copy the array
		mergeSort(mergeArray - 1, userSize); //decrement index and sort the list (everything starts at 1 in mergesort)
		printf("Merge Sort\n%d elements\n%d moves\n%d compares\n", userSize, moves, compares);
		sortPrint(mergeArray, printTask); //print the list
		free(mergeArray); //free the memory
		mergeArray = NULL; //set pointer to null

	}
	delVec(options); //free the bitvector memory
	free(array); //free the random array memory
	array= NULL; //set random array pointer to null
	return 0;
}

void sortPrint(uint32_t *list, uint32_t size)
{
	//print the list with a size of 9 digits available for each integer
	for (uint32_t k = 0; k < size; k++)
	{
		printf(" %9u", list[k]);
		//every 7 integers, print a new line
		//for some reason k=2 triggers the original equation
		if (((k - 6) % 7) == 0 && k != 2)
		{
				printf("\n");
		}
	}
	printf("\n");
}
