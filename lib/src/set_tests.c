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
  //  TEST_ASSERT_EQUAL_INT();
  free_set(set);
}

static void test_findSet(){
  int *array = build_fixture();
  set_o *set = build_set();

  make_set(set, 0); /* 2 */
  make_set(set, 1); /* 5 */
  make_set(set, 2); /* 7 */

  printf("make(2); make(5); make(7); \n");
  printf("find(2); find(5); find(7); \n");
  printf("find_set: %d\n", array[(int)find_set(set, 0)]);
  printf("find_set: %d\n", array[(int)find_set(set, 1)]);
  printf("find_set: %d\n", array[(int)find_set(set, 2)]);
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


  printf("make(2); make(5); make(7); make(6); make(4); make(3); make(1); union(2,5); \n");
  union_set(set, 0, 1); 
  printf("find(2); find(5); find(7); \n");
  printf("find_set: %d\n", array[(int)find_set(set, 0)]);
  printf("find_set: %d\n", array[(int)find_set(set, 1)]);
  printf("find_set: %d\n", array[(int)find_set(set, 2)]);

  printf("union(2,7); \n");
  union_set(set, 0, 2);
  printf("find(2); find(5); find(7); \n");
  printf("find_set: %d\n", array[(int)find_set(set, 0)]);
  printf("find_set: %d\n", array[(int)find_set(set, 1)]);
  printf("find_set: %d\n", array[(int)find_set(set, 2)]);

  printf("union(6,4); union(3,1); \n");
  union_set(set, 3, 4);
  union_set(set, 5, 6);
  printf("find(6); find(4); find(3); find(1); \n");
  printf("find_set: %d\n", array[(int)find_set(set, 3)]);
  printf("find_set: %d\n", array[(int)find_set(set, 4)]);
  printf("find_set: %d\n", array[(int)find_set(set, 5)]);
  printf("find_set: %d\n", array[(int)find_set(set, 6)]);

  printf("union(4,3); \n");
  union_set(set, 4, 5);
  printf("find(4); find(3); \n");
  printf("find_set: %d\n", array[(int)find_set(set, 4)]);
  printf("find_set: %d\n", array[(int)find_set(set, 5)]);

  printf("union(5,6); \n");
  union_set(set, 1, 3);
  printf("find(2); find(5); find(7); find(6); find(4); find(3); find(1); \n");
  printf("find_set: %d\n", array[(int)find_set(set, 0)]);
  printf("find_set: %d\n", array[(int)find_set(set, 1)]);
  printf("find_set: %d\n", array[(int)find_set(set, 2)]);
  printf("find_set: %d\n", array[(int)find_set(set, 3)]);
  printf("find_set: %d\n", array[(int)find_set(set, 4)]);
  printf("find_set: %d\n", array[(int)find_set(set, 5)]);
  printf("find_set: %d\n", array[(int)find_set(set, 6)]);

  free_set(set);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_makeSet);
  RUN_TEST(test_findSet);
  RUN_TEST(test_unionSet);
  return UNITY_END();
}
