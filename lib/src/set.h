/*
 *  File: set.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 03-05-2017
 *
 */


/*
 * Defines an abstracted etc etc
 *
 */

#pragma once

#include <stddef.h>


/* Definition of the set's opaque type */
typedef struct _mySet set_o;

/* Definition of the array's compare function */
typedef int (*SetCompare)(void*, void*);



/* ....... */
extern void make_set(set_o*, size_t);

extern set_o* union_set(set_o*, set_o*);

extern set_o* link_set(set_o*, set_o*);

extern set_o* find_set(set_o*);
