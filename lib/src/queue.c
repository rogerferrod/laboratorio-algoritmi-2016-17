/*
 *  File: queue.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */
 
 
/*
 * Implements an abstracted array
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "queue.h"

#define ASSERT_PARAMETERS_NOT_NULL(x) if((x) == NULL){     \
           fprintf(stderr, "Invalid parameter NULL\n");    \
           errno = EINVAL;                                 \
           exit(EXIT_FAILURE);}
    

/*  A generic doubly-linked list (queue) */
struct queue_entry {
  struct queue_entry *next;	/* next element */
  struct queue_entry *prev; 	/* previous element */
  void* elem;
};

typedef struct queue_entry queue_entry_o;

/*  A generic doubly-linked list (queue) */
struct _myQueue {
  struct queue_entry *head;	/* */
  struct queue_entry *tail;
  size_t size;
};


queue_o* queue_new(){
  queue_entry_o *head = (queue_entry_o*)malloc(sizeof(queue_entry_o));
  if(head != NULL){
    queue_o *queue = (queue_o*)malloc(sizeof(queue_o));
    if(queue != NULL){
      head->next = NULL;
      head->prev = NULL;
      head->elem = NULL;
      queue->head = head;
      queue->tail = head;
      queue->size = 0;
      return queue;
    }
  }
  fprintf(stderr, "Not enough space for malloc\n");
  errno = ENOMEM;
  exit(EXIT_FAILURE);
}

void queue_free(queue_o* queue){
  if(queue != NULL){
    queue_entry_o *entry = queue->tail;
    while(entry->prev != NULL){
      free(entry->next); //non mi piace
      entry = entry->prev;
    }
    free(entry);
  }
  free(queue);
  return;  
}

void queue_enqueue(queue_o *queue, void* elem){
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

void* queue_dequeue(queue_o *queue){
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

void* queue_front(queue_o *queue){
  ASSERT_PARAMETERS_NOT_NULL(queue);
  return (queue->head != NULL)? queue->head->elem : NULL;
}

void* queue_back(queue_o *queue){
  ASSERT_PARAMETERS_NOT_NULL(queue);
  return (queue->tail != NULL)? queue->tail->elem : NULL;
}

size_t queue_size(queue_o *queue){
  ASSERT_PARAMETERS_NOT_NULL(queue);
  return queue->size;
}

int queue_is_empty(queue_o *queue){
  ASSERT_PARAMETERS_NOT_NULL(queue);
  return queue->size == 0;
}

