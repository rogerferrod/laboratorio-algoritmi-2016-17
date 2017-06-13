/*
 *  File: list.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */


/*
 * Defines an abstracted double linked list.
 * The elements in the list are comparable through the compare function.
 * A list is a pointer to a node.
 */

#pragma once

#include <stddef.h>


/* Definition of the list's opaque type. */
typedef struct _myList list_o;

/* Definition of the queue's opaque type. */
typedef struct _myList queue_o;

/* Definition of the list/queue's compare function. */
typedef int (*ListCompare)(void*, void*);

/* Return a newly allocated list. */
extern list_o* list_new();

/* Deallocate a list. */
extern void list_free(list_o *list);

/* Return the size of a list. */
extern size_t list_size(list_o *list);

/* Return 1 if the list is empty, 0 otherwise. */
extern int list_is_empty(list_o *list);

/* Add elem at the beginning of the list. */
extern void list_add(list_o *list, void *elem);

/* Return a pointer to the element in the specified position. */
extern void *list_get_at(list_o *list, size_t index);

/* Add elem at the index position. */
extern void list_insert_at(list_o *list, size_t index, void *elem);

/* Remove elem at the index position. */
extern void list_remove_at(list_o *list, size_t index);

/* Update the element at the index position with the new elem. */
extern void list_set_at(list_o *list, size_t index, void *elem);

/* Return 1 if the list contains elem, 0 otherwise. */
extern int list_contains(list_o *list, void *elem, ListCompare compare);

/* Return the element if the list contains elem, NULL otherwise. */
extern void* list_find(list_o *list, void *elem, ListCompare compare);


/* Return a newly allocated queue. */
extern queue_o* queue_new();

/* Deallocate a queue. */
extern void queue_free(queue_o* queue);

/* Add elem at the end of the queue. */
extern void queue_enqueue(queue_o *queue, void* elem);

/* Remove the element at the beginning of the queue. */
extern void* queue_dequeue(queue_o *queue);

/*Retrieve the element at the beginning of the queue. */
extern void* queue_front(queue_o *queue);

/*Retrieve the element at the end of the queue. */
extern void* queue_back(queue_o *queue);

/* Return the size of a queue. */
extern size_t queue_size(queue_o *queue);

/* Return 1 if the queue is empty, 0 otherwise. */
extern int queue_is_empty(queue_o *queue);
