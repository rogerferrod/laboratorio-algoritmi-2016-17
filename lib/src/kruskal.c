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

/* cosa deve ritornare? un albero? una lista?*/
void kruskal(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  node_o *list = NULL;
  void *elem = NULL;
  void *adj = NULL;

  set_o **set = (set_o**)malloc(graph_order(graph)*sizeof(set_o*)); //array di set?

  graphIterator *v_iter = graph_vertex_iter_init(graph);
  size_t v_index = 0;
  while(graph_vertex_iter_hasNext(graph, v_iter)){
    graph_vertex_iter_next(graph, v_iter, &elem, &adj);
    printf("%s\n", (char*)elem);
    set[v_index] = make_set(elem);
  }

  free(v_iter);
  free(set);
  return;
}


