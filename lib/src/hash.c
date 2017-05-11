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
  node_o **array;           /* generic array */  /* statico */
  size_t size;              /* size of the array */
  size_t capacity;          /* capacity of the array */
}array_h;

/* Implementation of the opaque type */
struct _myHashtable {
  array_h *T;           /* generic dynamic array */
  hash_fnc hash;
  size_t size;
  KeyCompare key_compare;
};

typedef struct _myHashEntry{
  void *key;
  void *value;
  /* +hash code? */
}hash_entry;

/* Return a newly allocated array */
array_h* array_new(size_t);

/* Deallocate an array */
void array_free(array_h*);

size_t array_size(array_h*);

size_t array_capacity(array_h*);

/* Return a pointer to the element in the specified position */
node_o* array_at(array_h*, size_t);

void array_insert_at(array_h*, size_t, node_o*);

hashtable_o* hashtable_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  hashtable_o *table = malloc(sizeof(hashtable_o));
  if(table == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  table->T = array_new(capacity);
  table->hash = hash;
  table->size = 0;
  table->key_compare = compare;
  return table;
}

void hashtable_free(hashtable_o *table){
  for(size_t i = 0; i < array_capacity(table->T); ++i){
    node_o *list = array_at(table->T, i);
    if(list != NULL){
      for(size_t j = 0; j < list_size(list); ++j){
	free(list_get_at(list, j));
      }
      list_free(list);
    }
  }
  array_free(table->T);
  free(table);
  return;
}

void* hashtable_search(hashtable_o *table, void *key){
  size_t index = table->hash(key);
  node_o *list = array_at(table->T, index);
  hash_entry *entry = NULL;
  if(list == NULL){
    return NULL;
  }
  for(size_t i = 0; i < list_size(list); ++i){
    entry = list_get_at(list, i);
    if(table->key_compare(key, entry->key) == 0){
      return entry->value;
    }
  }
  return NULL;
}

void hashtable_insert(hashtable_o *table, void *key, void *value){ /*controllare se non esiste già? */
  size_t index = table->hash(key);
  node_o *list = array_at(table->T, index);
  hash_entry *entry = (hash_entry*)malloc(sizeof(hash_entry));
  entry->key = key;
  entry->value = value;

  if(list == NULL){
    list = list_new(entry);
    array_insert_at(table->T, index, list);
  }
  else {
    list_add(&list, entry);
    array_insert_at(table->T, index, list);  //perchè serve?
  }
  table->size++;
  return;
}


void hashtable_remove(hashtable_o *table, void *key){
  size_t index = table->hash(key);
  node_o *list = array_at(table->T, index);
  hash_entry *entry;
  if(list == NULL){
    return;
  }
  if(list_size(list) == 1){ /* se c'è solo quell elemento */
    list_free(list);
    array_insert_at(table->T, index, NULL);
    return;
  }
  for(size_t i = 0; i < list_size(list); ++i){
    entry = list_get_at(list, i);
    if(table->key_compare(key, entry->key) == 0){
      free(entry);
      list_remove_at(&list, i);
      break;
    }
  }
  return;
}





    



array_h* array_new(size_t capacity) {
  array_h* new_array = (array_h*)malloc(sizeof(array_h));
  if (new_array != NULL){
    new_array->array = (node_o**)malloc(sizeof(void*)*capacity);
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

node_o* array_at(array_h* array, size_t index) { //NB puo restituire null!
  if(index > array->capacity) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", index, array->capacity);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[index];
}

void array_insert_at(array_h* array, size_t index, node_o* list) {
  array->array[index] = list;
  if(index >= array->size){
    array->size++;
  }
  return;
}
