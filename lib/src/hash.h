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
typedef int (*HashCompare)(void*, void*);



/* Return a newly allocated hash table */
extern hashtable_o* hashtable_new(size_t capacity);

extern void hashtable_free(hashtable_o *graph);
