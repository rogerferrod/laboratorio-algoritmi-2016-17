/*
 *  File: lib.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 11-04-2017
 *
 */



#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "lib.h"

/* Success or die malloc */
void* xmalloc(size_t size){
  void *ptr = malloc(size);
  if(ptr == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return ptr;  
}

void* xrealloc(void *pointer, size_t size){
  void *ptr = realloc(pointer, size);
  if(ptr == NULL){
    fprintf(stderr, "Not enough space for malloc\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }
  return ptr;  
}

