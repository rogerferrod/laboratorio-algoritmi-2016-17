/*
 *  File: list.h
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-08-2017
 *
 */


/*
 * Defines an abstracted double linked list. The elements in 
 * the list are comparable through the compare function
 * A list is a pointer to a node
 *
 */

#pragma once

#include <stddef.h>


/* Definition  */
//typedef struct _node* node_o;
typedef struct _myList list_o;

typedef struct _myList queue_o;

/* Definition of the array's compare function */
typedef int (*ListCompare)(void*, void*);

/*  */
extern list_o* list_new();

/* Deallocate a list */
extern void list_free(list_o *list);

extern size_t list_size(list_o *list);

extern int list_is_empty(list_o *list);

/* Add elem at the beginning of the list */
extern void list_add(list_o *list, void *elem);

extern void* list_front(list_o *list);

extern void* list_back(list_o *list);

extern void *list_get_at(list_o *list, size_t index);

/** inserisco elem in modo che quando inserito sarà in posizione index */
extern void list_insert_at(list_o *list, size_t index, void *elem);

extern void list_remove_at(list_o *list, size_t index);

extern void list_set_at(list_o *list, size_t index, void *elem);

extern size_t list_size(list_o *list);

extern int list_contains(list_o *list, void *elem, ListCompare compare);
/*
extern void* list_search(node_o *list, void *elem, ListCompare compare);
*/
