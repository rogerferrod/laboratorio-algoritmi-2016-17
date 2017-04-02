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


void insertion_sort(array_o* array, ArrayCompare compare) {
  size_t i;
  size_t j;

  for(i = 0; i < array_size(array); ++i ) {
    
    j = i;
    while(j > 0 && compare(array_at(array, j-1), array_at(array, j)) == 1){
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
      if (compare(array_at(array, k), array_at(array, j)) == 1){
        k = j;
      }
    }
    array_swap(array,i,k);
  }
  return;
}

void quick_sort(array_o* array, size_t top, size_t bottom, ArrayCompare compare) {
  size_t p;  

  if(bottom > 0){ /* se c'è almeno un elemento */ 
    p = array_partition(array, top, bottom, compare);
    if(p > 1) /* se prima del perno ci sono almeno due elementi */
      quick_sort(array, top, p-1, compare);
    if(p < bottom - 1) /* se dopo il perno ci sono almeno due elementi */
      quick_sort(array, p + 1, bottom, compare);
  }
  return;
}

size_t array_partition(array_o* array, size_t top, size_t bottom, ArrayCompare compare){
  void* pivot;
  size_t i,j;

  pivot = array_at(array, 0);  /* sarebbe meglio si trovasse a metà */
  i = 1;
  j = bottom;

  while (i < j) { /* minore stretto */
    if (compare(array_at(array, i), pivot) <= 0){ /* array[i] <= pivot */
      i++;
    } else if (compare(array_at(array, i), pivot) > 0){ /* array[i] > pivot */
      j--;
    } else {
      array_swap(array, i, j);
      i++;
      j--;
    }
  }
  array_swap(array, 0, j);
  return j;
}
