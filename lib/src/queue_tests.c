/*
 *  File: queue_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "queue.h"


static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}
/*
static array_o* build_fixture() {
  array_o* array = array_new(5);

  array_insert(array, new_int(1));
  array_insert(array, new_int(10));
  array_insert(array, new_int(4));
  array_insert(array, new_int(7));

  return array;
  }*/

static void test_queue_new() {
  queue_o* queue = queue_new();
  TEST_ASSERT_NOT_NULL(queue);

  free(queue);
}

static void test_queue_free() {
  queue_o* queue = queue_new();
  queue_free(queue);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue free failed\n");
}

static void test_queue_enqueue_empty() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue enqueue empty failed\n");
  queue_free(queue);
}

static void test_queue_enqueue_more() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_enqueue(queue, new_int(2));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue enqueue empty failed\n");
  queue_free(queue);
}

static void test_queue_dequeue_single() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  int *elem = queue_dequeue(queue);
  TEST_ASSERT_EQUAL_INT(5,*elem);
  queue_free(queue);
}

static void test_queue_dequeue() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_enqueue(queue, new_int(2));
  queue_enqueue(queue, new_int(1)); //test da sistemare
  TEST_ASSERT_EQUAL_INT(1,*(int*)queue_dequeue(queue));
  TEST_ASSERT_EQUAL_INT(2,*(int*)queue_dequeue(queue));
  TEST_ASSERT_EQUAL_INT(3,*(int*)queue_dequeue(queue));
  TEST_ASSERT_EQUAL_INT(4,*(int*)queue_dequeue(queue));
  queue_free(queue);
}

static void test_queue_front() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_enqueue(queue, new_int(2));
  queue_enqueue(queue, new_int(1)); //test da sistemare
  TEST_ASSERT_EQUAL_INT(5,*(int*)queue_front(queue));
  queue_free(queue);
}

static void test_queue_back() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_enqueue(queue, new_int(2));
  queue_enqueue(queue, new_int(1)); //test da sistemare
  TEST_ASSERT_EQUAL_INT(1,*(int*)queue_back(queue));
  queue_free(queue);
}

static void test_queue_size() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  TEST_ASSERT_EQUAL_INT(2, queue_size(queue)); 
  queue_free(queue);
}

static void test_queue_is_empty() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  TEST_ASSERT_EQUAL_INT(0, queue_is_empty(queue)); //da dividere i test
  queue_dequeue(queue);
  TEST_ASSERT_EQUAL_INT(1, queue_is_empty(queue)); //da dividere i test
  queue_free(queue);
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_queue_new);
  RUN_TEST(test_queue_free);
  RUN_TEST(test_queue_enqueue_empty);
  RUN_TEST(test_queue_enqueue_more);
  RUN_TEST(test_queue_dequeue_single);
  RUN_TEST(test_queue_dequeue);
  RUN_TEST(test_queue_front);
  RUN_TEST(test_queue_back);
  RUN_TEST(test_queue_size);
  RUN_TEST(test_queue_is_empty);
  return UNITY_END();
}

