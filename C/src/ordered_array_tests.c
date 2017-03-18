#include "unity.h"
#include "ordered_array.h"

typedef struct _OrderedArray OrderedArray;

static void test_OrderedArray_new_not_null(void) {
	OrderedArray* array = OrderedArray_new(10);
	TEST_ASSERT_NOT_NULL(array);

	OrderedArray_free(array);
}

static void test_OrderedArray_new_capacity_is_correct(void) {
	OrderedArray* array = OrderedArray_new(10);
	TEST_ASSERT_EQUAL_INT(10, OrderedArray_capacity(array));

	OrderedArray_free(array);
}

static void test_OrderedArray_new_size_zero(void) {
	OrderedArray* array = OrderedArray_new(10);
	TEST_ASSERT_EQUAL_INT(0, OrderedArray_size(array));

	OrderedArray_free(array);
}

static void test_OrderedArray_free(void) {
	return;
}

static void test_OrderedArray_size(void) {
	return;
}

static void test_OrderedArray_capacity(void) {
	return;
}

static void test_OrderedArray_empty(void) {
	return;
}

static void test_OrderedArray_at(void) {
	return;
}

static void test_OrderedArray_insert(void) {
	return;
}



int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_OrderedArray_new_not_null);
	RUN_TEST(test_OrderedArray_new_capacity_is_correct);
	RUN_TEST(test_OrderedArray_new_size_zero);
	RUN_TEST(test_OrderedArray_free);
	RUN_TEST(test_OrderedArray_size);
	RUN_TEST(test_OrderedArray_capacity);
	RUN_TEST(test_OrderedArray_empty);
	RUN_TEST(test_OrderedArray_at);
	RUN_TEST(test_OrderedArray_insert);
	return UNITY_END();
}
