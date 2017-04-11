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


/* pointer to sorting function */
typedef void (*AlgSort)(array_o* array, ArrayCompare compare);


/* insertion sort algorithm implementation */
extern void insertion_sort(array_o* array, ArrayCompare compare);

/* selection sort algorithm implementation */
extern void selection_sort(array_o* array, ArrayCompare compare);

/* quicksort algorithm implementation */
extern void quick_sort(array_o* array, ArrayCompare compare);
