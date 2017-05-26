/*
 *  File: queue.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */


/*
 * Defines an abstracted queue.
 */

#pragma once

#include <stddef.h>


/* Definition of the queue.*/
typedef struct _myQueue queue_o;

extern queue_o* queue_new();
extern void queue_free(queue_o* queue);
extern void queue_enqueue(queue_o *queue, void* elem);
extern void* queue_dequeue(queue_o *queue);
extern void* queue_front(queue_o *queue);
extern void* queue_back(queue_o *queue);
extern size_t queue_size(queue_o *queue);
extern int queue_is_empty(queue_o *queue);
