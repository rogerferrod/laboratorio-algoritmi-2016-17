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
#include <assert.h>
#include "lib.h"
#include "set.h"

/* Implementation of the opaque type */
struct _mySet {
  set_o *parent;
  int rank;
  void *elem;
};

set_o* make_set(void* elem){
  register set_o *set = (set_o*) xmalloc(sizeof(set_o));
  set->parent = set;
  set->rank = 0;
  set->elem = elem;
  return set;
}

set_o* find_set(set_o *x) {
  assert(x != NULL);

  while(x != x->parent){
    x = x->parent;
  }
  return x;
}

void link_set(set_o *x, set_o *y) {
  assert(x != NULL);
  assert(y != NULL);

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

void union_set(set_o *x, set_o *y) {
  link_set(find_set(x), find_set(y));
  return;
}

void free_set(set_o *set) {
  free(set);
  return;
}
