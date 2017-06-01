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

/* fare macro per errore malloc */

#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}


/*  A generic doubly-linked list */
struct list_entry {
  struct list_entry *next;	/* next element */
  struct list_entry *prev; 	/* previous element */
  void* elem;
};

typedef struct list_entry list_entry_o;
typedef struct list_entry queue_entry_o;

/*  A generic doubly-linked list  */
struct _myList {
  list_entry_o *head;
  list_entry_o *tail;
  size_t size;
};

list_o* list_new(){
  list_o *list = (list_o*)malloc(sizeof(list_o));
  if(list == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void list_free(list_o* list){
  if(list == NULL) return;

  list_entry_o *entry = list->head;
  while(entry != NULL){
    list_entry_o *current = entry;
    entry = entry->next;
    free(current);
  }
  free(list);
  return;
}

size_t list_size(list_o *list){
  ASSERT_PARAMETERS_NOT_NULL(list);
  return list->size;
}

int list_is_empty(list_o *list){
  ASSERT_PARAMETERS_NOT_NULL(list);
  return list->size == 0;
}

void list_add(list_o *list, void *elem) {
  ASSERT_PARAMETERS_NOT_NULL(list);
  ASSERT_PARAMETERS_NOT_NULL(elem);
  list_entry_o *entry = (list_entry_o*)malloc(sizeof(list_entry_o));
  if (entry == NULL) {
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  entry->elem = elem;
  entry->prev = NULL;
  entry->next = list->head;

  if (list->head != NULL) { //lista non vuota
    list->head->prev = entry;
  } else {  //list vuota: aggiorno tail
    list->tail = entry;
  }
  list->head = entry;

  list->size++;
  return;
}

/*potremmo fare se > meta parti dal fondo*/
void *list_get_at(list_o *list, size_t index){
  size_t count = 0;
  list_entry_o *node = list->head;

  while(node != NULL && count < index){ 
    node = node->next;
    ++count;
  }
  if(node == NULL){
    fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int)index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  return node->elem;
}

 /*potremmo fare se > meta parti dal fondo*/
void list_insert_at(list_o *list, size_t index, void *elem){
  if (index == 0) { //inserisco come primo elemento
    list_add(list, elem);
    return;
  }
  
  size_t count = 0;
  list_entry_o *current = list->head;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }

  if(current == NULL){
    if (count != index) {
      fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int) index);
      errno = ENOMEM;
      exit(EXIT_FAILURE);
    } else {  //inserisco come ultimo elemento (dopo list->tail)
      list_entry_o *node = (list_entry_o*)malloc(sizeof(list_entry_o));
      if (node == NULL) {
        fprintf(stderr, "Not enough space for malloc\n");
        errno = ENOMEM;
        exit(EXIT_FAILURE);
      }
      node->prev = list->tail;
      node->next = NULL;
      node->elem = elem;
      list->tail->next = node;
      list->tail = node;
      list->size++;
      return;
    }
  }
  // inserisco sicuramente tra 2 elementi già esistenti
  list_entry_o *node = (list_entry_o*)malloc(sizeof(list_entry_o));
   if (node == NULL) {
     fprintf(stderr, "Not enough space for malloc\n");
     errno = ENOMEM;
     exit(EXIT_FAILURE);
   }
  node->prev = current->prev;
  node->next = current;
  node->elem = elem;

  current->prev->next = node; 
  current->prev = node;

  list->size++;
  return;  
}

void list_remove_at(list_o *list, size_t index){
  size_t count = 0;
  list_entry_o *current = list->head;

  while(current != NULL && count < index){
    current = current->next;
    ++count;
  }
  if(current == NULL){
    fprintf(stderr, "List index (%d) out of bounds\n", (unsigned int)index);
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  if (current->next == NULL) { // ultimo 
    list->tail = current->prev;
  } else {
    current->next->prev = current->prev;
  }
  if (current->prev == NULL) { // primo
    list->head = current->next;
  } else {
    current->prev->next = current->next;
  }

  list->size--;
  free(current);
  return;
}

void list_set_at(list_o *list, size_t index, void *elem){
  ASSERT_PARAMETERS_NOT_NULL(list);
  ASSERT_PARAMETERS_NOT_NULL(elem);
  size_t count = 0;
  list_entry_o *current = list->head;

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

int list_contains(list_o *list, void *elem, ListCompare compare){
  list_entry_o *head = list->head;
  while(head != NULL){
    if(compare(head->elem, elem) == 0){
      return 1;
    }
    head = head->next;
  }
  return 0;
}

void* list_search(list_o *list, void *elem, ListCompare compare){
  ASSERT_PARAMETERS_NOT_NULL(list);
  //ASSERT_PARAMETERS_NOT_NULL(elem);
  ASSERT_PARAMETERS_NOT_NULL(compare);
  list_entry_o *head = list->head;
  while(head != NULL){
    if(compare(head->elem, elem) == 0){
      return head->elem;
    }
    head = head->next;
  }
  return NULL;
}

queue_o* queue_new() {
  return (queue_o*)list_new();
}

void queue_free(queue_o* queue) {
  list_free((list_o*)queue);
}

void queue_enqueue(queue_o *queue, void* elem) {
  ASSERT_PARAMETERS_NOT_NULL(queue);
  queue_entry_o *entry = (queue_entry_o*)malloc(sizeof(queue_entry_o));
  entry->prev = queue->tail;
  entry->next = NULL;
  entry->elem = elem;
  queue->tail = entry;
  if(queue->size == 0){
    queue->head = entry;
  }
  queue->size++;
  return;
}

void* queue_dequeue(queue_o *queue) {
  ASSERT_PARAMETERS_NOT_NULL(queue);
  queue_entry_o *entry = queue->tail;
  void *elem = entry->elem;
  queue->tail = entry->prev;
  queue->size--;
  if(queue->size == 0){
    queue->head = NULL;
  }
  free(entry);
  return elem;
}

void* queue_front(queue_o *queue) {
  ASSERT_PARAMETERS_NOT_NULL(queue);
  return (queue->head != NULL) ? queue->head->elem : NULL;
}

void* queue_back(queue_o *queue) {
  ASSERT_PARAMETERS_NOT_NULL(queue);
  return (queue->tail != NULL) ? queue->tail->elem : NULL;
}

size_t queue_size(queue_o *queue) {
  return list_size((list_o*)queue);
}

int queue_is_empty(queue_o *queue) {
  return list_is_empty((list_o*)queue);
}
