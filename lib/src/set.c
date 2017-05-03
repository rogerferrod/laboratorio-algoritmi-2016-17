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
  size_t parent;  /* index of parent */
  int rank;
};

void make_set(set_o singletons[], size_t i){
  singletons[i].parent = i;
  singletons[i].rank = 0;
}

void union_set(set_o singletons[], size_t x, size_t y) {
  link_set(singletons, find_set(singletons, x), find_set(singletons, y));
}

void link_set(set_o singletons[], size_t x, size_t y) {
  if (singletons[x].rank > singletons[y].rank) {
    singletons[y].parent = x;
  }
  else{
    singletons[x].parent = y;
    if (singletons[x].rank == singletons[y].rank) {
      singletons[y].rank++;
    }
  } 
}

size_t find_set(set_o singletons[], size_t i) {
  if(i != singletons[i].parent){
    i = find_set(singletons, singletons[i].parent);
  }
  return i;
}
