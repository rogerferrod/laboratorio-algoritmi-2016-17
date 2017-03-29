/*
 *  File: array.c
 *  Author: 
 *
 *  Date: 
 *
 */

#include "array.h"
#include "sort.h"
#include <stdlib.h>
#include <stdio.h>


size_t insertion_sort(array_o* array, void* element) {
size_t i;
ArrayCompare compare = array_get_compare(array);
 for(i = array_size(array); i > 0 && compare(array_at(array, i-1), element) > 0; --i ) {
    array_set_elem(array, array_at(array, i-1), i); /* array->array[i] = array->array[i-1]; */
  }
return i;
}

