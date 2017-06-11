/*
 *  File: kruscal.c
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
#include <assert.h>
#include "lib.h"
#include "array.h"
#include "sort.h"
#include "set.h"
#include "hash.h"
#include "graph.h"
#include "kruskal.h"

typedef struct {
    void *v1;
    void *v2;
    double *weight;
} edge;


static int compare_weight(void* elem1, void* elem2) {
  edge edge1 = *(edge*)elem1;
  edge edge2 = *(edge*)elem2;
  return *edge1.weight - *edge2.weight;
}


graph_o* kruskal(graph_o *graph){
  assert(graph != NULL);
  clock_t timer;

  size_t numVertex = graph_order(graph);
  size_t numEdge = graph_size(graph);

  TIMER_START(timer);
  graph_o * min = graph_new(numVertex, graph_get_hash_fnc(graph), graph_get_key_compare(graph));  //A ←∅
  TIMER_STOP(timer, "kruskal: graph_new");
  TIMER_START(timer);
  hashtable_o *set_dictionary = hashtable_new(numVertex, graph_get_hash_fnc(graph), graph_get_key_compare(graph));
  TIMER_STOP(timer, "kruskal: hashtable_new");
  TIMER_START(timer);
  array_o* array = array_new(numEdge);
  TIMER_STOP(timer, "kruskal: array_new");
  void *elem = NULL;
  void *adj = NULL;

  TIMER_START(timer);
  graphIterator *v_iter = graph_vertex_iter_init(graph);
  while(graph_vertex_iter_hasNext(graph, v_iter)){    //for ∀v ∈ V do
    graph_vertex_iter_next(graph, v_iter, &elem, &adj);

    hashtable_put(set_dictionary, elem, make_set(elem));
    graph_add(min, elem);

    void* edge_elem = NULL;
    double* edge_weight = NULL;
    graphIterator* edge_iter = graph_edge_iter_init(graph, elem);
    while (graph_edge_iter_hasNext(graph, elem, edge_iter)) {
      graph_edge_iter_next(graph, elem, edge_iter, &edge_elem, &edge_weight);

      edge *e = malloc(sizeof(edge));
      e->v1 = elem;
      e->v2 = edge_elem;
      e->weight = (double*)edge_weight;
      array_insert(array, e);
    }
    free(edge_iter);
  }
  free(v_iter);
  TIMER_STOP(timer, "kruskal: make_set & array_insert");

  //ci sono il doppio degli archi perché per esempio c'è sia A-D che D-A
  TIMER_START(timer);
  insertion_sort(array, compare_weight);    //ordina gli archi in ordine non decrescente di peso
//  quick_sort(array, compare_weight);    //ordina gli archi in ordine non decrescente di peso
  TIMER_STOP(timer, "kruskal: quick_sort");

  TIMER_START(timer);
  for(size_t i = 0; i<array_size(array); ++i) {   //for ∀(u, v) ∈ E nell’ordine do
    edge e = *(edge*)array_at(array, i);

    set_o *setU = (set_o*)hashtable_find(set_dictionary, e.v1);
    set_o *setV = (set_o*)hashtable_find(set_dictionary, e.v2);
    if (graph_get_key_compare(graph)(find_set(setU), find_set(setV)) != 0) {  //  if Find(u) != Find(v ) then
      graph_connect(min, e.v1, e.v2, e.weight, DIRECTED);   //A ← A ∪ (u, v)
      union_set(setU, setV);    //Union(u, v)
    }
  }
  TIMER_STOP(timer, "kruskal: graph_connect & union_set");

  TIMER_START(timer);
  for (size_t i=0; i<array_size(array); ++i) {
    free(array_at(array, i));
  }
  array_free(array);
  TIMER_STOP(timer, "kruskal: free_array");
  return min;
}


