/*
 *  File: kruskal_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "graph.h"
#include "kruskal.h"

static int compare_str(void *x, void *y){
  return strcmp(x, y);
}

/*
static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}
*/

static double* new_double(double value) {
  double* elem = (double*) malloc(sizeof(double));
  *elem = value;
  return elem;
}

/**
 * Hash function
 * @param str char* String to be hashed
 * @return hash
 */
static size_t djb2a(void* str) {
  size_t hash = 5381;
  int c;
  char* my_str = (char*)str;
  while((c = *my_str)==1){
    (*my_str)++;
    hash = ((hash << 5) + hash) ^ c; /* hash * 33 ^ c */
  }
  return hash;
}

static void test_kruskal(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_add(graph, "F");
  graph_add(graph, "G");
  graph_connect(graph, "A", "B", new_double(15), ORIENTED);
  graph_connect(graph, "A", "D", new_double(7), ORIENTED);
  graph_connect(graph, "A", "F", new_double(1), ORIENTED);

  graph_connect(graph, "B", "C", new_double(20), ORIENTED);
  graph_connect(graph, "B", "D", new_double(12), ORIENTED);

  graph_connect(graph, "C", "E", new_double(6), ORIENTED);
  graph_connect(graph, "C", "G", new_double(3), ORIENTED);

  graph_connect(graph, "D", "E", new_double(11), ORIENTED);
  graph_connect(graph, "D", "F", new_double(7), ORIENTED);

  graph_connect(graph, "E", "G", new_double(4), ORIENTED);

  graph_connect(graph, "F", "G", new_double(10), ORIENTED);

  graph_o *min = kruskal(graph);

  printf("min\n");
  printf("min order: %ld \n", (unsigned long)graph_order(min));
//  printf("min size: %ld\n", (unsigned long)graph_size(min));
/*
  graphIterator *iter = graph_vertex_iter_init(min);
  void *elem, *adj;
  int i=0;
  while (graph_vertex_iter_hasNext(min, iter)) {
    graph_vertex_iter_next(min, iter, &elem, &adj);
    printf("i: %ld\n", ++i);
  }
*/
  graph_free(min);
  graph_free(graph);
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_kruskal);
  return UNITY_END();
}
