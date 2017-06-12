/*
 *  File: list_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */


#include <stdlib.h>
#include "lib.h"
#include "unity.h"
#include "list.h"

/* fare la free dei new_int! */


static int compare_int_ptr(void* elem1, void* elem2) {
  int int1 = *(int*) elem1;
  int int2 = *(int*) elem2;
  return int1 - int2;
}

static int* new_int(int value) {
  int* elem = (int*) xmalloc(sizeof(int));
  *elem = value;
  return elem;
}
static void free_fixture(list_o* list) {
  for (size_t i=0; i<list_size(list); ++i) {
    free(list_get_at(list, i));
  }
}

static void test_listNew() {
  list_o* list = list_new();
  TEST_ASSERT_NOT_NULL(list);

  free(list);
}

static void test_listFree() {
  list_o* list = list_new();
  list_free(list);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "List free failed\n");
}

static void test_listSizeEmpty(){
  list_o *list = list_new();
  TEST_ASSERT_EQUAL_INT(0, list_size(list));
  list_free(list);
}

static void test_listIsEmpty(){
  list_o *list = list_new();
  TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));
  list_free(list);
}

static void test_listAddEmpty() {
  list_o* list = list_new();
  list_add(list, new_int(5));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "List add empty failed\n");

  free_fixture(list);
  list_free(list);
}

static void test_listAddMore() {
  list_o* list = list_new();
  list_add(list, new_int(5));
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));
  list_add(list, new_int(0));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "List add more failed\n");

  free_fixture(list);
  list_free(list);
}

static void test_listGetAtFirst(){
  list_o *list = list_new();
  list_add(list, new_int(1));
  list_add(list, new_int(2));
  list_add(list, new_int(3));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 0));

  free_fixture(list);
  list_free(list);
}

static void test_listGetAtLast(){
  list_o *list = list_new();
  list_add(list, new_int(1));
  list_add(list, new_int(2));
  list_add(list, new_int(3));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, list_size(list)-1));

  free_fixture(list);
  list_free(list);
}

static void test_listGetAt(){
  list_o *list = list_new();
  list_add(list, new_int(1));
  list_add(list, new_int(2));
  list_add(list, new_int(3));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 2));

  free_fixture(list);
  list_free(list);
}

static void test_listInsertAt(){
  list_o *list = list_new();
  list_add(list, new_int(1));
  list_add(list, new_int(2));
  list_add(list, new_int(4));
  list_add(list, new_int(5));

  list_insert_at(list, 2, new_int(3));

  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 3));

  free_fixture(list);
  list_free(list);
}

static void test_listInsertAtFirst(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));

  list_insert_at(list, 0, new_int(1));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));
  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(list, 3));

  free_fixture(list);
  list_free(list);
}

static void test_listInsertAtBottom(){
  list_o *list = list_new();
  list_add(list, new_int(3));  //3
  list_add(list, new_int(2));  //2 - 3
  list_add(list, new_int(1));  //1 - 2 - 3

  list_insert_at(list, list_size(list)-1, new_int(5));  //1 - 2 - 5 - 3
  list_insert_at(list, list_size(list), new_int(4));    //1 - 2 - 5 - 3 - 4

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(5, *(int*)list_get_at(list, 2));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 3));
  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(list, 4));

  free_fixture(list);
  list_free(list);
}

static void test_listInsertAtMiddle(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(1));

  list_insert_at(list, 1, new_int(2));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));

  free_fixture(list);
  list_free(list);
}

static void test_listRemoveAt(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  list_remove_at(list, 1);

  TEST_ASSERT_EQUAL_INT(2, list_size(list));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 1));

  free_fixture(list);
  list_free(list);
}

static void test_listRemoveAtFirst(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  list_remove_at(list, 0);

  TEST_ASSERT_EQUAL_INT(2, list_size(list));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 1));

  free_fixture(list);
  list_free(list);
}

static void test_listRemoveAtBottom(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  list_remove_at(list, list_size(list)-1);

  TEST_ASSERT_EQUAL_INT(2, list_size(list));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));

  free_fixture(list);
  list_free(list);
}

