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

#define EPSILON -1


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
  hashtable_o *E;
};

/* riorganizzare gli argomenti! */
graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  graph_o *graph = malloc(sizeof(graph_o));
  if(graph == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  graph->V = hashtable_new(capacity, hash, compare);
  graph->E = hashtable_new(capacity, hash, compare);
  return graph;
}

void graph_free(graph_o *graph){
  /* si presuppone che l'utente abbia fatto la free di elem */
  hashtable_free(graph->V);
  hashtable_free(graph->E);
  free(graph);
  return;
}

size_t graph_size(graph_o *graph){
  return hashtable_size(graph->V);
}

void graph_add(graph_o *graph, void *elem){
  int* val = (int*) malloc(sizeof(int));
  *val = EPSILON;
  hashtable_insert(graph->V, elem, val);
  return;
}

void graph_link(graph_o *graph, void *x, void *y, int weight, int bitmask){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  ASSERT_PARAMETERS_NOT_NULL(x);
  ASSERT_PARAMETERS_NOT_NULL(y);		
  /* oriented */
  hashtable_insert(graph->V, x, y);
  hashtable_insert(graph->E, y, weight);  

  if((bitmask & NO_ORIENTED) == NO_ORIENTED){
    printf("no oriented!\n");
    
  }
  
  return;
}

int graph_contains_vertex(graph_o *graph, void *v1){
  return hashtable_search(graph->V, v1) != NULL;
}

int graph_contains_edge(graph_o *graph, void *v1, void *v2){
  void *vertex = hashtable_search(graph->V, v1);
  if(*(int*)vertex != EPSILON){
    void *edge = hashtable_search(graph->E, vertex);
    printf("edge == NULL? %d\n", edge == NULL);
    return edge != NULL;
  }
  return 0;
}



