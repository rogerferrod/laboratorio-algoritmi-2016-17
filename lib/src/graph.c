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

/* Implementation of the opaque type */
struct _myGraph {
  array_o *array;             /* generic array */
};

typedef struct _myVertex {
  void *elem;
  list_o *adj;
} vertex_o;

vertex_o *vertex_new(graph_o *graph, size_t index, void *elem);

graph_o* graph_new(size_t capacity) {
  graph_o *graph = malloc(sizeof(graph_o));
  if(graph == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  graph->array = array_new(capacity);
  return graph;
}

vertex_o *vertex_new(graph_o *graph, size_t index, void *elem){
  vertex_o *vertex = malloc(sizeof(vertex_o));
  vertex->elem = elem;
  vertex->adj = malloc(sizeof(list_o)); //controllare NULL
  return vertex;
}

void graph_free(graph_o *graph){
  /* si presuppone che l'utente abbia fatto la free di elem */
  for(size_t i = 0; i < array_size(graph->array); ++i){
    vertex_o *vertex = array_at(graph->array, i);
    list_free(vertex->adj);
    free(vertex);
  }
  array_free(graph->array);
  free(graph);
  return;
}

size_t graph_size(graph_o *graph){
  return array_size(graph->array);
}

void graph_add(graph_o *graph, void *elem){
  vertex_o *vertex = vertex_new(graph, array_size(graph->array), elem);
  array_insert(graph->array, vertex);
  return;
}

void graph_link(graph_o *graph, void *x, void *y){
  /* serve hash table! */
  return;
}

