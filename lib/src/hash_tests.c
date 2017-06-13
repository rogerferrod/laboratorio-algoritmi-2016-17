/*
 *  File: hash_tests.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "unity.h"
#include "hash.h"

static int compare_str(void *x, void *y){
  return strcmp(x, y);
}

static int* new_int(int value) {
  int* elem = (int*) xmalloc(sizeof(int));
  *elem = value;
  return elem;
}

static size_t hash(void* key) {
  return (size_t)strlen((char*)key);
}

static void free_fixture(hashtable_o *table) {
  iterator *iter = hashtable_iter_init(table);
  void *key, *value;
  while (hashtable_iter_hasNext(table, iter)) {
    hashtable_iter_next(table, iter, &key, &value);
    free(value);
  }
  free(iter);
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

static void test_hashtablePut(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "Insert hash table failed");

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableSizeEmpty(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  TEST_ASSERT_EQUAL_INT(0, hashtable_size(table));
  hashtable_free(table);
}

static void test_hashtableSize(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));
  TEST_ASSERT_EQUAL_INT(3, hashtable_size(table));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableSizeUpdate(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));

  TEST_ASSERT_EQUAL_INT(3, hashtable_size(table));

  hashtable_put(table, "mouse", new_int(17));
  TEST_ASSERT_EQUAL_INT(3, hashtable_size(table));

  hashtable_put(table, "hi", new_int(7));
  TEST_ASSERT_EQUAL_INT(3, hashtable_size(table));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableFindNotFound(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  TEST_ASSERT(NULL == (int*)hashtable_find(table, "ciao"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableFindSimple(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  TEST_ASSERT_EQUAL_INT(5, *(int*)hashtable_find(table, "hello"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableFindChaining(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "house", new_int(6)); /* collision */
  hashtable_put(table, "mouse", new_int(8)); /* collision */
  TEST_ASSERT_EQUAL_INT(5, *(int*)hashtable_find(table, "hello"));
  TEST_ASSERT_EQUAL_INT(6, *(int*)hashtable_find(table, "house"));
  TEST_ASSERT_EQUAL_INT(8, *(int*)hashtable_find(table, "mouse"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableFind(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "house", new_int(6)); /* collision */
  hashtable_put(table, "bye", new_int(9));
  hashtable_put(table, "hi", new_int(9));
  TEST_ASSERT_EQUAL_INT(5, *(int*)hashtable_find(table, "hello"));
  TEST_ASSERT_EQUAL_INT(6, *(int*)hashtable_find(table, "house"));
  TEST_ASSERT_EQUAL_INT(9, *(int*)hashtable_find(table, "bye"));
  TEST_ASSERT_EQUAL_INT(9, *(int*)hashtable_find(table, "hi"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableRemoveNoConflict(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_remove(table, "hello");
  TEST_ASSERT(NULL == (int*)hashtable_find(table, "hello"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableRemoveConflict(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_remove(table, "hello");
  TEST_ASSERT(NULL == (int*)hashtable_find(table, "hello"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableRemoveFirst(){
  hashtable_o *table = hashtable_new(10, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_remove(table, "mouse");
  TEST_ASSERT(NULL == (int*)hashtable_find(table, "mouse"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableExpandAuto(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));

  size_t old_capacity = hashtable_capacity(table);
  hashtable_put(table, "bye", new_int(1));

  TEST_ASSERT_EQUAL_INT(old_capacity*2, hashtable_capacity(table));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableExpandMultiple(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));

  size_t old_capacity = hashtable_capacity(table);
  hashtable_put(table, "bye", new_int(1));

  hashtable_put(table, "other", new_int(1));
  hashtable_put(table, "boh", new_int(1));
  hashtable_put(table, "idk", new_int(1));

  old_capacity = hashtable_capacity(table);
  hashtable_put(table, "ciao", new_int(1));
  TEST_ASSERT_EQUAL_INT(old_capacity*2, hashtable_capacity(table));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableIteratorInit(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));

  iterator *iter = hashtable_iter_init(table);

  TEST_ASSERT(NULL != iter);

  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableIteratorNull(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);

  iterator *iter = hashtable_iter_init(table);

  TEST_ASSERT_EQUAL_INT(0, hashtable_iter_hasNext(table, iter));

  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableIteratorNextFirst(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));

  iterator *iter = hashtable_iter_init(table);

  void *key = NULL;
  void *value = NULL;
  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(0, strcmp("mouse", key)); /* mouse */
  TEST_ASSERT_EQUAL_INT(6, *(int*)value); /* mouse */
  
  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableIteratorNextMultiple(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));

  iterator *iter = hashtable_iter_init(table);

  void *key = NULL;
  void *value = NULL;
  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(6, *(int*)value); /* mouse */

  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(5, *(int*)value); /* house */

  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(4, *(int*)value); /* hi */

  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableIteratorHasNext(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));
  hashtable_put(table, "bye", new_int(2));

  iterator *iter = hashtable_iter_init(table);
  void *key = NULL;
  void *value = NULL;

  TEST_ASSERT_EQUAL_INT(1, hashtable_iter_hasNext(table, iter));
  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(1, hashtable_iter_hasNext(table, iter));
  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(1, hashtable_iter_hasNext(table, iter));
  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(1, hashtable_iter_hasNext(table, iter));
  hashtable_iter_next(table, iter, &key, &value);
  TEST_ASSERT_EQUAL_INT(0, hashtable_iter_hasNext(table, iter));

  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableIterator(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));
  hashtable_put(table, "bye", new_int(3));

  iterator *iter = hashtable_iter_init(table);

  void *key = NULL;
  void *value = NULL;

  size_t counter = 0;

  while(hashtable_iter_hasNext(table,iter)){
    hashtable_iter_next(table, iter, &key, &value);
    counter++;
  }
  TEST_ASSERT_EQUAL_INT(4,counter);

  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableContains(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));
  hashtable_put(table, "bye", new_int(3));

  TEST_ASSERT_EQUAL_INT(1,hashtable_contains(table,"mouse"));
  TEST_ASSERT_EQUAL_INT(0,hashtable_contains(table,"roger"));

  free_fixture(table);
  hashtable_free(table);
}

static void test_hashtableUltimateExpand(){
  hashtable_o *table = hashtable_new(5, hash, compare_str);
  hashtable_put(table, "hello", new_int(5));
  hashtable_put(table, "mouse", new_int(6));
  hashtable_put(table, "hi", new_int(4));
  hashtable_put(table, "bye", new_int(1));
  hashtable_put(table, "other", new_int(1));
  hashtable_put(table, "boh", new_int(1));
  hashtable_put(table, "idk", new_int(1));
  hashtable_put(table, "ciao", new_int(1));
  hashtable_put(table, "ciaa", new_int(1));
  hashtable_put(table, "ciae", new_int(1));
  hashtable_put(table, "ciai", new_int(1));
  hashtable_put(table, "ciau", new_int(1));
  hashtable_put(table, "ciaz", new_int(1));


  char* str[] = {
    "hi",
    "bye",
    "boh",
    "idk",
    "ciaz",
    "ciau",
    "ciai",
    "ciae",
    "ciaa",
    "ciao",
    "mouse",
    "hello",
    "other"
  };

  iterator *iter = hashtable_iter_init(table);

  void *key = NULL;
  void *value = NULL;
  size_t i = 0;

  while(hashtable_iter_hasNext(table,iter)){
    hashtable_iter_next(table, iter, &key, &value);
    TEST_ASSERT_EQUAL_INT(0, strcmp(str[i], key));
    ++i;
  }

  free(iter);
  free_fixture(table);
  hashtable_free(table);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hashtableNew);
  RUN_TEST(test_hashtableFree);
  RUN_TEST(test_hashtablePut);
  RUN_TEST(test_hashtableSizeEmpty);
  RUN_TEST(test_hashtableSize);
  RUN_TEST(test_hashtableSizeUpdate);
  RUN_TEST(test_hashtableFindNotFound);
  RUN_TEST(test_hashtableFindSimple);
  RUN_TEST(test_hashtableFindChaining);
  RUN_TEST(test_hashtableFind);
  RUN_TEST(test_hashtableRemoveNoConflict);
  RUN_TEST(test_hashtableRemoveConflict);
  RUN_TEST(test_hashtableRemoveFirst);
  RUN_TEST(test_hashtableExpandAuto);
  RUN_TEST(test_hashtableExpandMultiple);
  RUN_TEST(test_hashtableIteratorInit);
  RUN_TEST(test_hashtableIteratorNull);
  RUN_TEST(test_hashtableIteratorNextFirst);
  RUN_TEST(test_hashtableIteratorNextMultiple);
  RUN_TEST(test_hashtableIteratorHasNext);
  RUN_TEST(test_hashtableIterator);
  RUN_TEST(test_hashtableContains);
  RUN_TEST(test_hashtableUltimateExpand);
  return UNITY_END();
}
