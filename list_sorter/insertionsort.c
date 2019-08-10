/*
 * insertionsort.c
 * Author: Ryan Hamamoto
 * Took the algorithm from Assignment2 -sorting PDF
 * CMPS 12B: Spring 2017
 */
 
# include <stdint.h>

void insertionSort(uint32_t a[], uint32_t length)
{
	int temp, j;
	extern uint32_t compares, moves;
	for (int i = 1; i < (int)length; i++)
	{
		moves++;
		temp = a[i]; //stores initial array value
		j = i - 1; //sets j index to value before initial array value
		while (j >= 0 && a[j] > (uint32_t) temp) //decrements through j until lesser value is reached
		{
			compares++;
			moves++;
			a[j + 1] = a[j]; //shifts up the list
			j--;
		}
		a[j + 1] = temp; //inserts value and increments i
	}
}
