/*
 *  File: kruskal.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


/*
 * Defines an abstracted graph.
 * The elements in the graph are comparable through the compare function.
 */

#pragma once

#include <stddef.h>
#include "graph.h"

/* Returns the minimum spanning tree (MST) created using the Kruskal algorithm from the given undirected graph. */
extern graph_o* kruskal(graph_o *graph);
