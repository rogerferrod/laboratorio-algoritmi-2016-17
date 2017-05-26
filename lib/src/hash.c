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
#include "list.h"
#include "hash.h"

#define MAX_LOAD_FACTOR  0.75

#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}


/* Implementation of the opaque type */
typedef struct _myHashArray {
  node_o **array;           /* array */
  size_t size;              /* size of the array */
  size_t capacity;          /* capacity of the array */
}array_h;

/* Implementation of the opaque type */
struct _myHashtable {
  array_h *T;           /* generic static array */
  hash_fnc hash;
  size_t size;
  KeyCompare key_compare;
  float load_factor;
};

typedef struct _myHashEntry{
  void *key;
  void *value;
}hash_entry;


/* Return a newly allocated array */
array_h* array_h_new(size_t);

/* Deallocate an array */
void array_h_free(array_h*);

/* Returns array's length */
size_t array_h_size(array_h*);

/* Returns the array's capacity */
size_t array_h_capacity(array_h*);

/* Return a pointer to the element in the specified position */
node_o* array_h_at(array_h*, size_t);

/* Inserts element in the specified position with replacement */
void array_h_insert_at(array_h*, size_t, node_o*);



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
  table->load_factor = (float)table->size / capacity;
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

void** hashtable_lookup(hashtable_o *table, void *key) {
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
      return &(entry->value);
    }
  }
  return NULL;
}

void* hashtable_find(hashtable_o *table, void *key){
  void** ptr = hashtable_lookup(table, key);
  return (ptr == NULL) ? NULL : *ptr;
}

/* Insert or Replace*/

void hashtable_put(hashtable_o **table, void *key, void *value){
  ASSERT_PARAMETERS_NOT_NULL(table);
  ASSERT_PARAMETERS_NOT_NULL(key);
  ASSERT_PARAMETERS_NOT_NULL(value);

  size_t index = (*table)->hash(key)% array_h_capacity((*table)->T);
  node_o *list = array_h_at((*table)->T, index);
  hash_entry *entry = (hash_entry*)malloc(sizeof(hash_entry));

  entry->key = key;
  entry->value = value;

  int is_update = 0;
  
  if(list == NULL){
    list = list_new(entry);
  } else {
    if (list_contains(list, entry, (*table)->key_compare) == 1) {
      is_update = 1;
    }
    list_add(&list, entry);
  }
  array_h_insert_at((*table)->T, index, list);
  if (is_update == 0) {
    (*table)->size++;
    (*table)->load_factor = (float)(*table)->size / array_h_capacity((*table)->T);

    if ((*table)->load_factor > MAX_LOAD_FACTOR) {
      hashtable_expand(table);
    }
  }
  return;
}
/*
void hashtable_insert(hashtable_o **table, void *key, void *value){
  ASSERT_PARAMETERS_NOT_NULL(table);
  ASSERT_PARAMETERS_NOT_NULL(key);
  ASSERT_PARAMETERS_NOT_NULL(value);

	if(hashtable_contains(*table,key)){
		fprintf(stderr, "Key already exits\n");
		errno = EPERM;                    
		exit(EXIT_FAILURE);
	}
  hashtable_put(table,key,value);
  return;
}

void hashtable_replace(hashtable_o **table, void *key, void *value){
  ASSERT_PARAMETERS_NOT_NULL(table);
  ASSERT_PARAMETERS_NOT_NULL(key);
  ASSERT_PARAMETERS_NOT_NULL(value);

  if(hashtable_contains(*table,key) == 1){
		fprintf(stderr, "Key does not exits\n");
		errno = EPERM;                    
		exit(EXIT_FAILURE);
	}
  hashtable_put(table,key,value);
  return;
}
*/
void hashtable_remove(hashtable_o *table, void *key){
  ASSERT_PARAMETERS_NOT_NULL(table);
  size_t index = table->hash(key) % array_h_capacity(table->T);
  node_o *list = array_h_at(table->T, index);
  hash_entry *entry;
  size_t removed = 0;
  if(list == NULL){
    return;
  }
  if(list_size(list) == 1){ /* se c'è solo quell elemento */
    list_free(list);
    array_h_insert_at(table->T, index, NULL);
    removed = 1;
  }
  else {
    for(size_t i = 0; i < list_size(list); ++i){
      entry = list_get_at(list, i);
      if(table->key_compare(key, entry->key) == 0){
	list_remove_at(&list, i);
	if (i == 0) {
	  array_h_insert_at(table->T, index, list);
	}
	free(entry);
	removed = 1;
	break;
      }
    }
  }
  if(removed == 1){
    table->size--;
    table->load_factor = (float)table->size / array_h_capacity(table->T);
  }
  return;
}

