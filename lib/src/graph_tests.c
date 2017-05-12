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

static int compare_str(void *x, void *y){
  return strcmp(x, y);
}

static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

static size_t djb2a(char* str) {
  size_t hash = 5381;
  int c;
  while(c = *str++){
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

static void test_graphSizeEmpty(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  TEST_ASSERT_EQUAL_INT(0, graph_size(graph));
  graph_free(graph);
}

static void test_graphAdd(){
  graph_o *graph = graph_new(5, djb2a, compare_str);
  graph_add(graph, "A");
  TEST_ASSERT_EQUAL_INT(1, graph_size(graph));
  graph_free(graph);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_graphNew);
  RUN_TEST(test_graphFree);
  RUN_TEST(test_graphSizeEmpty);
  RUN_TEST(test_graphAdd);
  return UNITY_END();
}


