/*
 *  File: list_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 05-05-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "unity_internals.h"
#include "list.h"

/* fare la free dei new_int! */


static int compare_int_ptr(void* elem1, void* elem2) {
  int int1 = *(int*) elem1;
  int int2 = *(int*) elem2;
  return int1 - int2;
}

static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

static void test_listNew(){
  node_o *list = list_new(new_int(55));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New list failed");
  free(list);
}

static void test_listFree(){
  node_o *list = list_new(new_int(3));
  list_free(list);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free list failed");
}

static void test_listAdd(){
  node_o *list = list_new(new_int(55));
  list_add(&list, new_int(2));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Add list failed");
  list_free(list);
}

static void test_listFreeAdd(){
  node_o *list = list_new(new_int(3));
  list_add(&list, new_int(4));
  list_add(&list, new_int(5));
  list_free(list);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free list failed");
}

static void test_listGetAtFirst(){
  node_o *list = list_new(new_int(1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  list_free(list);
}

static void test_listGetAt(){
  node_o *list = list_new(new_int(1));
  list_add(&list, new_int(2));
  list_add(&list, new_int(3));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 2));
  list_free(list);
}

static void test_listInsertAt(){
  node_o *list = list_new(new_int(1));
  list_add(&list, new_int(2));
  list_add(&list, new_int(4));
  list_add(&list, new_int(5));

  list_insert_at(&list, 2, new_int(3));

  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 3));
  list_free(list);
}

static void test_listInsertAtFirst(){
  node_o *list = list_new(new_int(3));
  list_add(&list, new_int(2));
  
  list_insert_at(&list, 0, new_int(1));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));
  
  list_free(list);
}

static void test_listInsertAtBottom(){
  node_o *list = list_new(new_int(3));
  list_add(&list, new_int(1));
  
  list_insert_at(&list, 1, new_int(2));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));
  
  list_free(list);
}

static void test_listInsertAtMiddle(){
  node_o *list = list_new(new_int(4));
  list_add(&list, new_int(3));
  list_add(&list, new_int(1));
  
  list_insert_at(&list, 1, new_int(2));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(list, 2));
  
  list_free(list);
}
/*
static void test_listRemoveAt(){
  node_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  
  list_remove_at(&list, 1);

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(&list, 1));
  
  list_free(&list);
}

static void test_listRemoveAtFirst(){
  node_o list = list_new(new_int(1));
  list_add(&list, new_int(2));
  
  list_remove_at(&list, 0);

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  
  list_free(&list);
}

static void test_listRemoveAtBottom(){
  node_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  
  list_remove_at(&list, 2);

  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(&list, 1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));

  list_free(&list);
}

static void test_listRemoveAtPos(){
  node_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  
  list_remove_at(&list, 1);

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(&list, 1));

  list_free(&list);
}

static void test_listRemoveAtAll(){
  node_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));

  list_remove_at(&list, 2);
  list_remove_at(&list, 1);
  list_remove_at(&list, 0);

  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Remove all failed");

  list_free(&list);
}

static void test_listIsEmpty(){
  node_o list = list_new(new_int(3));
  TEST_ASSERT_EQUAL_INT(0, list_is_empty(&list));
  list_remove_at(&list, 0);
  TEST_ASSERT_EQUAL_INT(1, list_is_empty(&list));
}

static void test_listSetAt(){
  node_o list = list_new(new_int(2));
  list_add(&list, new_int(3));
  list_set_at(&list, 0, new_int(1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  list_free(&list);
}
*/
static void test_listSize(){
  node_o *list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  TEST_ASSERT_EQUAL_INT(3, list_size(list));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(list, 0));
  list_free(list);
}

static void test_listContains(){
  node_o *list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  TEST_ASSERT_EQUAL_INT(1, list_contains(list, new_int(2), compare_int_ptr));
  TEST_ASSERT_EQUAL_INT(0, list_contains(list, new_int(5), compare_int_ptr));
  list_free(list);
}

static void test_listSearchFirst(){
  node_o *list = list_new(new_int(3));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_search(list, new_int(3), compare_int_ptr));
  list_free(list);
}

static void test_listSearchNotFound(){
  node_o *list = list_new(new_int(3));
  TEST_ASSERT(NULL == list_search(list, new_int(4), compare_int_ptr));
  list_free(list);
}

static void test_listSearch(){
  node_o *list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_search(list, new_int(2), compare_int_ptr));
  TEST_ASSERT(NULL == list_search(list, new_int(5), compare_int_ptr));
  list_free(list);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_listNew);
  RUN_TEST(test_listFree);
  RUN_TEST(test_listAdd);
  RUN_TEST(test_listFreeAdd);
  RUN_TEST(test_listGetAtFirst);
  RUN_TEST(test_listGetAt);
  RUN_TEST(test_listInsertAt);
  RUN_TEST(test_listInsertAtFirst);
  RUN_TEST(test_listInsertAtBottom);
  RUN_TEST(test_listInsertAtMiddle);
  //RUN_TEST(test_listRemoveAt);
  //RUN_TEST(test_listRemoveAtFirst);
  //RUN_TEST(test_listRemoveAtBottom);
  //RUN_TEST(test_listRemoveAtPos);
  //RUN_TEST(test_listRemoveAtAll);
  //RUN_TEST(test_listIsEmpty);
  //RUN_TEST(test_listSetAt);
  RUN_TEST(test_listSize);
  RUN_TEST(test_listContains);
  RUN_TEST(test_listSearchFirst);
  RUN_TEST(test_listSearchNotFound);
  RUN_TEST(test_listSearch);
  //RUN_TEST(test_listFreeAdd);
  return UNITY_END();
}

