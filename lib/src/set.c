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


/* Implementation of the opaque type */
struct _mySet {
  set_o *parent;  /* pointer to parent */
  int rank;
};

void make_set(set_o subset[], size_t i){
  subset[i]->parent = subset[i];
  subset[i]->rank = 0;
}

set_o* union_set(set_o* x, set_o* y) {
  return link_set(find_set(x), find_set(y));
}

set_o* link_set(set_o* x, set_o* y) {
  if (x->rank > y->rank) {
    y->parent = x;
    return x;
  }

  x->parent = y;

  if (x->rank == y->rank) {
    y->rank++;
  }

  return y;
}

set_o* find_set(set_o* elem) {
  while (elem != elem->parent) {
    elem = elem->parent;
  }
  return elem;
}

void free_set(set_o* elem) {
  free(elem);
}
