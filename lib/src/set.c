/*
 *  File: set.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
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
  _mySet parent;  /* pointer to parent */
  int rank;
  void* label;
};

set_o* make_set(void* label){
  set_o *elem = malloc(sizeof(set_o));
  elem.parent = elem;
  elem.rank = 0;
  elem.label = label;
  return elem;
}

extern set_o* union_set(void*, void*);

extern set_o* link_set(void*, void*);

extern set_o* find_set(void*)
