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
#include "hash.h"
#include "queue.h"
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
    int directed;
};


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
  graph->directed = DIRECTED;
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
      double *weight;
  } my_edge;

  double graph_weight = 0.0;

  array_o *array = array_new(graph_order(graph));

  void *elem = NULL;
  void *adj = NULL;
  graphIterator *v_iter = graph_vertex_iter_init(graph);
  while(graph_vertex_iter_hasNext(graph, v_iter)){
    graph_vertex_iter_next(graph, v_iter, &elem, &adj);

    void *current_edge = NULL;
    double *weight = NULL;
    graphIterator *e_iter = graph_edge_iter_init(graph, elem);
    while(graph_edge_iter_hasNext(graph, elem, e_iter)) {
      graph_edge_iter_next(graph, elem, e_iter, &current_edge, &weight);

      int exists = 0;
      for(size_t i=0; i<array_size(array) && !exists; ++i) {
        my_edge *a =(my_edge*)array_at(array, i);
        //if ((a->v1 == elem && a->v2 == current_edge) || (a->v1 == current_edge && a->v2 == elem)) {
        if ((graph_get_key_compare(graph)(a->v1, elem)==0 && graph_get_key_compare(graph)(a->v2, current_edge)==0) ||
            (graph_get_key_compare(graph)(a->v1, current_edge)==0 && graph_get_key_compare(graph)(a->v2, elem)==0)) {
          exists = 1;
        }
      }
      if (!exists) {
        my_edge *e = malloc(sizeof(my_edge));
        e->v1 = elem;
        e->v2 = current_edge;
        e->weight = weight;

        array_insert(array, e);

        graph_weight += *weight;
      }
    }
    free(e_iter);
  }
  free(v_iter);

  for(size_t i=0; i<array_size(array); ++i) {
    free(array_at(array, i));
  }
  array_free(array);

  return graph_weight;
}

void graph_add(graph_o *graph, void *elem){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  hashtable_o *E = hashtable_new(EDGE_CAPACITY, graph->hash, graph->compare);
  hashtable_put(graph->V, elem, E);
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

  hashtable_o *E = (hashtable_o*)hashtable_find(graph->V, x);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_put(E, y, weight);
  if((bitmask & NO_DIRECTED) == NO_DIRECTED){
    graph->directed = NO_DIRECTED;
    graph_connect(graph, y, x, weight, DIRECTED);
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

void set_color(hashtable_o *table, void *vertex, int color){
  int *status = (int*)malloc(sizeof(int)); //da qualche parte bisognerà fare la free di sta roba
  *status = color;
  hashtable_put(table, vertex, status);
  return;
}

int get_color(hashtable_o *table, void *vertex){
  int *status = hashtable_find(table, vertex);
  if(status != NULL){
    return *status;
  }
  //else che fai???
  printf("HEI!\n");
  return -1;
}
/*
void graph_BFS(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);

  //fai che uscire se vuoto al momento
  if(graph_order(graph) == 0)return;

  // color [V:color]
  enum status{black = 0, grey, white};
  
  hashtable_o *color = hashtable_new(graph_order(graph), graph->hash, graph->compare);
  
  graphIterator *viter = graph_vertex_iter_init(graph);
  graphIterator *eiter;
  void *vertex = NULL;
  void *adj = NULL;
  void *edge = NULL;
  double *weight = NULL;
  int *visited = (int*)malloc(sizeof(int));
  queue_o *queue = queue_new();

  while(graph_vertex_iter_hasNext(graph, viter)){
    graph_vertex_iter_next(graph, viter, &vertex, &adj);
    set_color(color, vertex, white);
  }


  viter = graph_vertex_iter_init(graph);
  graph_vertex_iter_next(graph, viter, &vertex, &adj); //il primo elemento
  set_color(color, vertex, grey);

  queue_enqueue(queue, vertex);

  while(!queue_is_empty(queue)){
    void *u = queue_dequeue(queue);

    eiter = graph_edge_iter_init(graph, u); 
    while(graph_edge_iter_hasNext(graph, u, eiter)){ //for each adj di u : bianco
      graph_edge_iter_next(graph, u, eiter, &edge, &weight);     
      if(get_color(color, edge) == white){
	queue_enqueue(queue, edge);
	set_color(color, edge, grey);
      }
    }
    set_color(color, u, black);
  }

  return;
}
*/
double graph_BFS_weight(graph_o *graph){
  ASSERT_PARAMETERS_NOT_NULL(graph);
  double graph_weight = 0.0;

  if(graph_order(graph) == 0) {
    return 0.0;
  }

  // color [V:color]
  enum status{black = 0, grey, white};
  
  hashtable_o *color = hashtable_new(graph_order(graph), graph->hash, graph->compare);
  
  graphIterator *viter = graph_vertex_iter_init(graph);
  graphIterator *eiter;
  void *vertex = NULL;
  void *adj = NULL;
  void *edge = NULL;
  double *weight = NULL;
  queue_o *queue = queue_new();

  while(graph_vertex_iter_hasNext(graph, viter)){
    graph_vertex_iter_next(graph, viter, &vertex, &adj);
    set_color(color, vertex, white);
  }

  viter = graph_vertex_iter_init(graph);
  graph_vertex_iter_next(graph, viter, &vertex, &adj); //il primo elemento

  printf("parto da %s che ha colore %d\n", (char*)vertex, get_color(color, vertex));
  set_color(color, vertex, grey); //la visita parte da qua
  queue_enqueue(queue, vertex);

  while(!queue_is_empty(queue)){
    void *u = queue_dequeue(queue);
    printf("vertex %s\n", (char*)u);

    eiter = graph_edge_iter_init(graph, u);
    while(graph_edge_iter_hasNext(graph, u, eiter)){ //for each adj di u : not black
      graph_edge_iter_next(graph, u, eiter, &edge, &weight);
      if(get_color(color, edge) != black){
        queue_enqueue(queue, edge);
        set_color(color, edge, grey);
        printf("   edge %s, weight %lf\n", (char*)edge, *weight);
        graph_weight += *weight;
      }
    }
    set_color(color, u, black);
  }

  return graph_weight;
}

int graph_is_directed(graph_o *graph) {
  ASSERT_PARAMETERS_NOT_NULL(graph);
  return graph->directed == DIRECTED ? 1 : 0;
}