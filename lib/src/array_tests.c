/*
 *  File: array_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "unity_internals.h"
#include "array.h"


static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

static array_o* build_fixture() {
  array_o* array = array_new(5);

  array_insert(array, new_int(1));
  array_insert(array, new_int(10));
  array_insert(array, new_int(4));
  array_insert(array, new_int(7));

  return array;
}

static void free_fixture(array_o* array) {
  for(size_t i = 0; i<array_size(array); ++i) {
    free(array_at(array, i) );
  }

  array_free(array);
}

static void test_ordered_array_new_not_null() {
  array_o* array = array_new(10);
  TEST_ASSERT_NOT_NULL(array);

  array_free(array);
}

static void test_ordered_array_new_capacity_is_correct() {
  array_o* array = array_new(10);
  TEST_ASSERT_EQUAL_INT(10, array_capacity(array));

  array_free(array);
}

static void test_ordered_array_new_size_zero() {
  array_o* array = array_new(10);
  TEST_ASSERT_EQUAL_INT(0, array_size(array));

  array_free(array);
}

static void test_ordered_array_free() {
  array_o* array = array_new(10);
  array_free(array);

  TEST_ASSERT_EQUAL_INT(1, 1);
}

static void test_ordered_array_size() {
  array_o* array = build_fixture();
  TEST_ASSERT_EQUAL_INT(4, array_size(array));
  free_fixture(array);
}

static void test_ordered_array_empty() {
  array_o* array = array_new(10);
  TEST_ASSERT_EQUAL_INT(1, array_empty(array));
  array_free(array);
}

static void test_ordered_array_realloc() {
  array_o* array = build_fixture();
  size_t old_capacity = array_capacity(array);
  array_insert(array, new_int(10));
  array_insert(array, new_int(3));
  TEST_ASSERT_EQUAL_INT(1, array_capacity(array) > old_capacity);
  TEST_ASSERT_EQUAL_INT(1, array_capacity(array) >= array_size(array));

  free_fixture(array);
}

static void test_ordered_array_at() {
  array_o* array = build_fixture();
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0) );
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 1) );
  TEST_ASSERT_EQUAL_INT(4, *(int*)array_at(array, 2) );
  TEST_ASSERT_EQUAL_INT(7, *(int*)array_at(array, 3) );
  free_fixture(array);
}

static void test_ordered_array_insert_at_end() {
  array_o* array = build_fixture();

  array_insert(array, new_int(20));
  TEST_ASSERT_EQUAL_INT(5, array_size(array));
  TEST_ASSERT_EQUAL_INT(20, *(int*)array_at(array, 4));

  free_fixture(array);
}

static void test_ordered_array_delete(){
  array_o* array = build_fixture();
  
  array_delete(array,0);
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(3, array_size(array));

  free_fixture(array);
}

static void test_ordered_array_swap(){
  array_o* array = build_fixture();

  array_swap(array,0,1);
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 1));

  free_fixture(array);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_ordered_array_new_not_null);
  RUN_TEST(test_ordered_array_new_capacity_is_correct);
  RUN_TEST(test_ordered_array_new_size_zero);
  RUN_TEST(test_ordered_array_free);
  RUN_TEST(test_ordered_array_size);
  RUN_TEST(test_ordered_array_empty);
  RUN_TEST(test_ordered_array_realloc);
  RUN_TEST(test_ordered_array_at);
  RUN_TEST(test_ordered_array_insert_at_end);
  RUN_TEST(test_ordered_array_delete);
  RUN_TEST(test_ordered_array_swap);
  return UNITY_END();
}
