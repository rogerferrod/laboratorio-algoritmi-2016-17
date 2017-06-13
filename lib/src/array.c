/*
 *  File: array.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Implements an abstracted array
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "lib.h"
#include "array.h"

#define REALLOC_FACTOR   2.25 /* 1.5*(3/2) */
#define DECREMENT_LIMIT  0.25 /* 1/4 */


/* Implementation of the opaque type */
struct _myArray {
  void** array;             /* generic array */
  size_t size;              /* size of the array */
  size_t capacity;          /* capacity of the array */
};


array_o* array_new(size_t capacity) {
  register array_o* new_array = (array_o*) xmalloc(sizeof(array_o));
  new_array->array = (void**) xmalloc(sizeof(void*)*capacity);
  new_array->size = 0;
  new_array->capacity = capacity;
  return new_array;
}

void array_free(array_o* array) {
  assert(array != NULL);
  free(array->array);
  free(array);
  return;
}

size_t array_size(array_o* array) {
  assert(array != NULL);
  return array->size;
}

size_t array_capacity(array_o* array) {
  assert(array != NULL);
  return array->capacity;
}

int array_empty(array_o* array) {
  assert(array != NULL);
  return array->size == 0;
}

void* array_at(array_o* array, size_t position) {
  assert(array != NULL);
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%d) out of bounds (0:%d)\n", (unsigned int)position, (unsigned int)array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[position];
}

void array_insert(array_o* array, void* element) {
  assert(array != NULL);
  if(array->size >= array->capacity){
    array->capacity *= REALLOC_FACTOR;
    array->array = xrealloc(array->array, array->capacity*sizeof(void*));
  }
  array->array[array->size] = element;
  array->size++;
  return;
}

void array_delete(array_o* array, size_t position) {
  assert(array != NULL);
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%d) out of bounds (0:%d)\n", (unsigned int)position, (unsigned int)array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  register size_t i;
  for(i = position+1; i < array_size(array); ++i) {
    array->array[i-1] = array->array[i];
  }
  array->size--;

  if (array->size <= (array->capacity)*DECREMENT_LIMIT){
    array->capacity /= REALLOC_FACTOR;
    array->array = xrealloc(array->array, array->capacity*sizeof(void*));
  }

  return;
}

void array_swap(array_o* array, size_t position_a, size_t position_b){
  assert(array != NULL);
  if(position_a >= array->size || position_b>= array->size){
    fprintf(stderr, "Array index out of bounds (0:%d)\n", (unsigned int)array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  register void* temp = array->array[position_a];
  array->array[position_a] = array->array[position_b];
  array->array[position_b] = temp;
  return;
}

void array_set(array_o* array,size_t position, void* element){
  assert(array != NULL);
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%d) out of bounds (0:%d)\n", (unsigned int)position, (unsigned int)array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  array->array[position] = element;
}
