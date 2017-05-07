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
  list_o list = list_new(new_int(55));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New list failed");
  free(list);
}

static void test_listAdd(){
  list_o list = list_new(new_int(55));
  list_add(&list, new_int(2));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Add list failed");
  list_free(&list);
}

static void test_listGetAtFirst(){
  list_o list = list_new(new_int(1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  list_free(&list);
}

static void test_listGetAt(){
  list_o list = list_new(new_int(1));
  list_add(&list, new_int(2));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(&list, 0));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 1));
  list_free(&list);
}

static void test_listInsertAt(){
  list_o list = list_new(new_int(1));
  list_add(&list, new_int(2));
  list_add(&list, new_int(4));
  list_add(&list, new_int(5));

  list_insert_at(&list, 2, new_int(3));

  TEST_ASSERT_EQUAL_INT(4, *(int*)list_get_at(&list, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(&list, 2));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(&list, 3));
  list_free(&list);
}

static void test_listInsertAtFirst(){
  list_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  
  list_insert_at(&list, 0, new_int(1));

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(&list, 1));
  
  list_free(&list);
}

static void test_listRemoveAt(){
  list_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  
  list_remove_at(&list, 1);

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  TEST_ASSERT_EQUAL_INT(3, *(int*)list_get_at(&list, 1));
  
  list_free(&list);
}

static void test_listRemoveAtFirst(){
  list_o list = list_new(new_int(1));
  list_add(&list, new_int(2));
  
  list_remove_at(&list, 0);

  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  
  list_free(&list);
}

static void test_listRemoveAtBottom(){
  list_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  
  list_remove_at(&list, 2);

  TEST_ASSERT_EQUAL_INT(2, *(int*)list_get_at(&list, 1));
  
  list_free(&list);
}

static void test_listRemoveAtAll(){
  list_o list = list_new(new_int(1));
  
  list_remove_at(&list, 0);
  TEST_ASSERT_EQUAL_INT(1, list_get_at(&list, 0) == NULL);
  /* non ci va la free! e' un problema? */
}

static void test_listIsEmpty(){
  list_o list = list_new(new_int(3));
  TEST_ASSERT_EQUAL_INT(0, list_is_empty(&list));
  list_remove_at(&list, 0);
  TEST_ASSERT_EQUAL_INT(1, list_is_empty(&list));
}

static void test_listSetAt(){
  list_o list = list_new(new_int(2));
  list_add(&list, new_int(3));
  list_set_at(&list, 0, new_int(1));
  TEST_ASSERT_EQUAL_INT(1, *(int*)list_get_at(&list, 0));
  list_free(&list);
}

static void test_listSize(){
  list_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  TEST_ASSERT_EQUAL_INT(3, list_size(&list));
  list_free(&list);
}

static void test_listContains(){
  list_o list = list_new(new_int(3));
  list_add(&list, new_int(2));
  list_add(&list, new_int(1));
  TEST_ASSERT_EQUAL_INT(1, list_contains(&list, new_int(2), compare_int_ptr));
  TEST_ASSERT_EQUAL_INT(0, list_contains(&list, new_int(5), compare_int_ptr));
  list_free(&list);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_listNew);
  RUN_TEST(test_listAdd);
  RUN_TEST(test_listGetAtFirst);
  RUN_TEST(test_listGetAt);
  RUN_TEST(test_listInsertAt);
  RUN_TEST(test_listInsertAtFirst);
  RUN_TEST(test_listRemoveAt);
  RUN_TEST(test_listRemoveAtFirst);
  RUN_TEST(test_listRemoveAtBottom);
  RUN_TEST(test_listRemoveAtAll);
  RUN_TEST(test_listIsEmpty);
  RUN_TEST(test_listSetAt);
  RUN_TEST(test_listSize);
  RUN_TEST(test_listContains);
  return UNITY_END();
}

