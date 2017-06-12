/*
 *  File: array.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Defines an abstracted array. The elements in 
 * the array are comparable through the compare function
 *
 */

#pragma once

#include <stddef.h>


/* Definition of the array's opaque type */
typedef struct _myArray array_o;

/* Definition of the array's compare function */
typedef int (*ArrayCompare)(void*, void*);


/* Return a newly allocated array */
extern array_o* array_new(size_t capacity);

/* Deallocate an array */
extern void array_free(array_o* array);

/* Return the size of an array */
extern size_t array_size(array_o* array);

/* Return the capacity of an array */
extern size_t array_capacity(array_o* array);

/* Return 1 if the array is empty, 0 otherwise */
extern int array_empty(array_o* array);

/* Return a pointer to the element in the specified position */
extern void* array_at(array_o* array, size_t position);

/* Adds an element at the bottom of the array */
extern void array_insert(array_o* array, void* element);

/* Delete the element in the specified position */
extern void array_delete(array_o* array, size_t position);

/* Swap two element in the specified positions */
extern void array_swap(array_o* array, size_t position_a, size_t position_b);

/* Set element in specified position */
extern void array_set(array_o* array,size_t position, void* element);
