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

#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}

/* Implementation of the opaque type */
struct _node {
  void*  elem;             /*  */
  struct _node *prev;      /* di fatto node_o */
  struct _node *next;
};

void node_remove(node_o *node);

node_o* list_new(void *elem) {
  ASSERT_PARAMETERS_NOT_NULL(elem);
  node_o *new_list = malloc(sizeof(node_o));
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

void list_free(node_o *head){ // da togliere ricorsione (stack?) 
  if (head != NULL) {
    if(head->next != NULL){
      list_free(head->next);
    }
    free(head);
  }
  return;
}

void list_add(node_o **head, void *elem) {
  ASSERT_PARAMETERS_NOT_NULL(elem);
  node_o *new_node = list_new(elem);
  new_node->next = *head;
  new_node->prev = NULL;
  (*head)->prev = new_node;
  *head = new_node;
  return;
}

void *list_get_at(node_o *head, size_t index){
  size_t count = 0;
  while(head != NULL && count < index){
    head = head->next;
    ++count;
  }
  if(head == NULL){
    fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int)index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return head->elem;
}

void list_insert_at(node_o **head, size_t index, void *elem){
  if (index == 0) {
    list_add(head, elem);
    return;
  }

  size_t count = 0;
  node_o *current = *head;
  node_o *node = list_new(elem);

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int)index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  
  if(current->prev == NULL){
    printf("Non dovrei main leggere questa riga.\n");
    //list_add(head, elem);
    return;
  }

  node->next = current;
  node->prev = current->prev;
  current->prev->next = node;
  current->prev = node;
  return;  
}

void list_remove_at(node_o **head, size_t index){
  size_t count = 0;
  node_o *current = *head;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int)index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  if (index == 0) {
    *head = current->next;
    if (*head != NULL) {
      (*head)->prev = NULL;
    }
  }
  node_remove(current);

  return;
}

void node_remove(node_o *node) {
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  node->next = NULL;
  node->prev = NULL;
  //free(node->elem);
  free(node);
}

int list_is_empty(node_o *list){
  return list == NULL;
}

void list_set_at(node_o *list, size_t index, void *elem){
  ASSERT_PARAMETERS_NOT_NULL(list);
  ASSERT_PARAMETERS_NOT_NULL(elem);
  size_t count = 0;
  node_o *current = list;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int)index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  current->elem = elem;  
  return;  
}

int list_size(node_o *head){
  size_t size = 0;
  while(head != NULL){
    head = head->next;
    ++size;
  }
  return size;
}

int list_contains(node_o *head, void *elem, ListCompare compare){
  int boolean = 0;
  while(head != NULL && boolean != 1){
    if(compare(head->elem, elem) == 0){
      boolean = 1;
    }
    head = head->next;
  }
  return boolean;
}

void* list_search(node_o *head, void *elem, ListCompare compare){
  while(head != NULL){
    if(compare(head->elem, elem) == 0){
      return head->elem;
    }
    head = head->next;
  }
  return NULL;
}
