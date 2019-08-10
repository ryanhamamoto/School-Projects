/*
 * quicksort.h
 * Author: Ryan Hamamoto
 * CMPS 12B: Spring 2017
 */

# ifndef _QUICK_SORT_H
# define _QUICK_SORT_H

# include <stdint.h>

void quickSort(uint32_t a[], uint32_t head, uint32_t length);

uint32_t partition(uint32_t a[], uint32_t head, uint32_t length);

#endif