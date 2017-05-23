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

static double* new_double(double value) {
  double* elem = (double*) malloc(sizeof(double));
  *elem = value;
  return elem;
}

/*
MST_Kruskal(G)
A ←∅
for ∀v ∈ V do
  Make_set(v)
ordina gli archi in ordine non decrescente di peso
for ∀(u, v) ∈ E nell’ordine do
  if Find(u) != Find(v ) then
    A ← A ∪ (u, v)
    Union(u, v)
 
*/

/* cosa deve ritornare? un albero? una lista? Un grafo*/
graph_o* kruskal(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  //node_o *list = NULL;
  size_t numVertex = graph_order(graph);
  size_t numEdge = graph_size(graph);

  graph_o * min = graph_new(numVertex, graph_get_hash_fnc(graph), graph_get_key_compare(graph));  //A ←∅

  array_o* array = array_new(numEdge);
  void *elem = NULL;
  void *adj = NULL;

  printf("graph_order: %d\n", (unsigned int)graph_order(graph));
  set_o **set = (set_o**)malloc(graph_order(graph)*sizeof(set_o*)); //array di set?

  graphIterator *v_iter = graph_vertex_iter_init(graph);
  size_t v_index = 0;
  while(graph_vertex_iter_hasNext(graph, v_iter)){    //for ∀v ∈ V do
    set[v_index] = make_set(elem);    //Make_set(v)
    ++v_index;

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
  }

  quick_sort(array, compare_edge_ptr);    //ordina gli archi in ordine non decrescente di peso

  for(size_t i = 0; i<array_size(array); ++i) {   //for ∀(u, v) ∈ E nell’ordine do
    edge e = *(edge*)array_at(array, i);

    printf("%s - %s - %lf\n", (char*)e.v1, (char*)e.v2, e.weight);

    if (find_set(e.v1) != find_set(e.v2)) {   //  if Find(u) != Find(v ) then
      graph_add(min, e.v1);
      graph_add(min, e.v2);
      graph_connect(min, e.v1, e.v2, new_double(e.weight), ORIENTED);   //A ← A ∪ (u, v)
      union_set(e.v1, e.v2);    //Union(u, v)
    }
  }


  for (size_t i=0; i<array_size(array); ++i) {
    free(array_at(array, i));
  }
  array_free(array);
  free(v_iter);
  free(set);
  return min;
}


