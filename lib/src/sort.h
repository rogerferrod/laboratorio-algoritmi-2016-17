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


/* mai usato? */
typedef int (*AlgSort)(array_o* array, ArrayCompare compare);

extern void insertion_sort(array_o* array, ArrayCompare compare);

extern void selection_sort(array_o* array, ArrayCompare compare);

extern void quick_sort(array_o* array, ArrayCompare compare);
