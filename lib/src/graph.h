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

/* |V| */
extern size_t graph_order(graph_o *graph);

/* |E| */
extern size_t graph_size(graph_o *graph);

extern void graph_add(graph_o *graph, void *elem);

extern void graph_connect(graph_o *graph, void *x, void *y, double *weight, int bitmask);

extern int graph_contains_vertex(graph_o *graph, void *v);

extern int graph_contains_edge(graph_o *graph, void *v1, void *v2);

extern size_t graph_vertex_degree(graph_o *graph, void *v);

extern hash_fnc graph_get_hash_fnc(graph_o *graph);

extern KeyCompare graph_get_key_compare(graph_o *graph);


/* Vertex iterator */
extern graphIterator *graph_vertex_iter_init(graph_o *graph);

extern int graph_vertex_iter_hasNext(graph_o *graph, graphIterator *iter);

extern void graph_vertex_iter_next(graph_o *graph, graphIterator *iter, void **elem, void **adj);

/* Edge iterator */
extern graphIterator *graph_edge_iter_init(graph_o *graph, void *elem);

extern int graph_edge_iter_hasNext(graph_o *graph, void *elem, graphIterator *iter);

extern void graph_edge_iter_next(graph_o *graph, void *elem, graphIterator *iter, void **adj_elem, double **weight);

