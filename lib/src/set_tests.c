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

#define MAX_LENGTH 10

static int* build_fixture() {
  int *array = malloc(MAX_LENGTH*sizeof(int));
  array[0] = 2;
  array[1] = 5;
  array[2] = 7;
  array[3] = 6;
  array[4] = 4;
  array[5] = 3;
  array[6] = 1;
  return array;
}

static void test_makeSet() {
  set_o *set = build_set();
  make_set(set, 1);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Make set failed");
  free_set(set);
}

static void test_findSet(){
  int *array = build_fixture();
  set_o *set = build_set();

  make_set(set, 0); /* 2 */
  make_set(set, 1); /* 5 */
  make_set(set, 2); /* 7 */

  TEST_ASSERT_EQUAL_INT(2, array[(int)find_set(set, 0)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 1)]);
  TEST_ASSERT_EQUAL_INT(7, array[(int)find_set(set, 2)]);
  free_set(set);
}

static void test_unionSet(){
  int *array = build_fixture();
  set_o *set = build_set();

  make_set(set, 0); /* 2 */
  make_set(set, 1); /* 5 */
  make_set(set, 2); /* 7 */
  make_set(set, 3); /* 6 */
  make_set(set, 4); /* 4 */
  make_set(set, 5); /* 3 */
  make_set(set, 6); /* 1 */


  union_set(set, 0, 1);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 0)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 1)]);
  TEST_ASSERT_EQUAL_INT(7, array[(int)find_set(set, 2)]);

  union_set(set, 0, 2);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 0)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 1)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 2)]);

  union_set(set, 3, 4);
  union_set(set, 5, 6);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 0)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 1)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 2)]);
  TEST_ASSERT_EQUAL_INT(4, array[(int)find_set(set, 3)]);
  TEST_ASSERT_EQUAL_INT(4, array[(int)find_set(set, 4)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 5)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 6)]);

  union_set(set, 4, 5);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 0)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 1)]);
  TEST_ASSERT_EQUAL_INT(5, array[(int)find_set(set, 2)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 3)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 4)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 5)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 6)]);

  union_set(set, 1, 3);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 0)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 1)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 2)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 3)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 4)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 5)]);
  TEST_ASSERT_EQUAL_INT(1, array[(int)find_set(set, 6)]);

  free_set(set);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_makeSet);
  RUN_TEST(test_findSet);
  RUN_TEST(test_unionSet);
  return UNITY_END();
}
