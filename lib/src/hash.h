/*
 *  File: hash.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


/*
 * Defines an abstracted hashtable.
 */

#pragma once

#include <stddef.h>
#include "lib.h"

/* Definition of the graph's opaque type. */
typedef struct _myHashtable hashtable_o;

/* Definition of the compare function. */
typedef int (*KeyCompare)(void*, void*);

/* Definition of the hash function. */
typedef size_t (*hash_fnc)(void* key);

/* Definition of the hashtable iterator entry. */
typedef struct _myHashEntry* iterator;


/* Return a newly allocated hash table */
extern hashtable_o* hashtable_new(size_t capacity, hash_fnc hash, KeyCompare compare);

/* Deallocate a hashtable. */
extern void hashtable_free(hashtable_o *hashtable);

/* Adds a couple key-value in the given hashtable. */
extern void hashtable_put(hashtable_o *table, void *key, void *value);

/* Return the elem with the associated key if exists, NULL otherwise. */
extern void* hashtable_find(hashtable_o *table, void *key);

/* Remove the couple the the given key if exists. */
extern void hashtable_remove(hashtable_o *table, void *key);

/* Returns the size of the hashtable. */
extern size_t hashtable_size(hashtable_o *table);

/* Returns the capacity of the hashtable. */
extern size_t hashtable_capacity(hashtable_o *table);

/* Initialize the hashtable iterator. */
extern iterator *hashtable_iter_init(hashtable_o *table);

/* Returns 1 if the hashtable has another couple, 0 otherwise. */
extern int hashtable_iter_hasNext(hashtable_o *table, iterator *iter);

/* Moves the iterator on the next couple key-value. */
extern void hashtable_iter_next(hashtable_o *table, iterator *iter, void **key, void **value);

/* Check if the hashtable contains the given key. */
extern int hashtable_contains(hashtable_o *table, void* key);
