/*
 *  File: sort.h
 *  Author: 
 *
 *  Date: 
 *
 */


#pragma once


#include "array.h"
#include <stddef.h>

#define ASCENDING  0
#define DESCENDING 1

/* Pivot choice method, can be random, median, first, last */
#define PIVOT_TYPE random

#if PIVOT_TYPE == random
  #define PIVOT_INDEX(first,last) (rand()%(last-first+1)+first)
#elif PIVOT_TYPE == median
  #define PIVOT_INDEX(first,last) (((last-first)/2)+first)
#elif PIVOT_TYPE == first
  #define PIVOT_INDEX(first,last) (first)
#elif PIVOT_TYPE == last
  #define PIVOT_INDEX(first,last) (last)
#else 
  #define PIVOT_INDEX(first,last) (rand()%(last-first+1)+first)
#endif

/* mai usato? */
typedef int (*AlgSort)(array_o* array, ArrayCompare compare);

extern void insertion_sort(array_o* array, ArrayCompare compare);

extern void selection_sort(array_o* array, ArrayCompare compare);

extern void quick_sort(array_o* array, ArrayCompare compare);