void hashtable_expand(hashtable_o **table){
  ASSERT_PARAMETERS_NOT_NULL(table);
  hashtable_o *old_table = *table;
  hash_entry *entry;
  node_o *list;
  hashtable_o *new_table;
  size_t capacity_old = array_h_capacity(old_table->T);
  new_table = hashtable_new(capacity_old << 1, old_table->hash, old_table->key_compare);

  for(size_t i = 0; i < capacity_old; ++i){
    list = array_h_at(old_table->T, i);
    if(list != NULL){
      for(size_t j = 0; j < list_size(list); ++j){
        entry = list_get_at(list, j);
        hashtable_put(&new_table, entry->key, entry->value);
      }
    }
  }
  new_table->load_factor = (float)new_table->size / array_h_capacity(new_table->T);
  hashtable_free(old_table);
  *table = new_table;
  return;
}

size_t hashtable_size(hashtable_o *table){
  ASSERT_PARAMETERS_NOT_NULL(table);
  return table->size; 
}

size_t hashtable_capacity(hashtable_o *table){
  ASSERT_PARAMETERS_NOT_NULL(table);
  return array_h_capacity(table->T);
}

iterator *hashtable_iter_init(hashtable_o *table){
  ASSERT_PARAMETERS_NOT_NULL(table);
  node_o *list;
  hash_entry *entry;
  iterator *iter = (iterator*)malloc(sizeof(iterator));

  for(size_t i = 0; i < array_h_capacity(table->T); ++i){
    list = array_h_at(table->T, i);
    if(list != NULL){
      entry = list_get_at(list, 0);
      if(entry == NULL){
        printf("ERRORE entry?\n");
        exit(EXIT_FAILURE);
      }
      *iter = entry; /* iter punta a entry */
      return iter;
    }
  }
  *iter = NULL;
  return iter;
/*
  fprintf(stderr, "No such element\n");
  errno = EPERM;
  exit(EXIT_FAILURE);
*/
}

int hashtable_iter_hasNext(hashtable_o *table, iterator *iter){
  ASSERT_PARAMETERS_NOT_NULL(table);
  ASSERT_PARAMETERS_NOT_NULL(iter);
  return *iter != NULL;
}

void hashtable_iter_next(hashtable_o *table, iterator *iter, void **key, void **value){
  ASSERT_PARAMETERS_NOT_NULL(table);
  ASSERT_PARAMETERS_NOT_NULL(iter);
  if(*iter == NULL){
    fprintf(stderr, "No such element\n");
    errno = EPERM;
    exit(EXIT_FAILURE);
  }
  node_o *list;
  hash_entry *entry = *iter;
  
  *key = entry->key;  //e' possibile copiare  valori?
  *value = entry->value; //invece di passare un puntatore che è modificabile?

  /* si sposta al successivo */
  size_t index = table->hash(*key)% array_h_capacity(table->T);
  list = array_h_at(table->T, index);
  for(size_t i = 0; i < list_size(list); ++i){
    entry = list_get_at(list, i);
    if(table->key_compare(*key, entry->key) == 0){ /* ritrovato il punto esatto */
      if(++i < list_size(list)){ /* se ha un next nella stessa lista */
	entry = list_get_at(list, i);
	*iter = entry;
	return;
      }
    }
  }

  /* se non e' nella lista riprovo sull'array */
  for(size_t i = index + 1; i < array_h_capacity(table->T); ++i){
    list = array_h_at(table->T, i);
    if(list != NULL){
      entry = list_get_at(list, 0);
      *iter = entry;
      return;
    }
  }

  /* no next */
  *iter = NULL;
  return;
}

int hashtable_contains(hashtable_o *table,void *key){

	return hashtable_find(table,key) != NULL;
}

/*
 * Implementation of
 * static array for table T
 * 
 */
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
    new_array->array[i] = NULL;  // usare memset
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
  if(index > array->capacity) {
    fprintf(stderr, "Array index (%d) out of bounds (0:%d)\n", (unsigned int)index, (unsigned int)array->capacity);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  array->array[index] = list;
  if(index >= array->size){
    array->size++;
  }
  return;
}
