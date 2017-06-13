/*
 *  File: sort.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#pragma once

#include <stddef.h>
#include "array.h"


/* Pointer to sorting function. */
typedef void (*AlgSort)(array_o* array, ArrayCompare compare);


/* Insertion sort algorithm implementation. */
extern void insertion_sort(array_o* array, ArrayCompare compare);

/* Selection sort algorithm implementation. */
extern void selection_sort(array_o* array, ArrayCompare compare);

/* Quick sort algorithm implementation. */
extern void quick_sort(array_o* array, ArrayCompare compare);
