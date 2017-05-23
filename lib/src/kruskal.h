/*
 *  File: kruskal.h
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
#include "graph.h"

extern graph_o* kruskal(graph_o *graph);
