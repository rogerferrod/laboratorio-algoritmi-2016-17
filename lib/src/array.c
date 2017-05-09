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
#include "array.h"

#define REALLOC_FACTOR   2.25 /* 1.5*(3/2) */
#define DECREMENT_LIMIT  0.25 /* 1/4 */

#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}
    
/* Implementation of the opaque type */
struct _myArray {
  void** array;             /* generic array */
  size_t size;              /* size of the array */
  size_t capacity;          /* capacity of the array */
};


array_o* array_new(size_t capacity) {
  array_o* new_array = (array_o*) malloc(sizeof(array_o));
  if (new_array != NULL){
    new_array->array = (void**) malloc(sizeof(void*)*capacity);
    if (new_array->array != NULL) {
      new_array->size = 0;
      new_array->capacity = capacity;
      return new_array;
    }
  }
  
  fprintf(stderr, "Not enough space for malloc\n");
  errno = ENOMEM;
  exit(EXIT_FAILURE);
}

void array_free(array_o* array) {
  ASSERT_PARAMETERS_NOT_NULL(array);
  free(array->array);
  free(array);
  return;
}

size_t array_size(array_o* array) {
  ASSERT_PARAMETERS_NOT_NULL(array);
  return array->size;
}

size_t array_capacity(array_o* array) {
  ASSERT_PARAMETERS_NOT_NULL(array);
  return array->capacity;
}

int array_empty(array_o* array) {
  ASSERT_PARAMETERS_NOT_NULL(array);
  return array->size == 0;
}

void* array_at(array_o* array, size_t position) {
  ASSERT_PARAMETERS_NOT_NULL(array);  

  if(position >= array->size ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[position];
}

void array_insert(array_o* array, void* element) {
  ASSERT_PARAMETERS_NOT_NULL(array);

  if(array->size >= array->capacity){
    array->capacity *= REALLOC_FACTOR;
    array->array = realloc(array->array, array->capacity*sizeof(void*));
    if(array->array == NULL){
      fprintf(stderr, "Not enough memory for realloc\n");
      errno = ENOMEM;
      exit(EXIT_FAILURE);
    }
  }
  array->array[array->size] = element;
  array->size++;
  return;
}

void array_delete(array_o* array, size_t position) {
  ASSERT_PARAMETERS_NOT_NULL(array);

  if(position >= array->size ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  size_t i;
  for(i = position+1; i < array_size(array); ++i) {
    array->array[i-1] = array->array[i];
  }
  array->size--;

  if (array->size <=  (array->capacity)*DECREMENT_LIMIT){
    array->capacity /= REALLOC_FACTOR;
    array->array = realloc(array->array, array->capacity*sizeof(void*));
    if(array->array == NULL){
      fprintf(stderr, "Not enough memory for realloc\n");
      errno = ENOMEM;
      exit(EXIT_FAILURE);
    }
  }

  return;
}

void array_swap(array_o* array, size_t position_a, size_t position_b){
  ASSERT_PARAMETERS_NOT_NULL(array);
  
  if(position_a >= array->size || position_b>= array->size){
    fprintf(stderr, "Array index out of bounds (0:%ld)\n", array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  
  void* temp = array->array[position_a];
  array->array[position_a] = array->array[position_b];
  array->array[position_b] = temp;
  return;
}
