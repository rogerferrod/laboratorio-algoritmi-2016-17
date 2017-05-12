/*
 *  File: hash_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 11-04-2017
 *
 */


#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "unity_internals.h"
#include "hash.h"

static int compare_str(void *x, void *y){
  return strcmp(x, y);
}

static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

static size_t hash(void* key) {
  return (size_t)strlen((char*)key);
}

static void test_hashtableNew(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New hash table failed");
  hashtable_free(table);
}

static void test_hashtableFree(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_free(table);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free hash table failed");
}

static void test_hashtableInsert(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Insert hash table failed");
  hashtable_free(table);
}

static void test_hashtableSearchNotFound(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  TEST_ASSERT(NULL == (int*)hashtable_search(table, "ciao"));
  hashtable_free(table);
}

static void test_hashtableSearchSimple(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  TEST_ASSERT_EQUAL_INT(5, *(int*)hashtable_search(table, "hello"));
  hashtable_free(table);
}

static void test_hashtableSearchChaining(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  hashtable_insert(table, "house", new_int(6)); /* collision */
  hashtable_insert(table, "mouse", new_int(8)); /* collision */
  TEST_ASSERT_EQUAL_INT(5, *(int*)hashtable_search(table, "hello"));
  TEST_ASSERT_EQUAL_INT(6, *(int*)hashtable_search(table, "house"));
  TEST_ASSERT_EQUAL_INT(8, *(int*)hashtable_search(table, "mouse"));
  hashtable_free(table);
}

static void test_hashtableSearch(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  hashtable_insert(table, "house", new_int(6)); /* collision */
  hashtable_insert(table, "bye", new_int(9));
  hashtable_insert(table, "hi", new_int(9));
  TEST_ASSERT_EQUAL_INT(5, *(int*)hashtable_search(table, "hello"));
  TEST_ASSERT_EQUAL_INT(6, *(int*)hashtable_search(table, "house"));
  TEST_ASSERT_EQUAL_INT(9, *(int*)hashtable_search(table, "bye"));
  TEST_ASSERT_EQUAL_INT(9, *(int*)hashtable_search(table, "hi"));
  hashtable_free(table);
}

/*static void test_hashtableInsertDuplicate(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  hashtable_insert(table, "hello");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Insert hash table failed"); /////
  hashtable_free(table);
  }*/

static void test_hashtableRemoveNoConflict(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  hashtable_remove(table, "hello");
  TEST_ASSERT(NULL == (int*)hashtable_search(table, "hello"));
  hashtable_free(table);
}

static void test_hashtableRemoveConflict(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  hashtable_insert(table, "mouse", new_int(6));
  hashtable_remove(table, "hello");
  TEST_ASSERT(NULL == (int*)hashtable_search(table, "hello"));
  hashtable_free(table);
}

static void test_hashtableRemoveFirst(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_insert(table, "hello", new_int(5));
  hashtable_insert(table, "mouse", new_int(6));
  hashtable_remove(table, "mouse");
  TEST_ASSERT(NULL == (int*)hashtable_search(table, "mouse"));
  hashtable_free(table);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hashtableNew);
  RUN_TEST(test_hashtableFree);
  RUN_TEST(test_hashtableInsert);
  RUN_TEST(test_hashtableSearchNotFound);
  RUN_TEST(test_hashtableSearchSimple);
  RUN_TEST(test_hashtableSearchChaining);
  RUN_TEST(test_hashtableSearch);
  //RUN_TEST(test_hashtableInsertDuplicate);
  RUN_TEST(test_hashtableRemoveNoConflict);
  RUN_TEST(test_hashtableRemoveConflict);
  RUN_TEST(test_hashtableRemoveFirst);
  return UNITY_END();
}
