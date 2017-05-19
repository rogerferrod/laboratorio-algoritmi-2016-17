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
#include "../../lib/src/graph.h"
#include "../../lib/src/hash.h"

#define MAX_VERTEX 1000000
#define BUFFER_LENGTH  100  //la linea più lunga del file è di 88 caratteri
#define TIMER_START(timer)  (timer = clock());
#define TIMER_STOP(timer)   (printf("Processor time used: %f s\n", \
            ((double) ((clock_t)clock() - timer)) / CLOCKS_PER_SEC));
/*
#define PRINT_RATE     0.125

#define FIELD1 4
#define FIELD2 5
#define FIELD3 6

#define ASCENDING  7
#define DESCENDING 8

#define I_SORT 1
#define S_SORT 2
#define Q_SORT 3

*/
/*
typedef struct {
    int id;
    char *field1;
    int field2;
    float field3;
} record;
*/

/*
int compare_ascending_field1(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return strcmp(first->field1, last->field1);
}

int compare_descending_field1(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return (-1)*strcmp(first->field1, last->field1);
}
*/

/*
static void array_print(array_o *array, float rate) {
  size_t i;
  record *elem;
  int delta;

  if (rate == 0){
    return;
  }

  if ((int)(array_size(array) * rate) == 0) {
    delta=1;
  } else {
    delta = (int) (rate * (float) array_size(array));
  }

  for (i = 0; i < array_size(array); i+=delta) {
    elem = (record *) array_at(array, i);
    printf("array[%d] = {%d,%s,%d,%f}\n", (int)i, elem->id, elem->field1, elem->field2, elem->field3);
  }

  i = array_size(array)-1;
  elem = (record *) array_at(array, i);
  printf("array[%d] = {%d,%s,%d,%f}\n", (int)i, elem->id, elem->field1, elem->field2, elem->field3);
  return;
}
*/

/*
static void memory_free(array_o *array){
  record *elem;
  size_t i;

  for (i = 0; i < array_size(array); ++i) {
    elem = (record *) array_at(array, i);
    free(elem->field1);
    free(elem);
  }

  array_free(array);
  return;
}
*/

/*
static record *record_load(char *buffer){
  int id;
  char *field1;
  int field2;
  float field3;

  record *row = (record *) malloc(sizeof(record));
  if (row == NULL) {
    fprintf(stderr, "Not enough memory for new record\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  char *raw_id = strtok(buffer, ",");
  char *raw_field1 = strtok(NULL, ",");
  char *raw_field2 = strtok(NULL, ",");
  char *raw_field3 = strtok(NULL, ",");

  id = atoi(raw_id);
  field1 = malloc((strlen(raw_field1) + 1)*sizeof(char));
  // +1 di \0

  if (field1 == NULL) {
    fprintf(stderr, "Not enough memory for new field1\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  strcpy(field1, raw_field1);
  field2 = atoi(raw_field2);
  field3 = atof(raw_field3);

  row->id = id;
  row->field1 = field1;
  row->field2 = field2;
  row->field3 = field3;

  return row;
}
*/

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

  hashtable_o * hashtable = hashtable_new(max_record_read, djb2a, compare_str);

  char **field1 = malloc(buff_size* sizeof(char*));
  char **field2 = malloc(buff_size* sizeof(char*));
  char **raw_field3 = malloc(buff_size* sizeof(char*));
  double *field3 = malloc(sizeof(double));

  count = 0;
  while (count < max_record_read && fgets(buffer, buff_size, file) != NULL) {
    *field1 = strtok(buffer, ",");
    *field2 = strtok(NULL, ",");
    *raw_field3 = strtok(NULL, ",");

    //*field3 = strtod(*raw_field3, NULL);
    *field3 = atof(*raw_field3);

    printf("_field1: %s\n", *field1);
    printf("_field2: %s\n", *field2);
    printf("_field3: %lf\n\n", *field3);

    graph_add(graph, *field1);
    graph_add(graph, *field2);
    graph_connect(graph, *field1, *field2, field3, NO_ORIENTED);

    hashtable_put(&hashtable, *field1, field3);
    hashtable_put(&hashtable, *field2, field3);
/*
    if (count % 50 == 0) {
      printf("%d - %s, %s, %s(%.12lf)\n", count, field1, field2, raw_field3, *field3);
    }
*/
    count++;
  }

  printf("Hashtable size: %ld\n", (unsigned long)hashtable_size(hashtable));
  printf("-------------------\n");
  iterator *iter = hashtable_iter_init(hashtable);

  void *key = malloc(buff_size*sizeof(char*));
  void *value = malloc(buff_size*sizeof(double*));

  size_t i = 0;
  while(hashtable_iter_hasNext(hashtable,iter)){
    hashtable_iter_next(hashtable, iter, &key, &value);
    printf("-%s, %lf\n", (char*)key, *(double*)value);
    if (++i > 10) break;
  }

  free(iter);

  printf("-------------------\n");

  hashtable_free(hashtable);
  free(buffer);
  fclose(file);
  return graph;
}

