/*
 *  File: set_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 05-05-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "unity_internals.h"
#include "set.h"

static int* new_int(int value) {
  int *ptr = malloc(sizeof(int));
  *ptr = value;
  return ptr;
}

static void test_makeSet() {
  int* ptr = new_int(1);
  
  set_o *set = make_set(ptr);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Make set failed");
  
  free(ptr);
  free_set(set);
}

static void test_makeSetNull() {
  set_o *set = make_set(NULL);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Make set failed");
  
  free_set(set);
}

static void test_findSet() {
  int* ptr = new_int(5);
  
  set_o *set = make_set(ptr);
  TEST_ASSERT(set == find_set(set));
  
  free(ptr);
  free_set(set);
}

static void test_unionSet() {
  int* ptr = new_int(2);
  int* ptr2 = new_int(5);
  
  set_o *set = make_set(ptr);
  set_o *set2 = make_set(ptr2);
  union_set(set, set2);
  TEST_ASSERT(find_set(set) == find_set(set2));
  
  free(ptr);
  free(ptr2);
  free_set(set);
  free_set(set2);
}

static void test_unionSetRank() {
  int* ptr1 = new_int(2);
  int* ptr2 = new_int(5);
  int* ptr3 = new_int(7);
  
  set_o *set1 = make_set(ptr1);
  set_o *set2 = make_set(ptr2);
  set_o *set3 = make_set(ptr3);
  union_set(set1, set2); /* rank 0 + rank 0 = rank 1 */
  union_set(set1, set3); /* rank 1 + rank 0 = rank 1 */
  TEST_ASSERT(find_set(set1) == find_set(set2) && find_set(set2) == find_set(set3));
  
  free(ptr1);
  free(ptr2);
  free(ptr3);
  free_set(set1);
  free_set(set2);
  free_set(set3);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_makeSet);
  RUN_TEST(test_makeSetNull);
  RUN_TEST(test_findSet);
  RUN_TEST(test_unionSet);
  RUN_TEST(test_unionSetRank);
  return UNITY_END();
}
