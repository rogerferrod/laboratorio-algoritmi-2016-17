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

/* + i vari algoritmi di ordinamento */
