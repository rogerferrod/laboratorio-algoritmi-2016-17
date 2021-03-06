/*
 *  File: graph_tests.c
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

static int compare_str(void *x, void *y){
  return strcmp(x, y);
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

static void test_graphNew(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New graph failed");
  graph_free(graph);
}

static void test_graphFree(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_free(graph);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free graph failed");
}

static void test_graphOrderEmpty(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  TEST_ASSERT_EQUAL_INT(0, graph_order(graph));
  graph_free(graph);
}

static void test_graphOrder(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  TEST_ASSERT_EQUAL_INT(3, graph_order(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphSizeEmpty(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  TEST_ASSERT_EQUAL_INT(0, graph_size(graph));
  graph_free(graph);
}

static void test_graphSizeNoLinks(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  TEST_ASSERT_EQUAL_INT(0, graph_size(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphSizeOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  graph_connect(graph, "A", "C", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT(2, graph_size(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphSizeNotOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  graph_connect(graph, "A", "C", new_double(0.0), NO_DIRECTED);
  TEST_ASSERT_EQUAL_INT(2, graph_size(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphAdd(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_order(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphAddDuplicate(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_order(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphConnectSimpleOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Link graph failed");

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphConnectSimpleNoOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Link graph failed");

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphContainsVertex(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_contains_vertex(graph, "A"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphContainsEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphNotContainsEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT(0, graph_contains_edge(graph, "A", "A"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphMultipleEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  graph_connect(graph, "A", "C", new_double(0.0), DIRECTED);
  graph_connect(graph, "A", "D", new_double(0.0), DIRECTED);
  graph_connect(graph, "B", "D", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "C"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "D"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "B", "D"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphConnectNoOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "B", "A"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphVertexDegreeEmpty() {
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(0, graph_vertex_degree(graph, "A"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphVertexDegreeOriented() {
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  graph_connect(graph, "A", "C", new_double(0.0), DIRECTED);
  graph_connect(graph, "A", "D", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT(3, graph_vertex_degree(graph, "A"));
  TEST_ASSERT_EQUAL_INT(0, graph_vertex_degree(graph, "B"));
  TEST_ASSERT_EQUAL_INT(0, graph_vertex_degree(graph, "C"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphVertexDegreeNotOriented() {
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  graph_connect(graph, "A", "C", new_double(0.0), NO_DIRECTED);
  graph_connect(graph, "A", "D", new_double(0.0), NO_DIRECTED);
  TEST_ASSERT_EQUAL_INT(3, graph_vertex_degree(graph, "A"));
  TEST_ASSERT_EQUAL_INT(1, graph_vertex_degree(graph, "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_vertex_degree(graph, "C"));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphVertexIteratorInit(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  graphIterator *vertex_iter = graph_vertex_iter_init(graph);

  TEST_ASSERT(NULL != *vertex_iter);

  free(vertex_iter);
  free_fixture(graph);
  graph_free(graph);
}

static void test_graphVertexIterator(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");

  graphIterator *vertex_iter = graph_vertex_iter_init(graph);
  size_t count = 0;

  void *elem = NULL;
  void *adj = NULL;
  while(graph_vertex_iter_hasNext(graph, vertex_iter)){
    graph_vertex_iter_next(graph, vertex_iter, &elem, &adj);
    count++;
  }

  TEST_ASSERT_EQUAL_INT(graph_order(graph), count);

  free(vertex_iter);
  free_fixture(graph);
  graph_free(graph);
}

static void test_graphEdgeIteratorInit(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  graph_connect(graph, "A", "C", new_double(0.0), NO_DIRECTED);
  graph_connect(graph, "A", "D", new_double(0.0), NO_DIRECTED);
  graphIterator *edge_iter = graph_edge_iter_init(graph, "A");

  TEST_ASSERT(NULL != *edge_iter);

  free(edge_iter);
  free_fixture(graph);
  graph_free(graph);
}

static void test_graphEdgeIterator(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(2.9), NO_DIRECTED);
  graph_connect(graph, "A", "C", new_double(5.3), NO_DIRECTED);
  graph_connect(graph, "A", "D", new_double(1.6), NO_DIRECTED);
  graphIterator *edge_iter = graph_edge_iter_init(graph, "A");
  void *adj = NULL;
  double *weight;
  size_t count = 0;

  while(graph_edge_iter_hasNext(graph, "A", edge_iter)){
    graph_edge_iter_next(graph, "A", edge_iter, &adj, &weight);
    count++;
  }

  TEST_ASSERT_EQUAL_INT(3, count);

  free(edge_iter);
  free_fixture(graph);
  graph_free(graph);
}

static void test_graphEdgeIteratorEmpty(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graphIterator *edge_iter = graph_edge_iter_init(graph, "A");
  void *adj = NULL;
  double *weight;
  size_t count = 0;
  while(graph_edge_iter_hasNext(graph, "A", edge_iter)){
    graph_edge_iter_next(graph, "A", edge_iter, &adj, &weight);
    count++;
  }

  TEST_ASSERT_EQUAL_INT(0, count);

  free(edge_iter);
  free_fixture(graph);
  graph_free(graph);
}

static void test_graphVertexHashExpand(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_add(graph, "F");

  TEST_ASSERT_EQUAL_INT(6, graph_order(graph));
  TEST_ASSERT_EQUAL_INT(0, graph_size(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphEdgeHashExpand(){
  graph_o *graph = graph_new(10, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_add(graph, "F");
  graph_connect(graph, "A", "B", new_double(2.9), DIRECTED);
  graph_connect(graph, "A", "C", new_double(5.3), DIRECTED);
  graph_connect(graph, "A", "D", new_double(1.6), DIRECTED);
  graph_connect(graph, "A", "E", new_double(1.6), DIRECTED);
  graph_connect(graph, "A", "F", new_double(1.6), DIRECTED);

  TEST_ASSERT_EQUAL_INT(6, graph_order(graph));
  TEST_ASSERT_EQUAL_INT(5, graph_size(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphWeightNotDirected(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
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

  TEST_ASSERT_EQUAL(96.0, graph_weight(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphWeightDirected(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_add(graph, "F");
  graph_add(graph, "G");
  graph_connect(graph, "A", "B", new_double(15), DIRECTED);
  graph_connect(graph, "A", "D", new_double(7), DIRECTED);
  graph_connect(graph, "A", "F", new_double(1), DIRECTED);

  graph_connect(graph, "B", "C", new_double(20), DIRECTED);
  graph_connect(graph, "B", "D", new_double(12), DIRECTED);

  graph_connect(graph, "C", "E", new_double(6), DIRECTED);
  graph_connect(graph, "C", "G", new_double(3), DIRECTED);

  graph_connect(graph, "D", "E", new_double(11),DIRECTED);
  graph_connect(graph, "D", "F", new_double(7), DIRECTED);

  graph_connect(graph, "E", "G", new_double(4), DIRECTED);

  graph_connect(graph, "F", "G", new_double(10), DIRECTED);
  graph_connect(graph, "G", "F", new_double(12), DIRECTED);

  TEST_ASSERT_EQUAL(108.0, graph_weight(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphIsDirectedTrue(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), DIRECTED);
  TEST_ASSERT_EQUAL_INT(1, graph_is_directed(graph));

  free_fixture(graph);
  graph_free(graph);
}

static void test_graphIsDirectedFalse(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_DIRECTED);
  TEST_ASSERT_EQUAL_INT(0, graph_is_directed(graph));

  free_fixture(graph);
  graph_free(graph);
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_graphNew);
  RUN_TEST(test_graphFree);
  RUN_TEST(test_graphOrderEmpty);
  RUN_TEST(test_graphOrder);
  RUN_TEST(test_graphSizeEmpty);
  RUN_TEST(test_graphSizeNoLinks);
  RUN_TEST(test_graphSizeOriented);
  RUN_TEST(test_graphSizeNotOriented);
  RUN_TEST(test_graphAdd);
  RUN_TEST(test_graphAddDuplicate);
  RUN_TEST(test_graphConnectSimpleOriented);
  RUN_TEST(test_graphConnectSimpleNoOriented);
  RUN_TEST(test_graphContainsVertex);
  RUN_TEST(test_graphContainsEdge);
  RUN_TEST(test_graphNotContainsEdge);
  RUN_TEST(test_graphMultipleEdge);
  RUN_TEST(test_graphConnectNoOriented);
  RUN_TEST(test_graphVertexDegreeEmpty);
  RUN_TEST(test_graphVertexDegreeOriented);
  RUN_TEST(test_graphVertexDegreeNotOriented);
  RUN_TEST(test_graphVertexIteratorInit);
  RUN_TEST(test_graphVertexIterator);
  RUN_TEST(test_graphEdgeIteratorInit);
  RUN_TEST(test_graphEdgeIterator);
  RUN_TEST(test_graphEdgeIteratorEmpty);
  RUN_TEST(test_graphVertexHashExpand);
  RUN_TEST(test_graphEdgeHashExpand);
  RUN_TEST(test_graphWeightNotDirected);
  RUN_TEST(test_graphWeightDirected);
  RUN_TEST(test_graphIsDirectedTrue);
  RUN_TEST(test_graphIsDirectedFalse);
  return UNITY_END();
}


