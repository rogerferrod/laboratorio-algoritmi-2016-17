/*
 *  File: esercizio1.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 14-05-2017
 *
 */


/*
 * Exercise 5 application
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "../../lib/src/lib.h"
#include "../../lib/src/graph.h"
#include "../../lib/src/kruskal.h"

#define MAX_VERTEX 1000000
#define BUFFER_LENGTH 100

typedef struct {
  char *field1;
  char *field2;
  double *field3;
} record;


static size_t hashJava(void* str) {
  char *val = (char*)str;
  size_t hash = 0, offset = 0;
  for(size_t i = 0; i < strlen(str); ++i){
    hash = ((hash << 5) - hash) + val[offset++];  /* hash*31 + val[offset] */
  }
  return hash;
}

static int compare_str(void *x, void *y){
  return strcmp((char*)x, (char*)y);
}

static double* new_double(double value) {
  double* elem = (double*) xmalloc(sizeof(double));
  *elem = value;
  return elem;
}

static void memory_free(graph_o *graph){
  if (graph_is_directed(graph)) {
    printf("directed\n");
    graphIterator* vIterator = graph_vertex_iter_init(graph);
    void* v1, * h;
    while (graph_vertex_iter_hasNext(graph, vIterator)) {
      graph_vertex_iter_next(graph, vIterator, &v1, &h);

      graphIterator* eIter = graph_edge_iter_init(graph, v1);
      void* v2;
      double* w;
      while (graph_edge_iter_hasNext(graph, v1, eIter)) {
        graph_edge_iter_next(graph, v1, eIter, &v2, &w);
        free(w);
      }
      free(eIter);
    }
    free(vIterator);
  }
  graph_free(graph);
  return;
}

static record *record_load(char *buffer){
  char *field1;
  char *field2;
  double *field3;

  record *row = (record *) xmalloc(sizeof(record));
  
  char *raw_field1 = strtok(buffer, ",");
  char *raw_field2 = strtok(NULL, ",");
  char *raw_field3 = strtok(NULL, ",");

  field1 = xmalloc((strlen(raw_field1) + 1)*sizeof(char));  /* +1 di \0 */
  strcpy(field1, raw_field1);

  field2 = xmalloc((strlen(raw_field2) + 1)*sizeof(char));  /* +1 di \0 */
  strcpy(field2, raw_field2);

  field3 = new_double(atof(raw_field3));

  row->field1 = field1;
  row->field2 = field2;
  row->field3 = field3;

  return row;
}

static graph_o *graph_load(char *path, int max_record_read) {
  if (max_record_read < 0 || max_record_read > MAX_VERTEX) {
    max_record_read = MAX_VERTEX;
  }

  FILE *file;
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE);
  }

  graph_o *graph = graph_new(max_record_read, hashJava, compare_str);
  size_t buff_size = BUFFER_LENGTH;
  char *buffer;
  int count;

  buffer = (char *) xmalloc(buff_size * (sizeof(char)));
  
  count = 0;
  while (count < max_record_read && fgets(buffer, buff_size, file) != NULL) {
    record *row;
    row = record_load(buffer);

    if(!graph_contains_vertex(graph, row->field1)){
      graph_add(graph, row->field1);
    }

    if(!graph_contains_vertex(graph, row->field2)){
      graph_add(graph, row->field2);
    }

    graph_connect(graph, row->field1, row->field2, row->field3, NO_DIRECTED);

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

  fprintf(stdout, "\nkruskal...\n");
  TIMER_START(timer);
  graph_o *min = kruskal(graph);
  TIMER_STOP(timer, "kruskal");

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
  memory_free(graph);
  memory_free(min);

  return 0;
}
