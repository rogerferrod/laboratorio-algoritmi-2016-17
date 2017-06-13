/*
 *  File: kruskal_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "unity.h"
#include "graph.h"
#include "kruskal.h"

static int compare_str(void *x, void *y){
  return strcmp(x, y);
}

static size_t hashJava(void* str) {
  char *val = (char*)str;
  size_t hash = 0, offset = 0;
  for(size_t i = 0; i < strlen(str); ++i){
    hash = ((hash << 5) - hash) + val[offset++];  /* hash*31 + val[offset] */
  }
  return hash;
}

static double* new_double(double value) {
  double* elem = (double*) xmalloc(sizeof(double));
  *elem = value;
  return elem;
}

static void free_fixture(graph_o *graph) {
  if (!graph_is_directed(graph)){
    return; 
  }

  graphIterator *vIter = graph_vertex_iter_init(graph);
  void *k1 = NULL, *v1 = NULL;
  while(graph_vertex_iter_hasNext(graph, vIter)) {
    graph_vertex_iter_next(graph, vIter, &k1, &v1);
    graphIterator *eIter = graph_edge_iter_init(graph, k1);
    void *v2;
    double *w;
    while(graph_edge_iter_hasNext(graph, k1, eIter)) {
      graph_edge_iter_next(graph, k1, eIter, &v2, &w);
      free(w);
    }
    free(eIter);
  }
  free(vIter);
}

static void test_kruskal_emptyGraph() {
  graph_o *graph = graph_new(1, hashJava, compare_str);

  graph_o *min = kruskal(graph);
  TEST_ASSERT_NULL(min);

  graph_free(graph);
}

static void test_kruskal_noEdges() {
  graph_o *graph = graph_new(1, hashJava, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");

  graph_o *min = kruskal(graph);
  TEST_ASSERT_EQUAL_PTR(graph, min);

  free_fixture(graph);
  graph_free(graph);
}

static void test_kruskal_verySimpleNotDirected() {
  graph_o *graph = graph_new(1, hashJava, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(4), NO_DIRECTED);

  graph_o *min = kruskal(graph);
  TEST_ASSERT_EQUAL_INT(2, (int)graph_order(min));
  
  free_fixture(min);
  graph_free(min);
  free_fixture(graph);
  graph_free(graph);
}

static void test_kruskalIsDirected() {
  graph_o *graph = graph_new(1, hashJava, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_double(4), NO_DIRECTED);
  graph_connect(graph, "B", "C", new_double(4), NO_DIRECTED);
  graph_connect(graph, "A", "C", new_double(4), NO_DIRECTED);

  graph_o *min = kruskal(graph);
  TEST_ASSERT_EQUAL_INT(0, graph_is_directed(min));
  
  free_fixture(min);
  graph_free(min);
  free_fixture(graph);
  graph_free(graph);
}

static void test_kruskal_simpleNotDirected() {
  graph_o *graph = graph_new(1, hashJava, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_double(4), NO_DIRECTED);
  graph_connect(graph, "A", "C", new_double(3), NO_DIRECTED);
  graph_connect(graph, "B", "C", new_double(2), NO_DIRECTED);

  graph_o *min = kruskal(graph);
  TEST_ASSERT_EQUAL_INT(3, (int)graph_order(min));
  
  free_fixture(min);
  graph_free(min);
  free_fixture(graph);
  graph_free(graph);
}

static void test_kruskal_weight(){
  graph_o *graph = graph_new(5, hashJava, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_add(graph, "F");
  graph_add(graph, "G");
  graph_connect(graph, "A", "B", new_double(15), NO_DIRECTED);
  graph_connect(graph, "A", "D", new_double(7), NO_DIRECTED);
  graph_connect(graph, "A", "F", new_double(1), NO_DIRECTED);

  graph_connect(graph, "B", "C", new_double(20), NO_DIRECTED);
  graph_connect(graph, "B", "D", new_double(12), NO_DIRECTED);

  graph_connect(graph, "C", "E", new_double(6), NO_DIRECTED);
  graph_connect(graph, "C", "G", new_double(3), NO_DIRECTED);

  graph_connect(graph, "D", "E", new_double(11), NO_DIRECTED);
  graph_connect(graph, "D", "F", new_double(7), NO_DIRECTED);

  graph_connect(graph, "E", "G", new_double(4), NO_DIRECTED);

  graph_connect(graph, "F", "G", new_double(10), NO_DIRECTED);


  graph_o *min = kruskal(graph);

  TEST_ASSERT_MESSAGE(37.0 == graph_weight(min), "37.0 expected");

  free_fixture(min);
  graph_free(min);
  free_fixture(graph);
  graph_free(graph);
}

static void test_kruskal_graph(){
  graph_o *graph = graph_new(5, hashJava, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_add(graph, "F");
  graph_add(graph, "G");
  graph_connect(graph, "A", "B", new_double(15), NO_DIRECTED);
  graph_connect(graph, "A", "D", new_double(7), NO_DIRECTED);
  graph_connect(graph, "A", "F", new_double(1), NO_DIRECTED);

  graph_connect(graph, "B", "C", new_double(20), NO_DIRECTED);
  graph_connect(graph, "B", "D", new_double(12), NO_DIRECTED);

  graph_connect(graph, "C", "E", new_double(6), NO_DIRECTED);
  graph_connect(graph, "C", "G", new_double(3), NO_DIRECTED);

  graph_connect(graph, "D", "E", new_double(11), NO_DIRECTED);
  graph_connect(graph, "D", "F", new_double(7), NO_DIRECTED);

  graph_connect(graph, "E", "G", new_double(4), NO_DIRECTED);

  graph_connect(graph, "F", "G", new_double(10), NO_DIRECTED);


  graph_o *min = kruskal(graph);

  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(min, "A", "F"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(min, "F", "G"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(min, "G", "E"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(min, "G", "C"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(min, "B", "D"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(min, "D", "F"));


  free_fixture(min);
  graph_free(min);
  free_fixture(graph);
  graph_free(graph);
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_kruskal_emptyGraph);
  RUN_TEST(test_kruskal_noEdges);
  RUN_TEST(test_kruskal_verySimpleNotDirected);
  RUN_TEST(test_kruskalIsDirected);
  RUN_TEST(test_kruskal_simpleNotDirected);
  RUN_TEST(test_kruskal_weight);
  RUN_TEST(test_kruskal_graph);
  return UNITY_END();
}