/*
static void array_sort(array_o *array, int algorithm, int field, int order){
  ArrayCompare compare_pnt;
  AlgSort sort_pnt;
  clock_t timer;

  switch(field){
    case FIELD1:
      fprintf(stdout, "field1 - ");
      compare_pnt = (order == ASCENDING)? compare_ascending_field1 : compare_descending_field1;
      break;
    case FIELD2:
      fprintf(stdout, "field2 - ");
      compare_pnt = (order == ASCENDING)? compare_ascending_field2 : compare_descending_field2;
      break;
    case FIELD3:
      fprintf(stdout, "field3 - ");
      compare_pnt = (order == ASCENDING)? compare_ascending_field3 : compare_descending_field3;
      break;
  }

  switch(algorithm){
    case I_SORT:
      fprintf(stdout, " insertion_sort\n");
      sort_pnt = insertion_sort;
      break;
    case S_SORT:
      fprintf(stdout, " selection_sort\n");
      sort_pnt = selection_sort;
      break;
    case Q_SORT:
      fprintf(stdout, " quicksort\n");
      sort_pnt = quick_sort;
      break;
  }

  // Sorting

  TIMER_START(timer);
  sort_pnt(array, compare_pnt);
  TIMER_STOP(timer);

  sleep(1);

  return;
}
*/

int main(int argc, char *argv[]) {
  graph_o *graph;
  int max_record_read;
//  int algorithm;
//  int field;
//  int order;
  clock_t timer;


  /* Default settings */
  max_record_read = -1;
//  algorithm = Q_SORT;
//  field = FIELD1;
//  order = ASCENDING;

  /* Parsing arguments */
  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  if (argc >= 3){
    max_record_read = atoi(argv[2]);
  }
/*
  if (argc >= 4) {
    if(strcmp(argv[3], "isort") == 0){algorithm = I_SORT;}
    else if(strcmp(argv[3], "ssort") == 0){algorithm = S_SORT;}
    else if(strcmp(argv[3], "qsort") == 0){algorithm = Q_SORT;}
  }
*/
/*
  if (argc >= 5) {
    if(strcmp(argv[4], "field1") == 0){field = FIELD1;}
    else if(strcmp(argv[4], "field2") == 0){field = FIELD2;}
    else if(strcmp(argv[4], "field3") == 0){field = FIELD3;}
  }
*/
/*
  if (argc >= 6) {
    if(strcmp(argv[5], "ascending") == 0){order = ASCENDING;}
    else if(strcmp(argv[5], "descending") == 0){order = DESCENDING;}
  }
*/

  /* Load array */
  fprintf(stdout, "graph_load\n");
  TIMER_START(timer);
  graph = graph_load(argv[1], max_record_read);
  TIMER_STOP(timer);

  TIMER_START(timer);
  fprintf(stdout, "graph_order: %u\n", (unsigned int) graph_order(graph));
  TIMER_STOP(timer);


/*
  TIMER_START(timer);
  fprintf(stdout, "graph_size: %u\n", (unsigned int) graph_size(graph));
  TIMER_STOP(timer);
*/
/*
  sleep(1);
*/
/*
  // Kruskal
  //kruskal(graph);
*/
/*
  //Print array
  //array_print(array, PRINT_RATE);
*/

  /* Free graph */
  TIMER_START(timer);
  graph_free(graph);
  TIMER_STOP(timer);

  return 0;
}
