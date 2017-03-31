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

struct _myArray {
  void** array;
  size_t size;
  size_t capacity;
  ArrayCompare compare;
};

array_o* array_new(size_t capacity, ArrayCompare compare) {
  array_o* new_array = (array_o*) malloc(sizeof(array_o));
  new_array->array = (void**) malloc(sizeof(void*)*capacity);
  new_array->size = 0;
  new_array->capacity = capacity;
  new_array->compare = compare;
  return new_array;
}

void array_free(array_o* array) {
  free(array->array);
  free(array);
  return;
}

size_t array_size(array_o* array) {
  return array->size;
}

size_t array_capacity(array_o* array) {
  return array->capacity;
}

int array_empty(array_o* array) {
  return array->size == 0;
}

void* array_at(array_o* array, size_t position) {
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    exit(EXIT_FAILURE); /* o return NULL? */
  }
  return array->array[position];
}

void array_insert(array_o* array, void* element) {
  if(array->size >= array->capacity){
    array->capacity *= 2;
    array->array = realloc(array->array, array->capacity*sizeof(void*));
  }

  size_t i;
  for( i = array_size(array); i > 0 && array->compare(array->array[i-1], element) > 0; --i ) {
    array->array[i] = array->array[i-1];
  }

  array->array[i] = element;
  array->size += 1;
  return;
}

void array_set_elem(array_o* array, void* element, size_t position){
  if(position >= array->capacity ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    exit(EXIT_FAILURE); /* o return NULL? */
  }
  array->array[position] = element;
  return;
}
