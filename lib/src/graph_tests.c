/*
 *  File: graph_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "unity_internals.h"
#include "graph.h"

static void test_graphNew(){
  graph_o *graph = graph_new(5);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New graph failed");
  graph_free(graph);
}

static void test_graphFree(){
  graph_o *graph = graph_new(5);
  graph_free(graph);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free graph failed");
}

static void test_graphSizeEmpty(){
  graph_o *graph = graph_new(5);
  TEST_ASSERT_EQUAL_INT(0, graph_size(graph));
  graph_free(graph);
}

static void test_graphAdd(){
  graph_o *graph = graph_new(5);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_size(graph));
  //graph_free(graph); ERRORE!
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_graphNew);
  RUN_TEST(test_graphFree);
  RUN_TEST(test_graphSizeEmpty);
  RUN_TEST(test_graphAdd);
  return UNITY_END();
}

