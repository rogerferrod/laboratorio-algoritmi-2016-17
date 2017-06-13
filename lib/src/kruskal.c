/*
 *  File: kruscal.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


/*
 * Implements the kruskal algorithm
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

enum sort_type {alg_qsort, alg_isort};
#define SORT_TYPE alg_qsort

#if SORT_TYPE == alg_isort
  #define SORT_ALG(array,compare) (insertion_sort((array), (compare)))
#elif SORT_TYPE == alg_qsort
  #define SORT_ALG(array,compare) (quick_sort((array), (compare)))
#else
  #define SORT_ALG(array,compare) (quick_sort((array), (compare)))
#endif

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
  size_t numVertex = graph_order(graph);
  size_t numEdge = graph_size(graph);
  register size_t i;
  
  if (numVertex < 1) {
    return NULL;
  } else if (numEdge == 0) {
    return graph;
  }
  
  if (graph_is_directed(graph)) {
    fprintf(stderr, "Source graph is directed.\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  register graph_o * min = graph_new(numVertex, graph_get_hash_fnc(graph), graph_get_key_compare(graph)); 
  register hashtable_o *set_dictionary = hashtable_new(numVertex, graph_get_hash_fnc(graph), graph_get_key_compare(graph));
  register array_o* array = array_new(numEdge);
  void *elem = NULL;
  void *adj = NULL;

  graphIterator *v_iter = graph_vertex_iter_init(graph);
  while(graph_vertex_iter_hasNext(graph, v_iter)){     /* for ∀v ∈ V do */
    graph_vertex_iter_next(graph, v_iter, &elem, &adj);
    hashtable_put(set_dictionary, elem, make_set(elem));
    graph_add(min, elem);

    void* edge_elem = NULL;
    double* edge_weight = NULL;
    graphIterator* edge_iter = graph_edge_iter_init(graph, elem);
    while (graph_edge_iter_hasNext(graph, elem, edge_iter)) {
      graph_edge_iter_next(graph, elem, edge_iter, &edge_elem, &edge_weight);

      int contains = 0;
      for(int i=0; contains == 0 && i<array_size(array); ++i) {
        register edge *tmp = array_at(array, i);
        if (graph_get_key_compare(graph)(tmp->v1, edge_elem) == 0 && graph_get_key_compare(graph)(tmp->v2, elem) == 0 ) {
          contains = 1;
        }
      }
      if (contains == 0) {
        register edge* e = xmalloc(sizeof(edge));
        e->v1 = elem;
        e->v2 = edge_elem;
        e->weight = (double*) edge_weight;
        array_insert(array, e);
      }
    }
    free(edge_iter);
  }
  free(v_iter);
  
  SORT_ALG(array, compare_weight);

  for(i = 0; i<array_size(array); ++i) {  /* for ∀(u, v) ∈ E nell’ordine do */
    register edge e = *(edge*)array_at(array, i);

    set_o *setU = (set_o*)hashtable_find(set_dictionary, e.v1);
    set_o *setV = (set_o*)hashtable_find(set_dictionary, e.v2);
    if (graph_get_key_compare(graph)(find_set(setU), find_set(setV)) != 0) {  /* if Find(u) != Find(v ) then */
      double *new_weight = xmalloc(sizeof(double));
      *new_weight = *e.weight;
      graph_connect(min, e.v1, e.v2, new_weight, NO_DIRECTED);   /* A ← A ∪ (u, v) */
      union_set(setU, setV);    /* Union(u, v) */
    }
  }
  
  for (i=0; i<array_size(array); ++i) {
    free(array_at(array, i));
  }
  array_free(array);
  return min;
}


