#pragma once

#include <stddef.h>

//
// Implements an ordered array.
// The elements in the array are kept in order by the library
//

//Definition of the opaque type
typedef struct _OrderedArray OrderedArray;

//Return a newly alloced OrderedArray.
//The returned array should be dealloced by OrderedArray_free.
//capacity: the initial size of the array
OrderedArray* OrderedArray_new(size_t capacity);

void OrderedArray_free(OrderedArray* array);

size_t OrderedArray_size(OrderedArray* array);

size_t OrderedArray_capacity(OrderedArray* array);

int OrderedArray_empty(OrderedArray* array);

void* OrderedArray_at(OrderedArray* array, size_t);

void OrderedArray_insert(OrderedArray* array, void*);
