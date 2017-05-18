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
#include "unity_internals.h"
#include "graph.h"
#include "hash.h"

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

static float* new_float(float value) {
  float* elem = (float*) malloc(sizeof(float));
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
  graph_connect(graph, "A", "B", new_float(0.0), ORIENTED);
  graph_connect(graph, "A", "C", new_float(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(2, graph_size(graph));
  graph_free(graph);
}

static void test_graphSizeNonOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_connect(graph, "A", "B", new_float(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_float(0.0), NO_ORIENTED);
  TEST_ASSERT_EQUAL_INT(2, graph_size(graph));
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
  graph_connect(graph, "A", "B", new_float(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Link graph failed");
  graph_free(graph);
}

static void test_graphConnectSimpleNoOriented(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_float(0.0), NO_ORIENTED);
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
  graph_connect(graph, "A", "B", new_float(0.0), ORIENTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  graph_free(graph);
}

static void test_graphNotContainsEdge(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_float(0.0), ORIENTED);
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
  graph_connect(graph, "A", "B", new_float(0.0), ORIENTED);
  graph_connect(graph, "A", "C", new_float(0.0), ORIENTED);
  graph_connect(graph, "A", "D", new_float(0.0), ORIENTED);
  graph_connect(graph, "B", "D", new_float(0.0), ORIENTED);
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
  graph_connect(graph, "A", "B", new_float(0.0), NO_ORIENTED);
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "A", "B"));
  TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(graph, "B", "A"));
  graph_free(graph);
}

static void test_graphVertexIteratorInit(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_connect(graph, "A", "B", new_float(0.0), NO_ORIENTED); // prova senza 
  graphIterator *viter = (graphIterator*)malloc(sizeof(graphIterator));
  graph_vertex_iter_init(graph, viter);

  TEST_ASSERT(NULL != *viter);

  graph_free(graph);
  free(viter);
}

static void test_graphVertexIterator(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
 
  graphIterator *viter = (graphIterator*)malloc(sizeof(graphIterator));
  graph_vertex_iter_init(graph, viter);

  void *elem = (char*)malloc(10*sizeof(char)); /* nome vertice */
  void *adj = NULL; /* hashtable E */
  while(graph_vertex_iter_hasNext(graph, viter)){
    graph_vertex_iter_next(graph, viter, &elem, &adj);
    printf("elem %s \n", (char*)elem);
  }
  
  TEST_ASSERT(NULL == *viter);

  graph_free(graph);
  free(viter);
}

static void test_graphEdgeIteratorInit(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_float(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_float(0.0), NO_ORIENTED);
  graph_connect(graph, "A", "D", new_float(0.0), NO_ORIENTED);
  graphIterator *eiter = (graphIterator*)malloc(sizeof(graphIterator));
  graph_edge_iter_init(graph, "A", eiter);

  TEST_ASSERT(NULL != *eiter);

  graph_free(graph);
  free(eiter);
}

static void test_graphEdgeIterator(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  graph_add(graph, "B");
  graph_add(graph, "C");
  graph_add(graph, "D");
  graph_connect(graph, "A", "B", new_float(2.9), NO_ORIENTED);
  graph_connect(graph, "A", "C", new_float(5.3), NO_ORIENTED);
  graph_connect(graph, "A", "D", new_float(1.6), NO_ORIENTED);
  graphIterator *eiter = (graphIterator*)malloc(sizeof(graphIterator));
  graph_edge_iter_init(graph, "A", eiter);
  void *adj = (char*)malloc(10*sizeof(char));
  float *weight;

  //prova l- hasNext su B o qualcos altro di non initializzato
  while(graph_edge_iter_hasNext(graph, "A", eiter)){
    graph_edge_iter_next(graph, "A", eiter, &adj, &weight);
    printf("edge(%s-%f) \n", (char*)adj, *(float*)weight);
  }

  TEST_ASSERT(NULL == *eiter);

  graph_free(graph);
  free(eiter);
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
  RUN_TEST(test_graphSizeNonOriented);
  RUN_TEST(test_graphAdd);
  RUN_TEST(test_graphConnectSimpleOriented);
  RUN_TEST(test_graphConnectSimpleNoOriented);
  RUN_TEST(test_graphContainsVertex);
  RUN_TEST(test_graphContainsEdge);
  RUN_TEST(test_graphNotContainsEdge);
  RUN_TEST(test_graphMultipleEdge);
  RUN_TEST(test_graphConnectNoOriented);
  RUN_TEST(test_graphVertexIteratorInit);
  RUN_TEST(test_graphVertexIterator);
  RUN_TEST(test_graphEdgeIteratorInit);
  RUN_TEST(test_graphEdgeIterator);
  return UNITY_END();
}


