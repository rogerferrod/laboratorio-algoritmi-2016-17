/*
 *  File: array.h
 *  Author: 
 *
 *  Date: 
 *
 */


/*
 * Implements an ordered array. The elements
 * in the array are kept in order by the library
 */

#pragma once

#include <stddef.h>


/* Defintion of the opaque type */
typedef struct _myArray array_o;

/* Definition of compare function */
typedef int (*ArrayCompare)(void*, void*);


/* Returns a newly alloced array.
 * The returned array should be dealloced by
 * array_free.
 * capacity: the initial size of the array
 */
extern array_o* array_new(size_t capacity, ArrayCompare compare);

extern void array_free(array_o* array);

extern size_t array_size(array_o* array);

extern size_t array_capacity(array_o* array);

extern int array_empty(array_o* array);

extern void* array_at(array_o* array, size_t position);

extern void array_insert(array_o* array, void* element);

extern void array_set_elem(array_o* array, void* element, size_t position);
