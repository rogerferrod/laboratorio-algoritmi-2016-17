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
#include <time.h>

/* Partition needed for the quick sort */
/* da rimettere static */
 size_t array_partition(array_o* array, size_t top, size_t bottom, ArrayCompare compare);

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

void q_sort(array_o* array, size_t begin, size_t bottom, ArrayCompare compare) {
  size_t p;  
  printf("begin %d, end %d\n", begin, bottom);
  
  if(bottom > begin){ /* se c'è almeno un elemento */
   p = array_partition(array, begin, bottom, compare);
   if(p > 1){  /* se prima del perno ci sono almeno due elementi */
     q_sort(array, begin, p-1, compare); 
   }
   if((bottom-p)> 1){ /* se dopo il perno ci sono almeno due elementi */
     q_sort(array, p+1, bottom, compare);
   }
  }

  return;
}

size_t array_partition(array_o* array, size_t begin, size_t end, ArrayCompare compare){

 for(int i = begin; i <= end; ++i){
    int *elem;
    elem = (int*)array_at(array,i);
    printf("%d ", *elem);
  }
   printf("\n");


  void* pivot;
  int i,j;
  pivot = array_at(array, ((end-begin)/2)+begin);  /* sarebbe meglio si trovasse a metà */
  i = (int)begin;
  j = (int)end;

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

   for(int i = begin; i <= end; ++i){
    int *elem;
    elem = (int*)array_at(array,i);
    printf("%d ", *elem);
  }
   printf("[p %d]\n", i-begin);

    return i;
}