static void test_listRemoveAtAllFromLast(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  list_remove_at(list, list_size(list)-1);
  list_remove_at(list, list_size(list)-1);
  list_remove_at(list, list_size(list)-1);

  TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));

  free_fixture(list);
  list_free(list);
}

static void test_listRemoveAtAllFromFirst(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  list_remove_at(list, 0);
  list_remove_at(list, 0);
  list_remove_at(list, 0);

  TEST_ASSERT_EQUAL_INT(1, list_is_empty(list));

  free_fixture(list);
  list_free(list);
}

static void test_listSetAtBegin(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  list_set_at(list, 0, new_int(4));
  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(list, 0));

  free_fixture(list);
  list_free(list);
}

static void test_listSetAtMiddle(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  list_set_at(list, 1, new_int(5));
  TEST_ASSERT_EQUAL_INT(5, *(int*)list_get_at(list, 1));

  free_fixture(list);
  list_free(list);
}

static void test_listSetAtEnd(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(list, list_size(list)-1));
  list_set_at(list, list_size(list)-1, new_int(5));
  TEST_ASSERT_EQUAL_INT(5, *(int*)list_get_at(list, list_size(list)-1));

  free_fixture(list);
  list_free(list);
}

static void test_listSize(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  TEST_ASSERT_EQUAL_INT(4, list_size(list));

  free_fixture(list);
  list_free(list);
}

static void test_listSizeAfterRemove(){
  list_o *list = list_new();
  list_add(list, new_int(4));
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));

  list_remove_at(list, 2);

  TEST_ASSERT_EQUAL_INT(3, list_size(list));

  free_fixture(list);
  list_free(list);
}

static void test_listContainsEmpty(){
  list_o *list = list_new();
  TEST_ASSERT_EQUAL_INT(0, list_contains(list, new_int(1), compare_int_ptr));
  list_free(list);
}

static void test_listContains(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));
  TEST_ASSERT_EQUAL_INT(1, list_contains(list, new_int(2), compare_int_ptr));
  TEST_ASSERT_EQUAL_INT(0, list_contains(list, new_int(5), compare_int_ptr));

  free_fixture(list);
  list_free(list);
}

static void test_listFindFirst(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_find(list, new_int(3), compare_int_ptr));

  free_fixture(list);
  list_free(list);
}

static void test_listFindEmpty(){
  list_o *list = list_new();
  TEST_ASSERT_NULL(list_find(list, new_int(3), compare_int_ptr));
  list_free(list);
}

static void test_listFindNull(){
  list_o *list = list_new();
  TEST_ASSERT_NULL(list_find(list, NULL, compare_int_ptr));
  list_free(list);
}

static void test_listFindNotFound(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));
  TEST_ASSERT_NULL(list_find(list, new_int(0), compare_int_ptr));

  free_fixture(list);
  list_free(list);
}

static void test_listFind(){
  list_o *list = list_new();
  list_add(list, new_int(3));
  list_add(list, new_int(2));
  list_add(list, new_int(1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_find(list, new_int(3), compare_int_ptr));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_find(list, new_int(2), compare_int_ptr));
  TEST_ASSERT_NULL(list_find(list, new_int(5), compare_int_ptr));

  free_fixture(list);
  list_free(list);
}

static void test_queueNew() {
  queue_o* queue = queue_new();
  TEST_ASSERT_NOT_NULL(queue);
  free(queue);
}

static void test_queueFree() {
  queue_o* queue = queue_new();
  queue_free(queue);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue free failed\n");
}

static void test_queueSizeEmpty(){
  queue_o* queue = queue_new();
  TEST_ASSERT_EQUAL_INT(0, queue_size(queue));
  queue_free(queue);
}

static void test_queueIsEmpty(){
  queue_o* queue = queue_new();
  TEST_ASSERT_EQUAL_INT(1, queue_is_empty(queue));
  queue_free(queue);
}

static void test_queueEnqueueEmpty(){
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue enqueue empty failed\n");

  queue_free(queue);
}

static void test_queueEnqueueMore(){
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue enqueue more failed\n");

  queue_free(queue);
}

