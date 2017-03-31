/*
 *  File: array.c
 *  Author: 
 *
 *  Date: 
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


