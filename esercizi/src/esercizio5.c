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
#include <unistd.h>
//#include "../../lib/src/array.h"
//#include "../../lib/src/sort.h"
//#include "../../lib/src/hash.h"
#include "../../lib/src/graph.h"
#include "../../lib/src/kruskal.h"
#include "../../lib/src/lib.h"

#define MAX_VERTEX 1000000
#define BUFFER_LENGTH  100  //la linea più lunga del file è di 88 caratteri

typedef struct {
    char *field1;
    char *field2;
    double *field3;
} record;


static size_t djb2a(void* str) {
  return (size_t)strlen((char*)str);
/*
  size_t hash = 5381;
  int c;
  char* my_str = (char*)str;
  while((c = *my_str)==1){
    (*my_str)++;
    hash = ((hash << 5) + hash) ^ c; // hash * 33 ^ c
  }
  return hash;
*/
}

static int compare_str(void *x, void *y){
  return strcmp((char*)x, (char*)y);
}
/*
static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}
*/
static double* new_double(double value) {
  double* elem = (double*) malloc(sizeof(double));
  *elem = value;
  return elem;
}
/*
static char** new_string(char* value) {
  char** elem = (char**)malloc(sizeof(char*)*(strlen(value)+1));
  strcpy(*elem, value);
  return elem;
}
*/
static void memory_free(graph_o *graph){
//  record *elem;
//  size_t i;
  
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
  strcpy(field1, raw_field1);

  field2 = malloc((strlen(raw_field2) + 1)*sizeof(char));  /* +1 di \0 */
  strcpy(field2, raw_field2);

  field3 = new_double(atof(raw_field3));

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
  while (count < max_record_read && fgets(buffer, buff_size, file) != NULL) {
  //while (count < 10 && fgets(buffer, buff_size, file) != NULL) {
    record *row;
    row = record_load(buffer);
    //printf("[%d]  %s -> %s (%lf)-------------\n", count, row->field1, row->field2, *row->field3);

    void *k1 = graph_contains_vertex(graph, row->field1);
    //printf("[%d] k1 == NULL ? %d\n", count, k1 == NULL);
    if (k1 == NULL || graph_get_key_compare(graph)(k1, row->field1) != 0) {
//    if(!graph_contains_vertex(graph, row->field1)){
      //printf("[%d]  - graph NOT contains_vertex %s\n", count, row->field1);
      graph_add(graph, row->field1);
      //printf("[%d]  - graph added %s\n", count, row->field1);
    } else {
      //printf("[%d]  - graph contains_vertex %s\n", count, row->field1);
    }

    void *k2 = graph_contains_vertex(graph, row->field2);
    //printf("[%d] k2 == NULL ? %d\n", count, k2 == NULL);
    if (k2 == NULL || graph_get_key_compare(graph)(k2, row->field2) != 0) {
//    if(!graph_contains_vertex(graph, row->field2)){
      //printf("[%d]  - graph NOT contains_vertex %s\n", count, row->field2);
      graph_add(graph, row->field2);
      //printf("[%d]  - graph added %s\n", count, row->field2);
    } else {
      //printf("[%d]  - graph contains_vertex %s\n", count, row->field2);
    }

    graph_connect(graph, row->field1, row->field2, row->field3, NO_DIRECTED);
    //graph_connect(graph, row->field1, row->field2, new_double(0.5), NO_DIRECTED);
    
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
  fprintf(stdout, "graph loading...\n");
  TIMER_START(timer);
  graph = graph_load(argv[1], max_record_read);
  TIMER_STOP(timer, "graph load");

  //printf("graph != NULL? %d\n", graph != NULL);
  fprintf(stdout, "calculating graph order & size...\n");
  TIMER_START(timer);
  size_t g_order = graph_order(graph);
  size_t g_size = graph_size(graph);
  TIMER_STOP(timer, "graph order & size");
  printf("graph: order = %ld - size = %ld\n", (unsigned long)g_order, (unsigned long)g_size);

  fprintf(stdout, "calculating graph weight...\n");
  TIMER_START(timer);
  double g_weight = graph_weight(graph);
  TIMER_STOP(timer, "graph weight");
  printf("graph: weight = %lf\n", g_weight);

/*
  graphIterator *vIter = graph_vertex_iter_init(graph);
  void *elem, *adj;
  while(graph_vertex_iter_hasNext(graph, vIter)) {
    graph_vertex_iter_next(graph, vIter, &elem, &adj);
    printf("%s\n", (char*)elem);
  }
  free(vIter);
*/

  graph_o *min = kruskal(graph);

  fprintf(stdout, "calculation kruskal graph order & size...\n");
  TIMER_START(timer);
  size_t k_order = graph_order(min);
  size_t k_size = graph_size(min);
  TIMER_STOP(timer, "kruskal graph order & size");
  printf("kruskal: order = %ld - size = %ld\n", (unsigned long)k_order, (unsigned long)k_size);

  fprintf(stdout, "calculating kruskal graph weight...\n");
  TIMER_START(timer);
  double k_weight = graph_weight(min);
  TIMER_STOP(timer, "kruskal graph weight");
  printf("kruskal: weight = %lf\n", k_weight);

  /* Free graph */
  TIMER_START(timer);
  memory_free(graph);
  TIMER_STOP(timer, "memory free graph");

  TIMER_START(timer);
  memory_free(min);
  TIMER_STOP(timer, "memory free kruskal graph");

  return 0;
}
