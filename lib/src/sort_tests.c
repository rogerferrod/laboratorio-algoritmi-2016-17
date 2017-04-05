#include "array.h"
#include "sort.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdlib.h>

int compare_int_ptr(void* elem1, void* elem2) {
  int int1 = *(int*) elem1;
  int int2 = *(int*) elem2;
  if(int1 == int2) {
    return 0;
  }

  if(int1 < int2) {
    return -1;
  }

  return 1;
}


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

static void test_sort_InsertionSort(){
  array_o* array = build_fixture();
  
  insertion_sort(array,compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(4, *(int*)array_at(array, 1));
  TEST_ASSERT_EQUAL_INT(7, *(int*)array_at(array, 2));
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 3));
  

  free_fixture(array);
}

static void test_sort_SelectionSort(){
  array_o* array = build_fixture();
  
  selection_sort(array,compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(4, *(int*)array_at(array, 1));
  TEST_ASSERT_EQUAL_INT(7, *(int*)array_at(array, 2));
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 3));
  

  free_fixture(array);
}

static void test_sort_QuickSort(){
  array_o* array = build_fixture();

  quick_sort(array, compare_int_ptr);
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(4, *(int*)array_at(array, 1));
  TEST_ASSERT_EQUAL_INT(7, *(int*)array_at(array, 2));
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 3));

  free_fixture(array);
}

static void test_sort_partition(){
  array_o* array = build_fixture();

//  array_partition(array, );
  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0));
  TEST_ASSERT_EQUAL_INT(4, *(int*)array_at(array, 1));
  TEST_ASSERT_EQUAL_INT(7, *(int*)array_at(array, 2));
  TEST_ASSERT_EQUAL_INT(10, *(int*)array_at(array, 3));

  free_fixture(array);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_sort_InsertionSort);
  RUN_TEST(test_sort_SelectionSort);
  RUN_TEST(test_sort_QuickSort);
  //RUN_TEST(test_sort_partition);
  return UNITY_END();
  
}
