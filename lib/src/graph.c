/*
 *  File: graph.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Implements an abstracted graph
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "array.h"
#include "list.h"
#include "hash.h"
#include "graph.h"

#define EDGE_CAPACITY 5


#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}

#define ASSERT_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "NULL Pointer FAIL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}

/* Implementation of the opaque type */
struct _myGraph {
    hashtable_o *V;
    hash_fnc hash;
    KeyCompare compare;
};


/* riorganizzare gli argomenti! */
graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  graph_o *graph = malloc(sizeof(graph_o));
  if(graph == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  graph->hash = hash;
  graph->compare = compare;
  graph->V = hashtable_new(capacity, graph->hash, graph->compare);
  return graph;
}

void graph_free(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_free(graph->V); //fare la free dei hash_E! (serve iteratore?)
  free(graph);
  return;
}

size_t graph_order(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  return hashtable_size(graph->V);
}

size_t graph_size(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  if (graph_order(graph) == 0) {
    return 0;
  }

  size_t size = 0;
  graphIterator *iter = (graphIterator*)malloc(sizeof(graphIterator));
  graph_vertex_iter_init(graph, iter);

  void *elem = NULL; //(void*)malloc(10*sizeof(void*)); /* nome vertice */
  void *adj = NULL; /* hashtable E */

  while(graph_vertex_iter_hasNext(graph, iter)){
    graph_vertex_iter_next(graph, iter, &elem, &adj);
    size += hashtable_size(adj);
  }

  free(iter);

  return size;
}

void graph_add(graph_o *graph, void *elem){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_new(EDGE_CAPACITY, graph->hash, graph->compare);
  hashtable_put(&(graph->V), elem, E);
  return;
}

void graph_connect(graph_o *graph, void *x, void *y, float *weight, int bitmask){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  ASSERT_PARAMETERS_NOT_NULL(x);
  ASSERT_PARAMETERS_NOT_NULL(y);

  hashtable_o *E = hashtable_find(graph->V, x);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_put(&E, y, weight);
  if((bitmask & NO_ORIENTED) == NO_ORIENTED){
    graph_connect(graph, y, x, weight, ORIENTED);
  }
}

int graph_contains_vertex(graph_o *graph, void *v1){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  return hashtable_find(graph->V, v1) != NULL;
}

int graph_contains_edge(graph_o *graph, void *v1, void *v2){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, v1);
  return (hashtable_size(E) > 0)? hashtable_find(E, v2) != NULL : 0;
}

void graph_vertex_iter_init(graph_o *graph, graphIterator *iter) {
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_iter_init(graph->V, (iterator*)iter);
  return;
}

int graph_vertex_iter_hasNext(graph_o *graph, graphIterator *iter) {
  ASSERT_PARAMETERS_NOT_NULL(graph);
  return hashtable_iter_hasNext(graph->V, iter);
}

void graph_vertex_iter_next(graph_o *graph, graphIterator *iter, void **elem, void **adj) {
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_iter_next(graph->V, iter, elem, adj);
  return;
}

void graph_edge_iter_init(graph_o *graph, void *elem, graphIterator *iter){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_iter_init(E, iter);
  return;
}

int graph_edge_iter_hasNext(graph_o *graph, void *elem, graphIterator *iter){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  return hashtable_iter_hasNext(E, iter);
}

void graph_edge_iter_next(graph_o *graph, void *elem, graphIterator *iter, void **adj_elem, float **weight){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_iter_next(E, iter, adj_elem, (void**)weight);
}




