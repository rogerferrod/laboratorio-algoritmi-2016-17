/*
 *  File: array.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 
 *
 */
 
 
/*
 * Implements an abstracted array
 *
 */

#include "array.h"
#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

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
    new_array->size = 0;
    new_array->capacity = capacity;
  }
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
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[position];
}

void array_check_realloc(array_o* array){
  if(array->size >= array->capacity){
    array->capacity *= INCREMENT_FACTOR;
    fprintf(stdout, "realloc_inc\n");
    array->array = realloc(array->array, array->capacity*sizeof(void*));
  }
  /* else if (array->size <=  (array->capacity)/4){
    array->capacity /= DECREMENT_FACTOR;
    fprintf(stdout, "realloc_dec\n");
    array->array = realloc(array->array, array->capacity*sizeof(void*)); 
  }
  */
}

void array_insert(array_o* array, void* element) {
  array_check_realloc(array);
  array->array[array->size] = element;
  array->size ++;
  return;
}

int array_delete(array_o* array, size_t position) {
  if(position >= array->size ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    errno = ENOMEM;
    return -1;
  }

  size_t i;
  for( i = position+1; i < array_size(array); ++i) {
    array->array[i-1] = array->array[i];
  }
  array->size--;

  array_check_realloc(array);
  return 0;
}

/*  forse non serve più */
void array_set_elem(array_o* array, void* element, size_t position){
  if(position >= array->capacity ) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  
  array->array[position] = element;
  return;
}

void array_swap(array_o* array, size_t position_a, size_t position_b){
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
