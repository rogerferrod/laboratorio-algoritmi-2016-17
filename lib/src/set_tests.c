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

#define MAX_LENGHT 10

/*static int array[MAX_ARRAY] = {1,2,3,4,5,6};
 */
static int* build_fixture() {
  int *array = malloc(MAX_ARRAY*sizeof(int));
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
}

static void test_unionSet(){
  int *array = build_fixture();
  set_o *set = build_set();

  make_set(set, 0); /* 2 */
  make_set(set, 1); /* 5 */
  make_set(set, 2); /* 7 */

  printf("make(2); make(5); make(7); union(2,5); \n");
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
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_makeSet);
  RUN_TEST(test_findSet);
  RUN_TEST(test_unionSet);
  return UNITY_END();
}
