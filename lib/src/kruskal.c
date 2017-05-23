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
#include "array.h"
#include "sort.h"
#include "set.h"
#include "list.h"
#include "hash.h"
#include "graph.h"
#include "kruskal.h"


#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}

#define ASSERT_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "NULL Pointer FAIL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}

typedef struct {
    void *v1;
    void *v2;
    double weight;
} edge;

static int compare_edge_ptr(void* elem1, void* elem2) {
  edge edge1 = *(edge*)elem1;
  edge edge2 = *(edge*)elem2;
  return edge1.weight - edge2.weight;
}

/*
MST_Kruskal(G)
A ←∅
for ∀v ∈ V do
  Make_set(v )
ordina gli archi in ordine non decrescente di peso
for ∀(u, v ) ∈ E nell’ordine do
  if Find(u)6 = Find(v ) then
    A ← A ∪ (u, v )
    Union(u, v )
 
*/

/* cosa deve ritornare? un albero? una lista? Un grafo*/
graph_o* kruskal(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  //node_o *list = NULL;
  size_t numVertex = graph_order(graph);
  size_t numEdge = graph_size(graph);

  array_o* array = array_new(numEdge);
  void *elem = NULL;
  void *adj = NULL;

  printf("graph_order: %d\n", (unsigned int)graph_order(graph));
  set_o **set = (set_o**)malloc(graph_order(graph)*sizeof(set_o*)); //array di set?

  graphIterator *v_iter = graph_vertex_iter_init(graph);
  size_t v_index = 0;
  while(graph_vertex_iter_hasNext(graph, v_iter)){
    graph_vertex_iter_next(graph, v_iter, &elem, &adj);
    printf("%s\n", (char*)elem);

    if (graph_vertex_degree(graph, elem) != 0){
      void* edge_elem = NULL;
      double* edge_weight = NULL;
      graphIterator* edge_iter = graph_edge_iter_init(graph, elem);
      while (graph_edge_iter_hasNext(graph, elem, edge_iter)) {
        graph_edge_iter_next(graph, elem, edge_iter, &edge_elem, &edge_weight);
        printf("- %s, %lf\n", (char*)edge_elem, *(double*)edge_weight);
        edge *e = malloc(sizeof(edge));
        e->v1 = elem;
        e->v2 = edge_elem;
        e->weight = *(double*)edge_weight;
        array_insert(array, e);
      }
      free(edge_iter);
    }
    set[v_index] = make_set(elem);
    ++v_index;
  }
  quick_sort(array, compare_edge_ptr);
  for(size_t i = 0; i<array_size(array); ++i) {
    edge e = *(edge*)array_at(array, i);
    char *v1 = (char*)e.v1;
    char *v2 = (char*)e.v2;
    double w = e.weight;
    printf("%s - %s - %lf\n", v1, v2, w);
  }

  for (size_t i=0; i<array_size(array); ++i) {
    free(array_at(array, i));
  }
  array_free(array);
  free(v_iter);
  free(set);
  return graph_new(1, graph_get_hash_fnc(graph), graph_get_key_compare(graph));
}


