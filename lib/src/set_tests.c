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

#define MAX_ARRAY 10

static int array[MAX_ARRAY] = {1,2,3,4,5,6};

static set_o* build_fixture() {
  set_o *singletons = malloc(MAX_ARRAY*sizeof(set_o));
  
  return singletons;
}

static void test_makeSet() {
  set_o *singletons = build_fixture();
  for(int i = 0; i < MAX_ARRAY; i++){
    make_set(singletons, i);
  }
  //for(int i = 0; i<MAX_ARRAY, i++){
  //  TEST_ASSERT_EQUAL_INT(1, *(int*)array_at(array, 0));
  //  }
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_makeSet);
  return UNITY_END();
}
