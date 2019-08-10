/*
 * minsort.h
 * Author: Ryan Hamamoto
 * CMPS 12B: Spring 2017
 */

# ifndef _MIN_SORT_H
# define _MIN_SORT_H

# include <stdint.h>

uint32_t minIndex(uint32_t a[], uint32_t first , uint32_t last);

void minSort(uint32_t a[], uint32_t length);

#endif