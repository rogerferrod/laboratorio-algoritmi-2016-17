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

  for(i = 0; i < array_size(array); ++i ) {
    size_t j;
    j = i;
    while(j > 0 && compare(array_at(array, j-1), array_at(array, j)) == 1){
      array_swap(array, j-1, j);
      j--;
    }
  }
  return;
}


