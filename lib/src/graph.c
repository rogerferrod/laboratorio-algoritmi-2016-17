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
#include "set.h"
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
  graphIterator *iter = graph_vertex_iter_init(graph);

  void *elem = NULL;
  void *adj = NULL;

  while(graph_vertex_iter_hasNext(graph, iter)){
    graph_vertex_iter_next(graph, iter, &elem, &adj);
    size += hashtable_size(adj);
  }

  free(iter);

  return size;
}

double graph_weight(graph_o *graph) {
  ASSERT_PARAMETERS_NOT_NULL(graph);

  typedef struct {
      void *v1;
      void *v2;
  } edge;

  double graph_weight = 0;
  hashtable_o *set_dictionary = hashtable_new(graph_order(graph), graph_get_hash_fnc(graph), graph_get_key_compare(graph));

  void *elem = NULL;
  void *adj = NULL;
  graphIterator *v_iter = graph_vertex_iter_init(graph);
  while(graph_vertex_iter_hasNext(graph, v_iter)){
    graph_vertex_iter_next(graph, v_iter, &elem, &adj);

    printf("h_put %s\n", elem);
    hashtable_put(&set_dictionary, elem, make_set(elem));
  }
  free(v_iter);
  printf("FINE VERTICI\n");

  iterator *hIter = hashtable_iter_init(set_dictionary);
  while(hashtable_iter_hasNext(set_dictionary, hIter)) {
    hashtable_iter_next(set_dictionary, hIter, &elem, &adj);

    void *edge = NULL;
    double *weight = NULL;
    graphIterator *e_iter = graph_edge_iter_init(graph, elem);
    while(graph_edge_iter_hasNext(graph, elem, e_iter)){
      graph_edge_iter_next(graph, elem, e_iter, &edge, &weight);

      set_o *setU = (set_o*)hashtable_find(set_dictionary, elem);
      set_o *setV = (set_o*)hashtable_find(set_dictionary, edge);

      if (graph_get_key_compare(graph)(find_set(setU), find_set(setV)) != 0) {  //  if Find(u) != Find(v ) then
        union_set(setU, setV);    //Union(u, v)
        printf("%s - %s - %lf\n", elem, edge, *weight);
        //printf("%lf\n", graph_weight);
        graph_weight += *weight;
      }

    }
    free(e_iter);
  }
  free(hIter);
  return graph_weight;
}

void graph_add(graph_o *graph, void *elem){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_new(EDGE_CAPACITY, graph->hash, graph->compare);
  hashtable_put(&(graph->V), elem, E);
  return;
}

void graph_connect(graph_o *graph, void *x, void *y, double *weight, int bitmask){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  ASSERT_PARAMETERS_NOT_NULL(x);
  if (!graph_contains_vertex(graph, y)) {
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  hashtable_o **E = (hashtable_o**)hashtable_lookup(graph->V, x);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_put(E, y, weight);
  if((bitmask & NO_ORIENTED) == NO_ORIENTED){
    graph_connect(graph, y, x, weight, ORIENTED);
  }
}

int graph_contains_vertex(graph_o *graph, void *v){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  return hashtable_find(graph->V, v) != NULL;
}

int graph_contains_edge(graph_o *graph, void *v1, void *v2){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, v1);
  return (hashtable_size(E) > 0)? hashtable_find(E, v2) != NULL : 0;
}

size_t graph_vertex_degree(graph_o *graph, void *v) {
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, v);
  ASSERT_NOT_NULL(E);
  return hashtable_size(E);
}

hash_fnc graph_get_hash_fnc(graph_o *graph) {
  return graph->hash;
}

KeyCompare graph_get_key_compare(graph_o *graph) {
  return graph->compare;
}

graphIterator *graph_vertex_iter_init(graph_o *graph) {
  ASSERT_PARAMETERS_NOT_NULL(graph);
  return (graphIterator*)hashtable_iter_init(graph->V);
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

graphIterator *graph_edge_iter_init(graph_o *graph, void *elem){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  return (graphIterator*)hashtable_iter_init(E);
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

void graph_edge_iter_next(graph_o *graph, void *elem, graphIterator *iter, void **adj_elem, double **weight){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_iter_next(E, iter, adj_elem, (void**)weight);
}




