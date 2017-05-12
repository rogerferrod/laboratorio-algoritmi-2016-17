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
  array_o *V;             /* generic dynamic array */
  hashtable_o *hash_map;
};

typedef struct _myVertex {
  void *elem;
  void *adj;
} vertex_o;

vertex_o *vertex_new(graph_o *graph, size_t index, void *elem);
vertex_o *graph_get(graph_o *graph, void *elem);

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
	size_t *index = (size_t*) malloc(sizeof(size_t));//TODO : da fare la free
  *index = array_size(graph->V);
  array_insert(graph->V, vertex);
  hashtable_insert(graph->hash_map, elem, index);
  return;
}

vertex_o *graph_get(graph_o *graph, void *elem){
	void* found = hashtable_search(graph->hash_map, elem);
	if (found == NULL){
		return NULL;
	}
	size_t index = *(size_t*)found;
	return array_at(graph->V,index);

}

//void graph_build_arch

void graph_link(graph_o *graph, void *x, void *y, int weight, int bitmask){
	ASSERT_PARAMETERS_NOT_NULL(graph);
	ASSERT_PARAMETERS_NOT_NULL(x);
	ASSERT_PARAMETERS_NOT_NULL(y);
	node_o *list;
			
	printf("oriented!\n");
	vertex_o *vertex_a = graph_get(graph, x);
	vertex_o *vertex_b = graph_get(graph, y);
	ASSERT_NOT_NULL(vertex_a);
	ASSERT_NOT_NULL(vertex_b);

	void* found = hashtable_search(graph->hash_map, vertex_a->elem);
	ASSERT_NOT_NULL(found);

	size_t index = *(size_t*)found;
	vertex_o *vertex = array_at(graph->V,index);
	
	if(vertex == NULL){
		list = list_new(vertex_b);
	} else {
		list_add(&list, vertex_b);
	}
	array_set(graph->V, index, list);
	

	if((bitmask & NO_ORIENTED) == NO_ORIENTED){
    printf("no oriented!\n");
		
  }
  
  return;
}




