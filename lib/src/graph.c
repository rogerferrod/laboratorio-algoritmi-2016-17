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

#define NO_ORIENTED 0x01 

/* Implementation of the opaque type */
struct _myGraph {
  array_o *V;             /* generic dynamic array */
  hashtable_o *hash_map;
};

typedef struct _myVertex {
  void *elem;
  void *adj;
} vertex_o;

vertex_o *vertex_new(graph_o *graph, size_t index, void *elem);

/* riorganizzare gli argomenti! */
graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  graph_o *graph = malloc(sizeof(graph_o));
  if(graph == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  graph->V = array_new(capacity);
  graph->hash_map = hashtable_new(capacity, hash, compare);
  return graph;
}

vertex_o *vertex_new(graph_o *graph, size_t index, void *elem){
  vertex_o *vertex = malloc(sizeof(vertex_o));
  vertex->elem = elem;
  vertex->adj = NULL;
  return vertex;
}

void graph_free(graph_o *graph){
  /* si presuppone che l'utente abbia fatto la free di elem */
  for(size_t i = 0; i < array_size(graph->V); ++i){
    vertex_o *vertex = array_at(graph->V, i);
    if(vertex->adj != NULL){
      list_free(vertex->adj);
    }
    free(vertex);
  }
  array_free(graph->V);
  free(graph);
  return;
}

size_t graph_size(graph_o *graph){
  return array_size(graph->V);
}

void graph_add(graph_o *graph, void *elem){
  vertex_o *vertex = vertex_new(graph, array_size(graph->V), elem);
  size_t index = array_size(graph->V);
  array_insert(graph->V, vertex);
  
  return;
}

void graph_link(graph_o *graph, void *x, void *y, int weight, int bitmask){
  if((bitmask & NO_ORIENTED) == NO_ORIENTED){
    printf("no oriented!\n");
  }
  
  return;
}


