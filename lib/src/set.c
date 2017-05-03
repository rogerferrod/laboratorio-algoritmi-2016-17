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
  array_insert_at(set->parent, (size_t*)i, i);
  array_insert_at(set->rank, (size_t*)0, i);
}

void union_set(set_o *set, size_t x, size_t y) {
  link_set(set, find_set(set, x), find_set(set, y));
}

void link_set(set_o *set, size_t x, size_t y) { /* da rimettere come prima */ 
  if(array_at(set->rank, x) > array_at(set->rank, y)){
    array_insert_at(set->parent, (size_t*)x, y); /* p[y] = x */
  }
  else {
    array_insert_at(set->parent, (size_t*)y, x); /* p[x] = y */
  }
  if(array_at(set->rank,x) == array_at(set->rank, y)){
    array_insert_at(set->rank, (size_t*)array_at(set->rank, y) + 1, y); /* rank[y] = rank[y] + 1 */
  }
}

size_t find_set(set_o *set, size_t x) {
  if(x != (size_t)array_at(set->parent, x)){
    x = find_set(set, (size_t)array_at(set->parent, x));
  }
  return x;
}
