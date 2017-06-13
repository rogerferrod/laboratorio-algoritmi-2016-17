/*
 *  File: esercizio1.c
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 12-04-2017
 *
 */


/*
 * Exercise 1 application
 *
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../lib/src/lib.h"
#include "../../lib/src/array.h"
#include "../../lib/src/sort.h"

#define MAX_ARRAY_SIZE 20000000
#define BUFFER_LENGTH  100
#define PRINT_RATE     0.125    //12.5%

#define FIELD1 4
#define FIELD2 5
#define FIELD3 6

#define ASCENDING  7
#define DESCENDING 8

#define I_SORT 1
#define S_SORT 2
#define Q_SORT 3


typedef struct {
    int id;
    char *field1;
    int field2;
    float field3;
} record;


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

int compare_ascending_field2(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return first->field2 - last->field2;
}

int compare_descending_field2(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return last->field2 - first->field2;
}

int compare_ascending_field3(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return (first->field3 - last->field3);
}

int compare_descending_field3(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return (last->field3 - first->field3);
}

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

static record *record_load(char *buffer){
  int id;
  char *field1;
  int field2;
  float field3;

  record *row = (record *) xmalloc(sizeof(record));

  char *raw_id = strtok(buffer, ",");
  char *raw_field1 = strtok(NULL, ",");
  char *raw_field2 = strtok(NULL, ",");
  char *raw_field3 = strtok(NULL, ",");

  id = atoi(raw_id);
  field1 = xmalloc((strlen(raw_field1) + 1)*sizeof(char));  // +1 di '\0'

  strcpy(field1, raw_field1);
  field2 = atoi(raw_field2);
  field3 = atof(raw_field3);

  row->id = id;
  row->field1 = field1;
  row->field2 = field2;
  row->field3 = field3;

  return row;
}

static array_o *array_load(char *path, int max_record_read) {
  if (max_record_read < 0) {
    max_record_read = MAX_ARRAY_SIZE;
  }

  FILE *file;
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE);
  }

  array_o *array = array_new(max_record_read);
  size_t buff_size = BUFFER_LENGTH;
  char *buffer;
  int count;

  buffer = (char *) xmalloc(buff_size * (sizeof(char)));

  count = 0;
  while (count < max_record_read && fgets(buffer, buff_size, file) != NULL) {
    record *row;
    row = record_load(buffer);
    array_insert(array, row);

    count++;
  }

  free(buffer);
  fclose(file);
  return array;
}

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

  /* Sorting */
  TIMER_START(timer);
  sort_pnt(array, compare_pnt);
  TIMER_STOP(timer, "sorting array.");

  sleep(1);

  return;
}

int main(int argc, char *argv[]) {
  array_o *array;
  int max_record_read;
  int algorithm;
  int field;
  int order;
  clock_t timer;


  /* Default settings */
  max_record_read = -1;
  algorithm = Q_SORT;
  field = FIELD1;
  order = ASCENDING;

  /* Parsing arguments */
  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  if (argc >= 3){
    max_record_read = atoi(argv[2]);
  }
  if (argc >= 4) {
    if(strcmp(argv[3], "isort") == 0){algorithm = I_SORT;}
    else if(strcmp(argv[3], "ssort") == 0){algorithm = S_SORT;}
    else if(strcmp(argv[3], "qsort") == 0){algorithm = Q_SORT;}
  }
  if (argc >= 5) {
    if(strcmp(argv[4], "field1") == 0){field = FIELD1;}
    else if(strcmp(argv[4], "field2") == 0){field = FIELD2;}
    else if(strcmp(argv[4], "field3") == 0){field = FIELD3;}
  }
  if (argc >= 6) {
    if(strcmp(argv[5], "ascending") == 0){order = ASCENDING;}
    else if(strcmp(argv[5], "descending") == 0){order = DESCENDING;}
  }

  /* Load array */
  fprintf(stdout, "array_load\n");
  TIMER_START(timer);
  array = array_load(argv[1], max_record_read);
  TIMER_STOP(timer, "loading array.");
  fprintf(stdout, "array_size: %u\n", (unsigned int) array_size(array));

  sleep(1);

  /* Sort array */
  array_sort(array, algorithm, field, order);

  /* Print array */
  array_print(array, PRINT_RATE);

  /* Free array */
  memory_free(array);

  return 0;
}
