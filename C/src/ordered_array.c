#include "ordered_array.h"
#include <stdlib.h>

struct _OrderedArray {
  void** array;
  size_t size;
  size_t capacity;
};

OrderedArray* OrderedArray_new(size_t capacity) {
  OrderedArray* result = (OrderedArray*) malloc(sizeof(OrderedArray));

  result->array = (void**) malloc(sizeof(void*)*capacity);
  result->size = 0;
  result->capacity = capacity;
  return result;
}

void OrderedArray_free(OrderedArray* array) {
  free(array->array);
  free(array);
  return;
}

size_t OrderedArray_size(OrderedArray* array) {
  return array->size;
}

size_t OrderedArray_capacity(OrderedArray* array) {
  return array->capacity;
}


int OrderedArray_empty(OrderedArray* array) {
  return array->size == 0;
}

void* OrderedArray_at(OrderedArray* array, size_t position) {
  return NULL;
}

void OrderedArray_insert(OrderedArray* array, void* element) {
  return;
}
