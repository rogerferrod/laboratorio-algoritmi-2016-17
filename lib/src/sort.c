/*
 *  File: sort.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */

/*
 * Implements the sorting algorithms
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "array.h"
#include "sort.h"


/* Pivot choice method, can be random, median, first, last */
enum pvt_type {random,median,first,last};
#define PIVOT_TYPE random

#if PIVOT_TYPE == random
  #define PIVOT_INDEX(first,last) (rand()%((last)-(first)+1)+(first))
#elif PIVOT_TYPE == median
  #define PIVOT_INDEX(first,last) ((((last)-(first))/2)+(first))
#elif PIVOT_TYPE == first
  #define PIVOT_INDEX(first,last) (first)
#elif PIVOT_TYPE == last
  #define PIVOT_INDEX(first,last) (last)
#else
  #define PIVOT_INDEX(first,last) (rand()%(last-first+1)+first)
#endif

/* Partition needed for the quick sort */
static void q_partition(array_o* array, int begin, int end, int *p, int *q, ArrayCompare compare);

/* Recursive quicksort function */
static void q_sort(array_o* array, int top, int end, ArrayCompare compare);


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

  if(n == 0){
    return;
  }

  for(i = 0; i < n-1; ++i){
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
  if(array_size(array) == 0){
    return;
  }

  srand(time(NULL));
  q_sort(array, 0, array_size(array)-1, compare);
  return;
}

void q_sort(array_o* array, int begin, int end, ArrayCompare compare) {
  int i,j;

  q_partition(array, begin, end, &i, &j, compare);

  if(begin < j){
    q_sort(array, begin, j, compare);
   }
  if(i < end){
    q_sort(array, i, end, compare);
  }

  return;
}

void q_partition(array_o* array, int begin, int end, int *p, int *q, ArrayCompare compare) {
  void* pivot;
  int i,j;
  int pivot_index;

  pivot_index = PIVOT_INDEX(begin,end);

  pivot = array_at(array, pivot_index);
  i = begin;
  j = end;

  while (i <= j) {
    while(compare(array_at(array, i), pivot) < 0){ /* array[i] < pivot */
      i++;
    }
    while(compare(array_at(array, j), pivot) > 0){ /* array[j] > pivot */
      j--;
    }
    if(i <= j){
      array_swap(array, i, j);
      i++;
      j--;
    }
  }

  /* output */
  *p = i;
  *q = j;

  return;
}


