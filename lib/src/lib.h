/*
 *  File: lib.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-06-2017
 *
 */


/*
 * Internal functions and defines.
 */

#pragma once

#include <stddef.h>
#include <time.h>

#define TIMER_START(timer)  (timer = clock());
#define TIMER_STOP(timer, msg)  (printf("Processor time used: %f s (%s)\n", ((double)((clock_t)clock() - (timer))) / (CLOCKS_PER_SEC), (msg)));

/* Success or die malloc. */
extern void* xmalloc(size_t);

/* Success or die realloc. */
extern void* xrealloc(void *pointer, size_t size);
