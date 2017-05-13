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
array_h* array_h_new(size_t);

/* Deallocate an array */
void array_h_free(array_h*);

size_t array_h_size(array_h*);

size_t array_h_capacity(array_h*);

/* Return a pointer to the element in the specified position */
node_o* array_h_at(array_h*, size_t);

void array_h_insert_at(array_h*, size_t, node_o*);


/* usare la memset per settare a NULL gli elementi! */
hashtable_o* hashtable_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  if(capacity == 0) {
    fprintf(stderr, "Invalid parameter: capacity can't be 0\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  ASSERT_PARAMETERS_NOT_NULL(hash);
  ASSERT_PARAMETERS_NOT_NULL(compare);

  hashtable_o *table = malloc(sizeof(hashtable_o));
  if(table == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  table->T = array_h_new(capacity);
  table->hash = hash;
  table->size = 0;
  table->key_compare = compare;
  return table;
}

void hashtable_free(hashtable_o *table){
  ASSERT_PARAMETERS_NOT_NULL(table);
  for(size_t i = 0; i < array_h_capacity(table->T); ++i){
    node_o *list = array_h_at(table->T, i);
    if(list != NULL){
      for(size_t j = 0; j < list_size(list); ++j){
        free(list_get_at(list, j));
      }
      list_free(list);
    }
  }
  array_h_free(table->T);
  free(table);
  return;
}

void* hashtable_search(hashtable_o *table, void *key){
  ASSERT_PARAMETERS_NOT_NULL(table);
  size_t index = table->hash(key) % array_h_capacity(table->T);
  node_o *list = array_h_at(table->T, index);
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
  ASSERT_PARAMETERS_NOT_NULL(table);
	ASSERT_PARAMETERS_NOT_NULL(key);
	ASSERT_PARAMETERS_NOT_NULL(value);

  size_t index = table->hash(key)% array_h_capacity(table->T);
  node_o *list = array_h_at(table->T, index);
  hash_entry *entry = (hash_entry*)malloc(sizeof(hash_entry));

  entry->key = key;
  entry->value = value;

  if(list == NULL){
    list = list_new(entry);
  } else {
    list_add(&list, entry);
  }
  array_h_insert_at(table->T, index, list);
  table->size++;
  return;
}


void hashtable_remove(hashtable_o *table, void *key){
  ASSERT_PARAMETERS_NOT_NULL(table);
  size_t index = table->hash(key) % array_h_capacity(table->T);
  node_o *list = array_h_at(table->T, index);
  hash_entry *entry;
  if(list == NULL){
    return;
  }
  if(list_size(list) == 1){ /* se c'è solo quell elemento */
    list_free(list);
    array_h_insert_at(table->T, index, NULL);
    return;
  }
  for(size_t i = 0; i < list_size(list); ++i){
    entry = list_get_at(list, i);
    if(table->key_compare(key, entry->key) == 0){
      list_remove_at(&list, i);
      if (i == 0) {
        array_h_insert_at(table->T, index, list);
      }
      free(entry);
      break;
    }
  }
  return;
}

void hashtable_expand(hashtable_o **table){
  ASSERT_PARAMETERS_NOT_NULL(*table);
  hash_entry *entry;
  node_o *list;
  size_t capacity_old = array_h_capacity((*table)->T);
  hashtable_o *new_table = hashtable_new(capacity_old*REALLOC_FACTOR, (*table)->hash, (*table)->key_compare);

  for(size_t i = 0; i < capacity_old; ++i){
    list = array_h_at((*table)->T, i);
    if(list != NULL){
      for(size_t j = 0; j < list_size(list); ++j){
        entry = list_get_at(list, j);
        hashtable_insert(new_table, entry->key, entry->value);
      }
    }
  }
  hashtable_free((*table));
  *table = new_table;
  
  return;
}

size_t hashtable_size(hashtable_o *table){
  ASSERT_PARAMETERS_NOT_NULL(table);
  return table->size; 
}





    



array_h* array_h_new(size_t capacity) {
  if(capacity == 0) {
    fprintf(stderr, "Invalid parameter: capacity can't be 0\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  array_h* new_array = (array_h*)malloc(sizeof(array_h));
  if (new_array == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  new_array->array = (node_o**)malloc(sizeof(void*)*capacity);
  if (new_array->array == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  new_array->size = 0;
  new_array->capacity = capacity;
  for(size_t i = 0; i < capacity; ++i){
    new_array->array[i] = NULL;
  }
  return new_array;
}

void array_h_free(array_h* array) {
  if (array != NULL) {
    free(array->array);
  }
  free(array);
  return;
}

size_t array_h_size(array_h* array){
  ASSERT_PARAMETERS_NOT_NULL(array);
  return array->size;
}

size_t array_h_capacity(array_h* array){
  ASSERT_PARAMETERS_NOT_NULL(array);
  return array->capacity;
}

node_o* array_h_at(array_h* array, size_t index) { //NB puo restituire null!
  ASSERT_PARAMETERS_NOT_NULL(array);
  if(index > array->capacity) {
    fprintf(stderr, "Array index (%d) out of bounds (0:%d)\n", (unsigned int)index, (unsigned int)array->capacity);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return array->array[index];
}

void array_h_insert_at(array_h* array, size_t index, node_o* list) {
  ASSERT_PARAMETERS_NOT_NULL(array);
  array->array[index] = list;
  if(index >= array->size){
    array->size++;
  }
  return;
}
