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
  list_o **array;           /* generic array */
  size_t size;              /* size of the array */
  size_t capacity;          /* capacity of the array */
}array_h;

/* Implementation of the opaque type */
struct _myHashtable {
  array_h *T;           /* generic dynamic array */
  hash_fnc hash;
  size_t size;
};

/* Return a newly allocated array */
array_h* array_new(size_t);

/* Deallocate an array */
void array_free(array_h*);

size_t array_size(array_h*);

size_t array_capacity(array_h*);

/* Return a pointer to the element in the specified position */
list_o* array_at(array_h*, size_t);

void array_insert_at(array_h*, size_t, list_o*);

hashtable_o* hashtable_new(size_t capacity, hash_fnc hash) {
  hashtable_o *table = malloc(sizeof(hashtable_o));
  if(table == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  table->T = array_new(capacity);
  table->hash = hash;
  table->size = 0;
  return table;
}

void hashtable_free(hashtable_o *table){
  for(size_t i = 0; i < array_capacity(table->T); ++i){
    list_o *list = array_at(table->T, i);
    if(list != NULL){
      list_free(list); // <--- il problema è qui
      array_insert_at(table->T, i, NULL);
    }
  }
  array_free(table->T);
  free(table);
  return;
}

void* hashtable_search(hashtable_o *table, void *key, HashCompare compare){
  size_t index = table->hash(key);
  list_o *list = array_at(table->T, index);
  return (list != NULL)? list_search(list, key, compare) : NULL;
}

void hashtable_insert(hashtable_o *table, void *key){ /* controllare se non esiste già! */
  size_t index = table->hash(key);
  list_o *list = array_at(table->T, index);
  if(list == NULL){
    list_o llist = list_new(key);
    list = &llist;
    array_insert_at(table->T, index, list);
  }
  else {
    list_add(list, key);
  }
  table->size++;
  printf("list-insert[0] %s\n", (char*)list_get_at(list, 0));
  return;
}




    



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

list_o* array_at(array_h* array, size_t index) { //NB puo restituire null!
  if(index > array->capacity) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", index, array->capacity);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[index];
}

void array_insert_at(array_h* array, size_t index, list_o* list) {
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
  array->array[index] = list;
  if(index >= array->size){
    array->size++;
  }
  return;
}
