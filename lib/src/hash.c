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
#include "array.h"
#include "list.h"

/* Implementation of the opaque type */
struct _myHashtable {
  array_o *array;             /* generic dynamic array */
};

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
  for(size_t i = 0; i < array_size(table->array); ++i){
    list_free(array_at(table->array, i)); //&?
  }
  array_free(table->array);
  free(table);
  return;
}
/*
void hashtable_put(hashtable_o *table, size_t key, void *value){
  if(array_at(table->array, key) == NULL)
  
  }*/
