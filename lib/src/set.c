/*
 *  File: set.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 03-05-2017
 *
 */
 
 
/*
 * Implements disjoint-set ...
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "set.h"
#include "array.h"


/* Implementation of the opaque type */
struct _mySet {
  array_o *parent;
  array_o *rank;
};

set_o* build_set(){
  set_o *set = (set_o*)malloc(sizeof(set_o));
  set->parent = array_new(MAX_ARRAY);
  set->rank = array_new(MAX_ARRAY);
  return set;
}

void make_set(set_o *set, size_t i){
  array_insert_at(set->parent, i, (size_t*)i);
  array_insert_at(set->rank, i, (size_t*)0);
}

void union_set(set_o *set, size_t x, size_t y) {
  link_set(set, find_set(set, x), find_set(set, y));
}

void link_set(set_o *set, size_t x, size_t y) {
  if(array_at(set->rank, x) > array_at(set->rank, y)){
    array_insert_at(set->parent, y, (size_t*)x); /* p[y] = x */
  }
  else {
    array_insert_at(set->parent, x, (size_t*)y); /* p[x] = y */
  }
  if(array_at(set->rank,x) == array_at(set->rank, y)){
    array_insert_at(set->rank, y, (size_t*)array_at(set->rank, y) + 1); /* rank[y] = rank[y] + 1 */
  }
}

size_t find_set(set_o *set, size_t x) {
  if(x != (size_t)array_at(set->parent, x)){
    x = find_set(set, (size_t)array_at(set->parent, x));
  }
  return x;
}

void free_set(set_o *set) {
  array_free(set->parent);
  array_free(set->rank);
  free(set);
}
