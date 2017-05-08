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


graph_o* graph_new(size_t capacity) {
  graph_o *graph = malloc(sizeof(graph_o));
  if(graph != NULL){
    graph->array = array_new(capacity);
    if (graph->array != NULL) {
      return graph;
    }
  }
  
  fprintf(stderr, "Not enough space for malloc\n");
  errno = ENOMEM;
  exit(EXIT_FAILURE);
}
