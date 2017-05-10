/*
 *  File: list.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */
 
 
/*
 * Implements an abstracted double linked list
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "list.h"

/* Implementation of the opaque type */
typedef struct _node {
  void*  elem;             /*  */
  struct _node *prev;      /* di fatto list_o */
  struct _node *next;
} node_o;

void node_free(node_o *node);


list_o list_new(void *elem) {
  list_o new_list = malloc(sizeof(node_o));
  if (new_list == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  new_list->elem = elem;
  new_list->next = NULL;
  new_list->prev = NULL;
  return new_list;
}

void list_free(list_o *list){ /* da togliere ricorsione (stack?) */
  if (!list_is_empty(list)) {
    node_free(*list);
  }
  return;
}

void node_free(node_o *node){
  if(node->next == NULL){
    free(node);
    return;
  }
  node_free(node->next);
  return;  
}

void list_add(list_o *list, void *elem) {
  node_o *node = list_new(elem);
  
  node->next = *list;
  if(*list != NULL){
    (*list)->prev = node;
  }
  *list = node;
  node->prev = NULL;
  return;
}

void *list_get_at(list_o *list, size_t index){
  size_t count = 0;
  node_o *node = *list;
  while(node != NULL && count < index){
    node = node->next;
    ++count;
  }
  if(node == NULL){
    fprintf(stderr, "List index (%ld) out of bounds\n", index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  
  return node->elem;
}

void list_insert_at(list_o *list, size_t index, void *elem){
  size_t count = 0;
  node_o *current = *list;

  node_o *node = list_new(elem);
  node->elem = elem;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%ld) out of bounds\n", index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  if(current->prev == NULL){
    list_add(list, elem);
    return;
  }
  
  node->next = current;
  node->prev = current->prev;
  current->prev->next = node;
  current->prev = node;
  return;  
}

void list_remove_at(list_o *list, size_t index){
  size_t count = 0;
  node_o *current = *list;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%ld) out of bounds\n", index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  
  if(current->prev == NULL){
    if(current->next != NULL){
      current->next->prev = NULL;
    }
    *list = current->next;
  } else {
    current->prev->next = current->next;
    if(current->next != NULL){
      current->next->prev = current->prev;
    }
  }

  /* NB non fa la free di elem */
  free(current);  
  return;  
}

int list_is_empty(list_o *list){
  return *list == NULL;
}

void list_set_at(list_o *list, size_t index, void *elem){
  size_t count = 0;
  node_o *current = *list;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%ld) out of bounds\n", index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  current->elem = elem;  
  return;  
}

int list_size(list_o *list){
  size_t size = 0;
  node_o *current = *list;
  while(current != NULL){
    current = current->next;
    ++size;
  }
  
  return size;
}

int list_contains(list_o *list, void *elem, ListCompare compare){
  int boolean = 0;
  node_o *current = *list;
  while(current != NULL && boolean != 1){
    if(compare(current->elem, elem) == 0){
      boolean = 1;
    }
    current = current->next;
  }
  
  return boolean;
}
/*
void* list_search(list_o *list, void *elem, ListCompare compare){
  node_o *current = *list;
  while(current != NULL){
    if(compare(current->elem, elem) == 0){
      return current->elem;
    }
    current = current->next;
  }
  return NULL;
}
*/
void* list_search(list_o *list, void *elem, ListCompare compare){
  size_t count = 0;
  node_o *current = *list;
  while(current != NULL){
    if(compare(current->elem, elem) == 0){
      break;
    }
    current = current->next;
    count++;
  }
  if(current == NULL)return NULL;
  return list_get_at(list, count);
}


