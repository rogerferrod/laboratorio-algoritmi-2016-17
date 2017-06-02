/*
 *  File: lib.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Defines an abstracted array. The elements in 
 * the array are comparable through the compare function
 *
 */

#pragma once

#include <stddef.h>

extern void* xmalloc(size_t);

extern void* xrealloc(void *pointer, size_t size);
