/*
 *  File: set.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */
 
 
/*
 * Implements union-find data structure
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "set.h"

/* Implementation of the opaque type */
struct _mySet {
  set_o *parent;
  int rank;
  void *elem;
};

set_o* make_set(void* elem){
  set_o *set = (set_o*)malloc(sizeof(set_o));
  if(set == NULL){
    fprintf(stderr, "Not enough memory for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  set->parent = set;
  set->rank = 0;
  set->elem = elem;
  return set;
}

void union_set(set_o *x, set_o *y) {
  if(x == NULL || y == NULL){
    fprintf(stderr, "Invalid parameter NULL\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  
  link_set(find_set(x), find_set(y));
  return;
}

void link_set(set_o *x, set_o *y) {  
  if(x->rank > y->rank){
    y->parent = x;
  }
  else {
    x->parent = y;
    if(x->rank == y->rank){
      y->rank++;
    }
  }
  return;
}

set_o* find_set(set_o *x) {
  if(x == NULL){
    fprintf(stderr, "Invalid parameter NULL\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  
  while(x != x->parent){
    x = x->parent;
  }
  return x;
}

void free_set(set_o *set) {
  free(set);
  return;
}
