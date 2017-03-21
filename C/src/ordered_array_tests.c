#include "ordered_array.h"
#include "unity.h"
#include "unity_internals.h"


static void test_ordered_array_new_not_null() {
  OrderedArray* array = OrderedArray_new(10);
  TEST_ASSERT_NOT_NULL(array);

  OrderedArray_free(array);
}

static void test_ordered_array_new_capacity_is_correct() {
  OrderedArray* array = OrderedArray_new(10);
  TEST_ASSERT_EQUAL_INT(10, OrderedArray_capacity(array));

  OrderedArray_free(array);
}

static void test_ordered_array_new_size_zero() {
  OrderedArray* array = OrderedArray_new(10);
  TEST_ASSERT_EQUAL_INT(0, OrderedArray_size(array));

  OrderedArray_free(array);
}


/* void test_ordered_array_free() {
//
// }

// static void test_ordered_array_size() {
//
// }
//
// static void test_ordered_array_empty() {
//
// }
//
// static void test_ordered_array_at() {
//
// }
//
// static void test_ordered_array_insert() {
//
// }
*/

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_ordered_array_new_not_null);
  RUN_TEST(test_ordered_array_new_capacity_is_correct);
  RUN_TEST(test_ordered_array_new_size_zero);
  UNITY_END();

  return 0;
}
