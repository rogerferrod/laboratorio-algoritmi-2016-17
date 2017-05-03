/*
 *  File: set.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
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
extern set_o* make_set(void*);

extern set_o* union_set(void*, void*);

extern set_o* link_set(void*, void*);

extern set_o* find_set(void*);
