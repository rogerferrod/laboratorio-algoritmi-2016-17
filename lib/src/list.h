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
typedef struct _node* list_o; 

/* Definition of the array's compare function */
typedef int (*ListCompare)(void*, void*);



/*  */
extern list_o list_new(void *elem);

/* Deallocate a list */
extern void list_free(list_o *list);

extern void list_add(list_o *list, void *elem);

extern void *list_get_at(list_o *list, size_t index);

extern void list_insert_at(list_o *list, size_t index, void *elem);

extern void list_remove_at(list_o *list, size_t index);

extern int list_is_empty(list_o *list);

extern void list_set_at(list_o *list, size_t index, void *elem);

extern int list_size(list_o *list);

extern int list_contains(list_o *list, void *elem, ListCompare compare);

extern void* list_search(list_o *list, void *elem, ListCompare compare);
