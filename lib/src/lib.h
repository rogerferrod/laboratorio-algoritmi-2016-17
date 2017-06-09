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
#include <time.h>

#define TIMER_START(timer)  (timer = clock());
#define TIMER_STOP(timer, msg)   (printf("Processor time used: %f s (%s)\n", \
            ((double) ((clock_t)clock() - timer)) / CLOCKS_PER_SEC, msg));


extern void* xmalloc(size_t);

extern void* xrealloc(void *pointer, size_t size);


typedef int (*Procedure)(void*, void*);
