/*
 *  File: esercizio1.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 18-05-2017
 *
 */


/*
 * Exercise 5 application
 * Riga nel file:
 *    citta,citta,distanza
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//#include "../../lib/src/array.h"
//#include "../../lib/src/sort.h"
#include "../../lib/src/hash.h"
#include "../../lib/src/graph.h"

#define MAX_VERTEX 1000000
#define BUFFER_LENGTH  100  //la linea più lunga del file è di 88 caratteri
#define TIMER_START(timer)  (timer = clock());
#define TIMER_STOP(timer)   (printf("Processor time used: %f s\n", \
            ((double) ((clock_t)clock() - timer)) / CLOCKS_PER_SEC));

typedef struct {
    char *field1;
    char *field2;
    double *field3;
} record;


static size_t djb2a(void* str) {
  return (size_t)strlen((char*)str);
  size_t hash = 5381;
  int c;
  char* my_str = (char*)str;
  while((c = *my_str)==1){
    (*my_str)++;
    hash = ((hash << 5) + hash) ^ c; /* hash * 33 ^ c */
  }
  return hash;
}

static int compare_str(void *x, void *y){
  return strcmp(x, y);
}

static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

static double* new_double(double value) {
  double* elem = (double*) malloc(sizeof(double));
  *elem = value;
  return elem;
}

static void memory_free(graph_o *graph){
  record *elem;
  size_t i;
  
  /*for (i = 0; i < array_size(array); ++i) {
    elem = (record *) array_at(array, i);
    free(elem->field1);
    free(elem);    
    }*/
  
  graph_free(graph);
  return;
}

static record *record_load(char *buffer){  
  char *field1;
  char *field2;
  double *field3;

  record *row = (record *) malloc(sizeof(record));
  if (row == NULL) {
    fprintf(stderr, "Not enough memory for new record\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  char *raw_field1 = strtok(buffer, ",");
  char *raw_field2 = strtok(NULL, ",");
  char *raw_field3 = strtok(NULL, ",");

  field1 = malloc((strlen(raw_field1) + 1)*sizeof(char));  /* +1 di \0 */
  field2 = malloc((strlen(raw_field2) + 1)*sizeof(char));  /* +1 di \0 */
  field3 = new_double(atof(raw_field3));

  strcpy(field1, raw_field1);
  strcpy(field2, raw_field2);

  row->field1 = field1;
  row->field2 = field2;
  row->field3 = field3;

  return row;
}

static graph_o *graph_load(char *path, int max_record_read) {
  if (max_record_read == -1) {
    max_record_read = MAX_VERTEX;
  }

  FILE *file;
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE);
  }

  graph_o *graph = graph_new(max_record_read, djb2a, compare_str);
  size_t buff_size = BUFFER_LENGTH;
  char *buffer;
  int count;

  buffer = (char *) malloc(buff_size * (sizeof(char)));
  if (buffer == NULL) {
    fprintf(stderr, "Not enough space for new buffer\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  count = 0;
  //  while (count < max_record_read && fgets(buffer, buff_size, file) != NULL) {
  while (count < 1000 && fgets(buffer, buff_size, file) != NULL) {
    record *row;
    row = record_load(buffer);
    printf("[%d]  %s -> %s (%lf)\n",count, row->field1, row->field2, *row->field3);

    if(!graph_contains_vertex(graph, row->field1)){
      graph_add(graph, row->field1);
    }
    if(!graph_contains_vertex(graph, row->field2)){
      graph_add(graph, row->field2);
    }
    //graph_connect(graph, row->field1, row->field2, row->field3, NO_DIRECTED);
    graph_connect(graph, row->field1, row->field2, new_double(0.5), NO_DIRECTED);
    
    count++;
  }

  
  free(buffer);
  fclose(file);
  return graph;
}


int main(int argc, char *argv[]) {
  graph_o *graph;
  int max_record_read;
  clock_t timer;


  /* Default settings */
  max_record_read = -1;

  /* Parsing arguments */
  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  if (argc >= 3){
    max_record_read = atoi(argv[2]);
  }

  /* Load array */
  fprintf(stdout, "graph_load\n");
  TIMER_START(timer);
  graph = graph_load(argv[1], max_record_read);
  TIMER_STOP(timer);
  fprintf(stdout, "graph_loaded\n");

  printf("graph != NULL? %d\n", graph != NULL);
  printf("order %d\n", graph_order(graph));
  printf("size %d\n", graph_size(graph));
  printf("weight %f\n", (float)graph_weight(graph));

  /* Free graph */
  memory_free(graph);

  return 0;
}
