/*
 *  File: hash.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


/*
 * Implements an abstracted hash table with chaining
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "assert.h"
#include "lib.h"
#include "list.h"
#include "hash.h"

#define MAX_LOAD_FACTOR  0.75


/* Implementation of the opaque type */
typedef struct _myHashArray {
  list_o **array;           /* array */
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
  KeyCompare key_compare;
}hash_entry;

void hashtable_expand(hashtable_o *table);

/* Return a newly allocated array */
array_h* array_h_new(size_t);

/* Deallocate an array */
void array_h_free(array_h*);

/* Returns array's length */
size_t array_h_size(array_h*);

/* Returns the array's capacity */
size_t array_h_capacity(array_h*);

/* Return a pointer to the element in the specified position */
list_o* array_h_at(array_h*, size_t);

/* Inserts element in the specified position with replacement */
void array_h_insert_at(array_h*, size_t, list_o*);

int entry_compare(void *a, void *b);


hashtable_o* hashtable_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  if(capacity == 0) {
    fprintf(stderr, "Invalid parameter: capacity can't be 0\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  if(hash == NULL) {
    fprintf(stderr, "Invalid parameter: hash can't be NULL\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  if(compare == NULL) {
    fprintf(stderr, "Invalid parameter: compare can't be NULL\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  register hashtable_o *table = (hashtable_o*) xmalloc(sizeof(hashtable_o));
  table->T = array_h_new(capacity);
  table->hash = hash;
  table->size = 0;
  table->key_compare = compare;
  table->load_factor = 0;
  return table;
}

void hashtable_free(hashtable_o *table){
  assert(table != NULL);
  array_h_free(table->T);
  free(table);
  return;
}

int entry_compare(void *a, void *b) {
  hash_entry *h1 = (hash_entry*)a;
  return h1->key_compare(h1->key, b);
}

void* hashtable_find(hashtable_o *table, void *key){
  assert(table != NULL);
  assert(key != NULL);
  size_t index = table->hash(key) % array_h_capacity(table->T);
  register list_o *list = array_h_at(table->T, index);
  if(list == NULL){
    return NULL;
  }

  register hash_entry *elem = (hash_entry*)list_find(list, key, entry_compare);
  return elem != NULL? elem->value : NULL;
}

void hashtable_put(hashtable_o *table, void *key, void *value){
  assert(table != NULL);
  assert(key != NULL);

  size_t index = table->hash(key) % array_h_capacity(table->T);
  register list_o *list = array_h_at(table->T, index);

  register hash_entry *entry = (hash_entry*) xmalloc(sizeof(hash_entry));
  entry->key = key;
  entry->value = value;
  entry->key_compare = table->key_compare;

  if(list == NULL){
    list = list_new();
    list_add(list, entry);
    array_h_insert_at(table->T, index, list);
  } else {
    for(size_t i=0; i<list_size(list); ++i) {
      register hash_entry *tmp = list_get_at(list, i);
      if (table->key_compare(key, tmp->key)==0) {
        list_set_at(list, i, entry);
        return;  /* ho aggiornato la lista, posso uscire */
      }
    }

    list_add(list, entry); /* non ho aggiornato la lista: inserisco */
  }
  table->size++;
  table->load_factor = (float)table->size / array_h_capacity(table->T);

  if (table->load_factor > MAX_LOAD_FACTOR) {
    hashtable_expand(table);
  }
  return;
}

void hashtable_remove(hashtable_o *table, void *key){
  assert(table != NULL);
  assert(key != NULL);
  register size_t i;

  size_t index = table->hash(key) % array_h_capacity(table->T);
  register list_o *list = array_h_at(table->T, index);
  if(list == NULL){
    return;
  }
  register hash_entry *entry;
  int removed = 0;
  if(list_size(list) == 1){ /* se c'è solo quell'elemento */
    list_free(list);
    array_h_insert_at(table->T, index, NULL);
    removed = 1;
  } else {
    for(i = 0; i < list_size(list); ++i){
      entry = list_get_at(list, i);
      if(table->key_compare(key, entry->key) == 0){
        list_remove_at(list, i);
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

void hashtable_expand(hashtable_o *table){
  assert(table != NULL);

  register size_t i, j;
  register hash_entry *entry;
  register list_o *list;
  register size_t capacity_old = array_h_capacity(table->T);
  register array_h *old_T = table->T;
  table->T = array_h_new(capacity_old << 1);
  table->size=0;

  for(i = 0; i < capacity_old; ++i){
    list = array_h_at(old_T, i);
    if(list != NULL){
      for(j = 0; j < list_size(list); ++j){
        entry = list_get_at(list, j);
        hashtable_put(table, entry->key, entry->value);
      }
    }
  }
  table->load_factor = (float)table->size / array_h_capacity(table->T);
  array_h_free(old_T);
  return;
}

size_t hashtable_size(hashtable_o *table){
  assert(table != NULL);
  return table->size;
}

size_t hashtable_capacity(hashtable_o *table){
  assert(table != NULL);
  return array_h_capacity(table->T);
}

iterator *hashtable_iter_init(hashtable_o *table){
  assert(table != NULL);
  
  register size_t i;
  register list_o *list;
  register hash_entry *entry;
  iterator *iter = (iterator*) xmalloc(sizeof(iterator));

  for(i = 0; i < array_h_capacity(table->T); ++i){
    list = array_h_at(table->T, i);
    if(list != NULL){
      entry = list_get_at(list, 0);
      assert(entry != NULL);
      *iter = entry;
      return iter;
    }
  }
  *iter = NULL;
  return iter;
}

int hashtable_iter_hasNext(hashtable_o *table, iterator *iter){
  assert(table != NULL);
  assert(iter != NULL);
  return *iter != NULL;
}

void hashtable_iter_next(hashtable_o *table, iterator *iter, void **key, void **value){
  assert(table != NULL);
  assert(iter != NULL);
  
  register size_t i;

  if(*iter == NULL){
    fprintf(stderr, "No such element\n");
    errno = EPERM;
    exit(EXIT_FAILURE);
  }

  register list_o *list;
  register hash_entry *entry = *iter;

  *key = entry->key;
  *value = entry->value;

  size_t array_h_cap = array_h_capacity(table->T);

  /* si sposta al successivo */
  size_t index = table->hash(*key) % array_h_cap;
  list = array_h_at(table->T, index);
  for(i = 0; i < list_size(list); ++i){
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
  for(i = index + 1; i < array_h_cap; ++i){
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
  assert(capacity != 0);

  register size_t i;
  register array_h* new_array = (array_h*) xmalloc(sizeof(array_h));
  new_array->array = (list_o**) xmalloc(sizeof(list_o*)*capacity);

  new_array->size = 0;
  new_array->capacity = capacity;

  for(i = 0; i < capacity; ++i){
    new_array->array[i] = NULL;
  }
  return new_array;
}

void array_h_free(array_h* array) {
  if (array != NULL) {
    size_t capacity = array_h_capacity(array);
    for(register size_t i = 0; i < capacity; ++i){
      list_free(array->array[i]);
    }
    free(array->array);
  }
  free(array);
  return;
}

size_t array_h_size(array_h* array){
  assert(array != NULL);
  return array->size;
}

size_t array_h_capacity(array_h* array){
  assert(array != NULL);
  return array->capacity;
}

list_o* array_h_at(array_h* array, size_t index) { 
  assert(array != NULL);
  assert(index <= array->capacity);
  return array->array[index];
}

void array_h_insert_at(array_h* array, size_t index, list_o* list) {
  assert(array != NULL);
  assert(index <= array->capacity);

  array->array[index] = list;
  if(index >= array->size){
    array->size++;
  }
  return;
}
