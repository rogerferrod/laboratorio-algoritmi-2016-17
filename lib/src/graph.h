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

#define ORIENTED 0x00
#define NO_ORIENTED 0x01 


/* Definition of the graph's opaque type */
typedef struct _myGraph graph_o;

/* Definition of the graph's compare function */
typedef int (*GraphCompare)(void*, void*);

typedef struct _myHashEntry* graphIterator;


/* Return a newly allocated graph */
extern graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare);

extern void graph_free(graph_o *graph);

extern size_t graph_size(graph_o *graph);

extern void graph_add(graph_o *graph, void *elem);

extern void graph_connect(graph_o *graph, void *x, void *y, float *weight, int bitmask);

extern int graph_contains_vertex(graph_o *graph, void *v1);

extern int graph_contains_edge(graph_o *graph, void *v1, void *v2);

extern void graph_vertex_iter_init(graph_o *graph, graphIterator *iter);

extern int graph_vertex_iter_hasNext(graph_o *graph, graphIterator *iter);

extern void graph_vertex_iter_next(graph_o *graph, graphIterator *iter, void **elem, void **adj);

extern void graph_edge_iter_init(graph_o *graph, void *elem, graphIterator *iter);

extern int graph_edge_iter_hasNext(graph_o *graph, void *elem, graphIterator *iter);

extern void graph_edge_iter_next(graph_o *graph, void *elem, graphIterator *iter, void **adj_elem, float **weight);

