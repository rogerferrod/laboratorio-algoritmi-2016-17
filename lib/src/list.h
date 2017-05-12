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
typedef struct _node node_o;

/* Definition of the array's compare function */
typedef int (*ListCompare)(void*, void*);



/*  */
extern node_o* list_new(void *elem);

/* Deallocate a list */
extern void list_free(node_o *head);

/**
 * Aggiunge all'inizio della lista
 * @param list
 * @param elem
 */
extern void list_add(node_o **list, void *elem);

extern void *list_get_at(node_o *list, size_t index);

extern void list_insert_at(node_o **list, size_t index, void *elem);

extern void list_remove_at(node_o **list, size_t index);

extern int list_is_empty(node_o *list);

extern void list_set_at(node_o *list, size_t index, void *elem);

extern int list_size(node_o *list);

extern int list_contains(node_o *list, void *elem, ListCompare compare);

extern void* list_search(node_o *list, void *elem, ListCompare compare);
