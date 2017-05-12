/*
 *  File: graph.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Defines an abstracted graph. The elements in 
 * the graph are comparable through the compare function
 *
 */

#pragma once

#include <stddef.h>
#include "hash.h"


/* Definition of the graph's opaque type */
typedef struct _myGraph graph_o;

/* Definition of the graph's compare function */
typedef int (*GraphCompare)(void*, void*);



/* Return a newly allocated graph */
extern graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare);

extern void graph_free(graph_o *graph);

extern size_t graph_size(graph_o *graph);

extern void graph_add(graph_o *graph, void *elem);

extern void graph_link(graph_o *graph, void *x, void *y, int weight, int bitmask);

