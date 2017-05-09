/*
 *  File: hash.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */
 
 
/*
 * Implements an abstracted hash table with chaining
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "hash.h"
#include "list.h"

#define REALLOC_FACTOR   2.25 /* 1.5*(3/2) */
#define DECREMENT_LIMIT  0.25 /* 1/4 */

/* usare la memset per settare a NULL gli elementi! */

#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}


/* Implementation of the opaque type */
typedef struct _myHashArray {
  list_o **array;             /* generic array */
  size_t size;              /* size of the array */
  size_t capacity;          /* capacity of the array */
}array_h;

/* Implementation of the opaque type */
struct _myHashtable {
  array_h *array;             /* generic dynamic array */
};

/* Return a newly allocated array */
array_h* array_new(size_t capacity);

/* Deallocate an array */
void array_free(array_h* array);

size_t array_size(array_h* array);

size_t array_capacity(array_h* array);

/* Return a pointer to the element in the specified position */
list_o* array_at(array_h* array, size_t key);

void array_insert_at(array_h* array, size_t key, void* element);

hashtable_o* hashtable_new(size_t capacity) {
  hashtable_o *table = malloc(sizeof(hashtable_o));
  if(table == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  table->array = array_new(capacity);
  return table;
}

void hashtable_free(hashtable_o *table){
  for(size_t i = 0; i < array_capacity(table->array); ++i){
    if(array_at(table->array, i) != NULL){
      list_free(array_at(table->array, i)); //&?
      array_insert_at(table->array, i, NULL);
    }
  }
  array_free(table->array);
  free(table);
  return;
}
/*
void hashtable_put(hashtable_o *table, size_t key, void *value){
  if(array_at(table->array, key) == NULL)
  
  }*/





    



array_h* array_new(size_t capacity) {
  array_h* new_array = (array_h*)malloc(sizeof(array_h));
  if (new_array != NULL){
    new_array->array = (list_o**)malloc(sizeof(void*)*capacity);
    if (new_array->array != NULL) {
      new_array->size = 0;
      new_array->capacity = capacity;
      for(size_t i = 0; i < capacity; ++i){
	new_array->array[i] = NULL;
      }
      return new_array;
    }
  }
  fprintf(stderr, "Not enough space for malloc\n");
  errno = ENOMEM;
  exit(EXIT_FAILURE);
}

void array_free(array_h* array) {
  free(array->array);
  free(array);
  return;
}

size_t array_size(array_h* array){
  return array->size;
}

size_t array_capacity(array_h* array){
  return array->capacity;
}

list_o* array_at(array_h* array, size_t position) { //NB puo restituire null!
  if(position > array->capacity) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->capacity);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[position];
}

void array_insert_at(array_h* array, size_t index, void* element) {
  if(index >= array->capacity){
    array->capacity *= REALLOC_FACTOR;
    array->array = realloc(array->array, array->capacity*sizeof(void*));
    if(array->array == NULL){
      fprintf(stderr, "Not enough memory for realloc\n");
      errno = ENOMEM;
      exit(EXIT_FAILURE);
    }
    for(size_t i = array->size; i < array->capacity; ++i){
      array->array[i] = NULL;
    }
  }
  array->array[index] = element;
  if(index >= array->size){
    array->size++;
  }
  return;
}

