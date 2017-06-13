/*
 *  File: set.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */


/*
 * Defines an abstracted union-find data structure.
 */

#pragma once

#include <stddef.h>

/* Definition of the set's opaque type. */
typedef struct _mySet set_o;


/* Returns a new set. */
extern set_o* make_set(void*);

/* Union between two sets. */
extern void union_set(set_o*, set_o*);

/* Links two trees based on their ranks. */
extern void link_set(set_o*, set_o*);

/* Returns the rappresentative of the given set. */
extern set_o* find_set(set_o*);

/* Free memory. */
extern void free_set(set_o*);
