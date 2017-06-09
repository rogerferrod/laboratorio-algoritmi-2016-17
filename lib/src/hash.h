/*
 *  File: hash.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Defines an *
 *
 *
 */

#pragma once

#include <stddef.h>


/* Definition of the graph's opaque type */
typedef struct _myHashtable hashtable_o;

/* Definition of the compare function */
typedef int (*KeyCompare)(void*, void*);

typedef size_t (*hash_fnc)(void* key);

typedef struct _myHashEntry* iterator;

typedef struct _myHashEntry{
    void *key;
    void *value;
}hash_entry;



/* Return a newly allocated hash table */
extern hashtable_o* hashtable_new(size_t capacity, hash_fnc hash, KeyCompare compare);

extern void hashtable_free(hashtable_o *hashtable);

extern void hashtable_put(hashtable_o *table, void *key, void *value);

extern void* hashtable_find(hashtable_o *table, void *key);

extern void hashtable_remove(hashtable_o *table, void *key);

extern size_t hashtable_size(hashtable_o *table);

extern size_t hashtable_capacity(hashtable_o *table);

extern iterator *hashtable_iter_init(hashtable_o *table);

extern int hashtable_iter_hasNext(hashtable_o *table, iterator *iter);

extern void hashtable_iter_next(hashtable_o *table, iterator *iter, void **key, void **value);

extern int hashtable_contains(hashtable_o *table, void* key);
