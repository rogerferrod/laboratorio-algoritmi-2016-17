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
  /*if(x == NULL || y == NULL){
    fprintf(stderr, "Null in compare_str!");
    exit(EXIT_FAILURE);
    }*/
  return strcmp(x, y);
}

static size_t hash(void* key) {
  return (size_t)strlen((char*)key);
}

static void test_hashtableNew(){
  hashtable_o *table = hashtable_new(5, hash);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "New hash table failed");
  hashtable_free(table);
}

static void test_hashtableFree(){
  hashtable_o *table = hashtable_new(5, hash);
  hashtable_free(table);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Free hash table failed");
}

static void test_hashtableInsert(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Insert hash table failed");
  hashtable_free(table);
}

static void test_hashtableSearchNotFound(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  TEST_ASSERT(NULL == (char*)hashtable_search(table, "ciao", compare_str));
  hashtable_free(table);
}

static void test_hashtableSearchSimple(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  TEST_ASSERT_EQUAL_INT(0, strcmp("hello", (char*)hashtable_search(table, "hello", compare_str)));
  hashtable_free(table);
}

static void test_hashtableSearchChaining(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  hashtable_insert(table, "house"); /* collision */
  hashtable_insert(table, "mouse"); /* collision */
  TEST_ASSERT_EQUAL_INT(0, strcmp("hello", (char*)hashtable_search(table, "hello", compare_str)));
  TEST_ASSERT_EQUAL_INT(0, strcmp("house", (char*)hashtable_search(table, "house", compare_str)));
  TEST_ASSERT_EQUAL_INT(0, strcmp("mouse", (char*)hashtable_search(table, "mouse", compare_str)));
  hashtable_free(table);
}

static void test_hashtableSearch(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  hashtable_insert(table, "house"); /* collision */
  hashtable_insert(table, "bye");
  hashtable_insert(table, "hi");
  TEST_ASSERT_EQUAL_INT(0, strcmp("hello", (char*)hashtable_search(table, "hello", compare_str)));
  TEST_ASSERT_EQUAL_INT(0, strcmp("house", (char*)hashtable_search(table, "house", compare_str)));
  TEST_ASSERT_EQUAL_INT(0, strcmp("bye", (char*)hashtable_search(table, "bye", compare_str)));
  TEST_ASSERT_EQUAL_INT(0, strcmp("hi", (char*)hashtable_search(table, "hi", compare_str)));
  hashtable_free(table);
}

/*static void test_hashtableInsertDuplicate(){
  hashtable_o *table = hashtable_new(10, hash);
  hashtable_insert(table, "hello");
  hashtable_insert(table, "hello");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Insert hash table failed"); /////
  hashtable_free(table);
  }*/


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
  return UNITY_END();
}
