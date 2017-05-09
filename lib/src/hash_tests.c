/*
 *  File: hash_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include "unity.h"
#include "unity_internals.h"
#include "hash.h"


static void test_hashtableNew(){
  hashtable_o *table = hashtable_new(5);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New hash table failed");
  hashtable_free(table);
}

static void test_hashtableFree(){
  hashtable_o *table = hashtable_new(5);
  hashtable_free(table);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free hash table failed");
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hashtableNew);
  RUN_TEST(test_hashtableFree);
  return UNITY_END();
}
