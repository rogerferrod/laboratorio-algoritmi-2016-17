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

#define MAX_ARRAY 50


/* Definition of the set's opaque type */
typedef struct _mySet set_o;


/* ....... */
extern set_o* build_set();

extern void make_set(set_o*, size_t);

extern void  union_set(set_o*, size_t, size_t);

extern void link_set(set_o*, size_t, size_t);

extern size_t find_set(set_o*, size_t);
