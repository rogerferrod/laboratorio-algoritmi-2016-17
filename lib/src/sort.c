/*
 *  File: array.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna 
 *
 *  Date: 
 *
 */

/*
 * Implements the sorting algorithms
 *
 */

#include "array.h"
#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

/* Partition needed for the quick sort */
static size_t array_partition(array_o* array, size_t top, size_t bottom, ArrayCompare compare);

static void q_sort(array_o* array, size_t top, size_t bottom, ArrayCompare compare);

void insertion_sort(array_o* array, ArrayCompare compare) {
  size_t i;
  size_t j;
  size_t size;
  size = array_size(array);

  for(i = 0; i < size; ++i ) {
    
    j = i;
    while(j > 0 && compare(array_at(array, j-1), array_at(array, j)) > 0){
      array_swap(array, j-1, j);
      j--;
    }
  }
  return;
}

void selection_sort(array_o* array, ArrayCompare compare) {
  size_t i,j,k,n;
  n = array_size(array);  

  for(i = 0; i < n -1; ++i){
    k = i;
    for(j = i + 1; j < n; ++j){
      if (compare(array_at(array, k), array_at(array, j)) > 0){
        k = j;
      }
    }
    array_swap(array,i,k);
  }
  return;
}

void quick_sort(array_o* array, ArrayCompare compare) {
  q_sort(array, 0, array_size(array)-1, compare);
  return;
}

//void q_sort(array_o* array, size_t top, size_t bottom, ArrayCompare compare) {
  //  size_t p;  

  //  if(bottom > 0){ /* se c'è almeno un elemento */ 
  //    p = array_partition(array, top, bottom, compare);
  //    if(p > 1) {/* se prima del perno ci sono almeno due elementi */
  //      q_sort(array, top, p-1, compare);
  //    }
  //    if(p < bottom - 1) {/* se dopo il perno ci sono almeno due elementi */
  //      q_sort(array, p + 1, bottom, compare);
  //    }
  //  }
  //  return;

  //if (top > bottom) return;
  //size_t p;
  //p = array_partition(array, top, bottom, compare);
  //q_sort(array, top, p-1, compare);
  //q_sort(array, p+1, bottom, compare);
  //return;

//}

void q_sort(array_o* array, size_t begin, size_t end, ArrayCompare compare) {
  size_t l, r; 
  void* pivot;
  if (end > begin) {
    pivot = array_at(array, begin);
    l = begin + 1;
    r = end+1;
    while(l < r)
      if (compare(array_at(array, l), pivot) < 0)
        l++;
      else {
        r--;
        array_swap(array, l, r); 
      }
      l--;
      array_swap(array, begin, l);
      q_sort(array, begin, l, compare);
      q_sort(array, r, end, compare);
    }
}

size_t array_partition(array_o* array, size_t begin, size_t end, ArrayCompare compare){

  //  void* pivot;
  //  size_t i,j;

  //  pivot = array_at(array, begin);  /* sarebbe meglio si trovasse a metà */
  //  i = begin+1;
  //  j = end;

  //  while (i < j) { /* minore stretto */
  //    if (compare(array_at(array, i), pivot) <= 0){ /* array[i] <= pivot */
  //      i++;
  //    } else if (compare(array_at(array, j), pivot) > 0){ /* array[j] > pivot */
  //      j--;
  //    } else {
  //      array_swap(array, i, j);
  //      i++;
  //      j--;
  //    }
  //  }
  //  array_swap(array, 0, j);
  //  return j;

  size_t i, j;
  i = begin;
  j = end+1;

  while(1) {
    while(compare(array_at(array, ++i), array_at(array, begin)) < 0) {
      if (i == end) break;
    }
    while(compare(array_at(array, begin), array_at(array, --j)) < 0) {
      if (j == begin) break;
    }
    if (i>=j) break;
    array_swap(array, i, j);
  }
  array_swap(array, begin, j);
  return j;
}
