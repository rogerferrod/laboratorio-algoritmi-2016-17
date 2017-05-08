/*
 *  File: graph.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Defines an abstracted graph. The elements in 
 * the graph are comparable through the compare function
 *
 */

#pragma once

#include <stddef.h>


/* Definition of the graph's opaque type */
typedef struct _myGraph graph_o;

/* Definition of the graph's compare function */
typedef int (*GraphCompare)(void*, void*);



/* Return a newly allocated graph */
extern graph_o* graph_new(size_t capacity);
