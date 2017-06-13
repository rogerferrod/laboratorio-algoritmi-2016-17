/*
 *  File: graph.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
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

#define DIRECTED 0x01
#define NO_DIRECTED 0x02


/* Definition of the graph's opaque type */
typedef struct _myGraph graph_o;

/* Definition of the graph's compare function */
typedef int (*GraphCompare)(void*, void*);

/*Definition of the Hash's entry*/
typedef struct _myHashEntry* graphIterator;

/* Returns a newly allocated graph */
extern graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare);

/* Deallocate a graph */
extern void graph_free(graph_o *graph);

/* Returns the number of nodes of the graph */
extern size_t graph_order(graph_o *graph);

/* Returns the number of edges of the graph */
extern size_t graph_size(graph_o *graph);

/* Returns the weight of the graph */
extern double graph_weight(graph_o *graph);

/* Adds a node in the given graph  */
extern void graph_add(graph_o *graph, void *elem);

/* Connects the given nodes if they exits */
extern void graph_connect(graph_o *graph, void *x, void *y, double *weight, int bitmask);

/* Returns 1 if the graph contains the vertex,0 otherwise*/
extern int graph_contains_vertex(graph_o *graph, void *v);

/* Returns 1 if the graph contains the edge,0 otherwise*/
extern int graph_contains_edge(graph_o *graph, void *v1, void *v2);

/*Returns the number of edges incident to the vertex*/
extern size_t graph_vertex_degree(graph_o *graph, void *v);

/*Returns the hash function of the graph*/
extern hash_fnc graph_get_hash_fnc(graph_o *graph);

/*Returns the key comparator of the graph*/
extern KeyCompare graph_get_key_compare(graph_o *graph);

/*Returns 1 if the graph is DIRECTED,0 otherwise*/
extern int graph_is_directed(graph_o *graph);

/*Initialize the Vertex iterator */
extern graphIterator *graph_vertex_iter_init(graph_o *graph);

/*Returns 1 if the vertex has an adjacent,0 otherwise*/
extern int graph_vertex_iter_hasNext(graph_o *graph, graphIterator *iter);

/*Moves the iterator on the next vertex*/
extern void graph_vertex_iter_next(graph_o *graph, graphIterator *iter, void **elem, void **adj);

/*Initialize the Edge iterator */
extern graphIterator *graph_edge_iter_init(graph_o *graph, void *elem);

/*Returns 1 if the edge has an next,0 otherwise*/
extern int graph_edge_iter_hasNext(graph_o *graph, void *elem, graphIterator *iter);

/*Moves the iterator on the next edge*/
extern void graph_edge_iter_next(graph_o *graph, void *elem, graphIterator *iter, void **adj_elem, double **weight);