static void test_queueDequeueSize(){
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_dequeue(queue);
  TEST_ASSERT_EQUAL_INT(2, queue_size(queue));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue dequeue failed\n");

  queue_free(queue);
}
static void test_queueDequeueAll(){
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_dequeue(queue);
  queue_dequeue(queue);
  queue_dequeue(queue);
  TEST_ASSERT_EQUAL_INT(0, queue_size(queue));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1,1, "Queue dequeue all failed\n");

  queue_free(queue);
}

static void test_queueSize(){
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  queue_dequeue(queue);
  queue_dequeue(queue);
  TEST_ASSERT_EQUAL_INT(1, queue_size(queue));

  queue_free(queue);
}

static void test_queueFrontEmpty() {
  queue_o* queue = queue_new();
  TEST_ASSERT_NULL(queue_front(queue));
  queue_free(queue);
}

static void test_queueFront() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  TEST_ASSERT_EQUAL_INT(5, *(int*)queue_front(queue));
  queue_free(queue);
}

static void test_queueBackEmpty() {
  queue_o* queue = queue_new();
  TEST_ASSERT_NULL(queue_back(queue));
  queue_free(queue);
}

static void test_queueBack() {
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  TEST_ASSERT_EQUAL_INT(3, *(int*)queue_back(queue));
  queue_free(queue);
}

static void test_queueDequeue(){
  queue_o* queue = queue_new();
  queue_enqueue(queue, new_int(5));
  queue_enqueue(queue, new_int(4));
  queue_enqueue(queue, new_int(3));
  TEST_ASSERT_EQUAL_INT(3, *(int*)queue_dequeue(queue));
  TEST_ASSERT_EQUAL_INT(4, *(int*)queue_dequeue(queue));
  TEST_ASSERT_EQUAL_INT(5, *(int*)queue_dequeue(queue));
  queue_free(queue);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_listNew);
  RUN_TEST(test_listFree);
  RUN_TEST(test_listSizeEmpty);
  RUN_TEST(test_listIsEmpty);
  RUN_TEST(test_listAddEmpty);
  RUN_TEST(test_listAddMore);
  RUN_TEST(test_listGetAtFirst);
  RUN_TEST(test_listGetAtLast);
  RUN_TEST(test_listGetAt);
  RUN_TEST(test_listInsertAt);
  RUN_TEST(test_listInsertAtFirst);
  RUN_TEST(test_listInsertAtBottom);
  RUN_TEST(test_listInsertAtMiddle);
  RUN_TEST(test_listRemoveAt);
  RUN_TEST(test_listRemoveAtFirst);
  RUN_TEST(test_listRemoveAtBottom);
  RUN_TEST(test_listRemoveAtAllFromLast);
  RUN_TEST(test_listRemoveAtAllFromFirst);
  RUN_TEST(test_listSetAtBegin);
  RUN_TEST(test_listSetAtMiddle);
  RUN_TEST(test_listSetAtEnd);
  RUN_TEST(test_listSize);
  RUN_TEST(test_listSizeAfterRemove);
  RUN_TEST(test_listContainsEmpty);
  RUN_TEST(test_listContains);
  RUN_TEST(test_listFindFirst);
  RUN_TEST(test_listFindEmpty);
  RUN_TEST(test_listFindNull);
  RUN_TEST(test_listFindNotFound);
  RUN_TEST(test_listFind);

  RUN_TEST(test_queueNew);
  RUN_TEST(test_queueFree);
  RUN_TEST(test_queueSizeEmpty);
  RUN_TEST(test_queueIsEmpty);
  RUN_TEST(test_queueEnqueueEmpty);
  RUN_TEST(test_queueEnqueueMore);
  RUN_TEST(test_queueDequeueAll);
  RUN_TEST(test_queueDequeueSize);
  RUN_TEST(test_queueSize);
  RUN_TEST(test_queueFrontEmpty);
  RUN_TEST(test_queueFront);
  RUN_TEST(test_queueBackEmpty);
  RUN_TEST(test_queueBack);
  RUN_TEST(test_queueDequeue);

  return UNITY_END();
}

