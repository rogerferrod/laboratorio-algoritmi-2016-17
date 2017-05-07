/*
 *  File: set.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */


/*
 * Defines an abstracted union-find data structure
 *
 */

#pragma once

#include <stddef.h>

/* Definition of the set's opaque type */
typedef struct _mySet set_o;


/* return new set */
extern set_o* make_set(void*);

/* union between two sets */
extern void union_set(set_o*, set_o*);

/* link two trees */
extern void link_set(set_o*, set_o*);

/* return rappresentative of set */
extern set_o* find_set(set_o*);

/* free memory */
extern void free_set(set_o*);
