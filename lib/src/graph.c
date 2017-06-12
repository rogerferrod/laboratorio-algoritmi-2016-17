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
#include <assert.h>
#include "lib.h"
#include "array.h"
#include "hash.h"
#include "list.h"
#include "graph.h"

#define EDGE_CAPACITY 5


/* Implementation of the opaque type */
struct _myGraph {
  hashtable_o *V;
  hash_fnc hash;
  KeyCompare compare;
  int directed;
  size_t size;
};

double graph_weight_all(graph_o *graph);
double graph_weight_BFS(graph_o *graph);
void set_color(hashtable_o *table, void *vertex, int* color);
int get_color(hashtable_o *table, void *vertex);


graph_o* graph_new(size_t capacity, hash_fnc hash, KeyCompare compare) {
  graph_o *graph = xmalloc(sizeof(graph_o));
  graph->hash = hash;
  graph->compare = compare;
  graph->V = hashtable_new(capacity, graph->hash, graph->compare);
  graph->directed = DIRECTED;
  graph->size = 0;
  return graph;
}

void graph_free(graph_o *graph){
  void* vertex;
  void *adj;
  graphIterator *viter = graph_vertex_iter_init(graph);
  while(graph_vertex_iter_hasNext(graph, viter)){
    graph_vertex_iter_next(graph, viter, &vertex, &adj);
    hashtable_free((hashtable_o*)adj);
  }
  hashtable_free(graph->V);
  free(graph);
  return;
}

size_t graph_order(graph_o *graph){
  assert(graph != NULL);
  return hashtable_size(graph->V);
}

size_t graph_size(graph_o *graph){
  assert(graph != NULL);
  return graph->size;
}

void graph_add(graph_o *graph, void *elem){
  assert(graph != NULL);
  assert(elem != NULL);
  hashtable_o *E = hashtable_new(EDGE_CAPACITY, graph->hash, graph->compare);
  hashtable_put(graph->V, elem, E);
  return;
}

void graph_connect(graph_o *graph, void *x, void *y, double *weight, int bitmask){
  assert(graph != NULL);
  if (!graph_contains_vertex(graph, y)) {
    fprintf(stderr, "Invalid parameters: destination vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  hashtable_o *E = (hashtable_o*)hashtable_find(graph->V, x);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: source vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  if(!hashtable_contains(E, y)){
    hashtable_put(E, y, weight);
    graph->size++;
  }

  if((bitmask & NO_DIRECTED) == NO_DIRECTED){
    graph->directed = NO_DIRECTED;
    graph_connect(graph, y, x, weight, DIRECTED);
  }

  return;
}

void* graph_contains_vertex(graph_o *graph, void *v){
  assert(graph != NULL);
  assert(v != NULL);
  void *find = hashtable_find(graph->V, v);
  return (find != NULL) ? v : NULL;
}

int graph_contains_edge(graph_o *graph, void *v1, void *v2){
  assert(graph != NULL);
  hashtable_o *E = hashtable_find(graph->V, v1);
  return (E != NULL && hashtable_size(E) > 0) ? hashtable_find(E, v2) != NULL : 0;
}

size_t graph_vertex_degree(graph_o *graph, void *v) {
  assert(graph != NULL);
  hashtable_o *E = hashtable_find(graph->V, v);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  return hashtable_size(E);
}

hash_fnc graph_get_hash_fnc(graph_o *graph) {
  assert(graph != NULL);
  return graph->hash;
}

KeyCompare graph_get_key_compare(graph_o *graph) {
  assert(graph != NULL);
  return graph->compare;
}

graphIterator *graph_vertex_iter_init(graph_o *graph) {
  assert(graph != NULL);
  return (graphIterator*)hashtable_iter_init(graph->V);
}

int graph_vertex_iter_hasNext(graph_o *graph, graphIterator *iter) {
  assert(graph != NULL);
  return hashtable_iter_hasNext(graph->V, iter);
}

void graph_vertex_iter_next(graph_o *graph, graphIterator *iter, void **elem, void **adj) {
  assert(graph != NULL);
  hashtable_iter_next(graph->V, iter, elem, adj);
  return;
}

graphIterator *graph_edge_iter_init(graph_o *graph, void *elem){
  assert(graph != NULL);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  return (graphIterator*)hashtable_iter_init(E);
}

int graph_edge_iter_hasNext(graph_o *graph, void *elem, graphIterator *iter){
  assert(graph != NULL);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  return hashtable_iter_hasNext(E, iter);
}

void graph_edge_iter_next(graph_o *graph, void *elem, graphIterator *iter, void **adj_elem, double **weight){
  assert(graph != NULL);
  hashtable_o *E = hashtable_find(graph->V, elem);
  if(E == NULL){
    fprintf(stderr, "Invalid parameters: vertex not found\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  hashtable_iter_next(E, iter, adj_elem, (void**)weight);
  return;
}

double graph_weight(graph_o *graph) {
  assert(graph != NULL);
  if (graph->directed == DIRECTED) {
    return graph_weight_all(graph);
  }
  return graph_weight_BFS(graph);
}

int graph_is_directed(graph_o *graph) {
  assert(graph != NULL);
  return graph->directed == DIRECTED;
}

/** For a directed graph. Must consider all edges. */
double graph_weight_all(graph_o *graph) {
  assert(graph != NULL);
  double graph_weight = 0.0;
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
      graph_weight += *weight;
    }
    free(e_iter);
  }
  free(v_iter);

  return graph_weight;
}

double graph_weight_BFS(graph_o *graph) {
  assert(graph != NULL);
  double graph_weight = 0.0;

  if(graph_order(graph) == 0) {
    return 0.0;
  }

  // color [V:color]
  enum status{black = 0, grey, white};
  int* colors[3];
  colors[black] = (int*)xmalloc(sizeof(int));
  colors[grey] = (int*)xmalloc(sizeof(int));
  colors[white] = (int*)xmalloc(sizeof(int));
  *colors[black] = black;
  *colors[grey] = grey;
  *colors[white] = white;

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
    set_color(color, vertex, colors[white]);
  }

  viter = graph_vertex_iter_init(graph);
  graph_vertex_iter_next(graph, viter, &vertex, &adj); //il primo elemento

  set_color(color, vertex, colors[grey]); //la visita parte da qua
  queue_enqueue(queue, vertex);

  while(!queue_is_empty(queue)){
    void *u = queue_dequeue(queue);

    eiter = graph_edge_iter_init(graph, u);
    while(graph_edge_iter_hasNext(graph, u, eiter)){ //for each adj di u : not black
      graph_edge_iter_next(graph, u, eiter, &edge, &weight);
      if(get_color(color, edge) != black){
        queue_enqueue(queue, edge);
        set_color(color, edge, colors[grey]);
        graph_weight += *weight;
      }
    }
    set_color(color, u, colors[black]);
  }

  free(colors[black]);
  free(colors[grey]);
  free(colors[white]);

  return graph_weight;
}

void set_color(hashtable_o *table, void *vertex, int* color){
  hashtable_put(table, vertex, color);
  return;
}

int get_color(hashtable_o *table, void *vertex){
  return *(int*)hashtable_find(table, vertex);
}
