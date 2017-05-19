/*
 *  File: graph_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "hash.h"
#include "graph.h"

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
  graph_free(graph);
}

static void test_graphSizeOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_double(0.0), ORIENTED);
  graph_connect(graph, "A", "C", new_double(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(2, graph_size(graph));
  graph_free(graph);
}

static void test_graphSizeNotOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_double(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_double(0.0), NO_ORIENTED);
  TEST_ASSERT_EQUAL_INT(4, graph_size(graph));
  graph_free(graph);
}

static void test_graphAdd(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_order(graph));
  graph_free(graph);
}

static void test_graphConnectSimpleOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Link graph failed");
  graph_free(graph);
}

static void test_graphConnectSimpleNoOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_ORIENTED);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Link graph failed");
  graph_free(graph);
}

static void test_graphContainsVertex(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_contains_vertex(graph, "A"));
  graph_free(graph);
}

static void test_graphContainsEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  graph_free(graph);
}

static void test_graphNotContainsEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(0, graph_contains_edge(graph, "A", "A"));
  graph_free(graph);
}

static void test_graphMultipleEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_add(graph, "E");
  graph_connect(graph, "A", "B", new_double(0.0), ORIENTED);
  graph_connect(graph, "A", "C", new_double(0.0), ORIENTED);
  graph_connect(graph, "A", "D", new_double(0.0), ORIENTED);
  graph_connect(graph, "B", "D", new_double(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "C"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "D"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "B", "D"));
  graph_free(graph);
}

static void test_graphConnectNoOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_ORIENTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "B", "A"));
  graph_free(graph);
}

static void test_graphVertexDegreeEmpty() {
  //size_t graph_vertex_degree(graph_o *graph, void *v) {
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(0, graph_vertex_degree(graph, "A"));
  graph_free(graph);
}

static void test_graphVertexDegreeOriented() {
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(0.0), ORIENTED);
  graph_connect(graph, "A", "C", new_double(0.0), ORIENTED);
  graph_connect(graph, "A", "D", new_double(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(3, graph_vertex_degree(graph, "A"));
  TEST_ASSERT_EQUAL_INT(0, graph_vertex_degree(graph, "B"));
  TEST_ASSERT_EQUAL_INT(0, graph_vertex_degree(graph, "C"));
  graph_free(graph);
}

static void test_graphVertexDegreeNotOriented() {
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_double(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "D", new_double(0.0), NO_ORIENTED);
  TEST_ASSERT_EQUAL_INT(3, graph_vertex_degree(graph, "A"));
  TEST_ASSERT_EQUAL_INT(1, graph_vertex_degree(graph, "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_vertex_degree(graph, "C"));
  graph_free(graph);
}

static void test_graphVertexIteratorInit(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_double(0.0), NO_ORIENTED); 
  graphIterator *vertex_iter = graph_vertex_iter_init(graph);

  TEST_ASSERT(NULL != *vertex_iter);

  graph_free(graph);
  free(vertex_iter);
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
  
  TEST_ASSERT(NULL == *vertex_iter);
  TEST_ASSERT_EQUAL_INT(graph_order(graph), count);

  graph_free(graph);
  free(vertex_iter);
}

static void test_graphEdgeIteratorInit(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_double(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "D", new_double(0.0), NO_ORIENTED);
  graphIterator *edge_iter = graph_edge_iter_init(graph, "A");

  TEST_ASSERT(NULL != *edge_iter);

  graph_free(graph);
  free(edge_iter);
}

static void test_graphEdgeIterator(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_double(2.9), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_double(5.3), NO_ORIENTED);
  graph_connect(graph, "A", "D", new_double(1.6), NO_ORIENTED);
  graphIterator *edge_iter = graph_edge_iter_init(graph, "A");
  void *adj = NULL;
  double *weight;
  size_t count = 0;

  //prova l- hasNext su B o qualcos altro di non inizializzato
  while(graph_edge_iter_hasNext(graph, "A", edge_iter)){
    graph_edge_iter_next(graph, "A", edge_iter, &adj, &weight);
    count++;
  }

  TEST_ASSERT(NULL == *edge_iter);
  TEST_ASSERT_EQUAL_INT(3, count);

  graph_free(graph);
  free(edge_iter);
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
  return UNITY_END();
}


