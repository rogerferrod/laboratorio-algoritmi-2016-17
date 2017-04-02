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

typedef int (*AlgSort)(array_o* array, ArrayCompare compare);

extern void insertion_sort(array_o* array, ArrayCompare compare);

extern void selection_sort(array_o* array, ArrayCompare compare);

extern void quick_sort(array_o* array, size_t top, size_t bottom, ArrayCompare compare);

/* Partition needed for the quick sort */
extern size_t array_partition(array_o* array, size_t top, size_t bottom, ArrayCompare compare);
