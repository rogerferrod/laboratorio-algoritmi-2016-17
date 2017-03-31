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

typedef int (*AlgSort)(array_o*, void*);

extern size_t insertion_sort(array_o* array, void* element);

/* + i vari algoritmi di ordinamento */
