/*
 *  File: sort.c
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
#include <time.h>

enum pivot_types{random,median,first,last};

#define PIVOT_TYPE random

/* Partition needed for the quick sort */
/* da rimettere static */
int array_partition(array_o* array, int begin, int end, ArrayCompare compare);

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

void q_sort(array_o* array, int  begin, int  end, ArrayCompare compare) {
  void* pivot;
  int i,j;
  int pivot_index;

  switch(PIVOT_TYPE){
  case random:
    pivot_index = rand()%(end-begin+1)+begin;
    break;
  case median:
    pivot_index = ((end-begin)/2)+begin;
    break;
  case first:
    pivot_index = begin;
    break;
  case last:
    pivot_index = end;
    break;
  default: pivot_index = begin;
  }

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

   if(begin < j){
     q_sort(array, begin, j, compare);
   }
   if(i < end){
     q_sort(array, i, end, compare);
   }

  return;
}

int array_partition(array_o* array, int begin, int end, ArrayCompare compare){
  return 0;
}

