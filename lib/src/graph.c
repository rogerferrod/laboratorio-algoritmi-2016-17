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
#include "graph.h"
#include "array.h"
#include "list.h"
#include "hash.h"

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
  hashtable_free(graph->V); //fare la free dei hash_E! (serve iteratore?)
  free(graph);
  return;
}

size_t graph_size(graph_o *graph){
  return hashtable_size(graph->V);
}

void graph_add(graph_o *graph, void *elem){
  hashtable_o *E = hashtable_new(EDGE_CAPACITY, graph->hash, graph->compare);
  hashtable_insert(&(graph->V), elem, E);
  return;
}

void graph_link(graph_o *graph, void *x, void *y, float *weight, int bitmask){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  ASSERT_PARAMETERS_NOT_NULL(x);
  ASSERT_PARAMETERS_NOT_NULL(y);

  hashtable_o *E = hashtable_find(graph->V, x);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_insert(&E, y, weight);
  if((bitmask & NO_ORIENTED) == NO_ORIENTED){
    graph_link(graph, y, x, weight, ORIENTED);
  }
}

int graph_contains_vertex(graph_o *graph, void *v1){
  return hashtable_find(graph->V, v1) != NULL;
}

int graph_contains_edge(graph_o *graph, void *v1, void *v2){
  hashtable_o *E = hashtable_find(graph->V, v1);
  return (hashtable_size(E) > 0)? hashtable_find(E, v2) != NULL : 0;
}



