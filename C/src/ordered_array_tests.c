#include "ordered_array.h"
#include "unity.h"
#include "unity_internals.h"

typedef struct _OrderedArray OrderedArray;

static void test_OrderedArray_new_not_null(size_t capacity) {
	OrderedArray* array = OrderedArray_new(10);
	TEST_ASSERT_NOT_NULL(array);

	OrderedArray_free(array);
}

static void test_OrderedArray_new_capacity_is_correct(size_t capacity) {
	OrderedArray* array = OrderedArray_new(10);
	TEST_ASSERT_EQUAL_INT(10, OrderedArray_capacity(array));

	OrderedArray_free(array);
}

static void test_OrderedArray_new_size_zero(size_t capacity) {
	OrderedArray* array = OrderedArray_new(10);
	TEST_ASSERT_EQUAL_INT(0, OrderedArray_size(array));

	OrderedArray_free(array);
}

static void test_OrderedArray_free(OrderedArray* array) {
	return;
}

static void test_OrderedArray_size(OrderedArray* array) {
	return;
}

static void test_OrderedArray_capacity(OrderedArray* array) {
	return;
}

static void test_OrderedArray_empty(OrderedArray* array) {
	return;
}

static void test_OrderedArray_at(OrderedArray* array, size_t position) {
	return;
}

static void test_OrderedArray_insert(OrderedArray* array, void* new) {
	return;
}



int main(int argc, char const *argv[]) {
	UNITY_BEGIN();
	RUN_TEST(test_OrderedArray_new_not_null);
	RUN_TEST(test_OrderedArray_new_capacity_is_correct);
	RUN_TEST(test_OrderedArray_new_size_zero);
	return UNITY_END();
}
