/*
 *  File: set_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 03-05-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "unity_internals.h"
#include "set.h"

/*
static int compare_int_ptr(void* elem1, void* elem2) {
  int int1 = *(int*) elem1;
  int int2 = *(int*) elem2;
  return int1 - int2;
}
*/
/*
static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}
*/
/*
static array_o* build_fixture() {
  array_o* array = array_new(10);

  array_insert(array, new_int(8));
  array_insert(array, new_int(10));
  array_insert(array, new_int(2));
  array_insert(array, new_int(9));
  array_insert(array, new_int(3));
  array_insert(array, new_int(7));
  array_insert(array, new_int(1));
  array_insert(array, new_int(8));
  array_insert(array, new_int(5));
  
  return array;
}
*/
/*
static void free_fixture(array_o* array) {
  for(size_t i = 0; i<array_size(array); ++i) {
    free(array_at(array, i));
  }

  array_free(array);
}
*/
static void test_sort_QuickSort(){
  array_o* array = build_fixture();

  quick_sort(array,compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(2, *(int*)array_at(array, 1));
  TEST_ASSERT_EQUAL_INT(3, *(int*)array_at(array, 2));
  TEST_ASSERT_EQUAL_INT(5, *(int*)array_at(array, 3));
  TEST_ASSERT_EQUAL_INT(7, *(int*)array_at(array, 4));
  TEST_ASSERT_EQUAL_INT(8, *(int*)array_at(array, 5));
  TEST_ASSERT_EQUAL_INT(8, *(int*)array_at(array, 6));
  TEST_ASSERT_EQUAL_INT(9, *(int*)array_at(array, 7));
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 8));
  
  free_fixture(array);  
}

static void test_set_

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_sort_InsertionSort);
  RUN_TEST(test_sort_SelectionSort);
  RUN_TEST(test_sort_QuickSort);
  RUN_TEST(test_empty_sort_InsertionSort);
  RUN_TEST(test_empty_sort_SelectionSort);
  RUN_TEST(test_empty_sort_QuickSort);
  return UNITY_END();
}
