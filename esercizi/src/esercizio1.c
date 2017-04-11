#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../lib/src/array.h"
#include "../../lib/src/sort.h"

#define MAX_ARRAY_SIZE 20000000
#define BUFFER_LENGTH  100
#define PRINT_RATE     0.125

#define FIELD1 4
#define FIELD2 5
#define FIELD3 6

#define ASCENDING  7
#define DESCENDING 8

#define I_SORT 1
#define S_SORT 2
#define Q_SORT 3

#define TIMER_START(timer)  (timer = clock());
#define TIMER_STOP(timer)   (printf("Processor time used: %f s\n", \
            ((double) ((clock_t)clock() - timer)) / CLOCKS_PER_SEC));

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

int compare_ascending_field3(void *a, void *b) {  /* ATTENZIONE: uguale a field2 ? */
  record *first = (record *) a;
  record *last = (record *) b;
  return (first->field3 - last->field3);
}

int compare_descending_field3(void *a, void *b) {  /* ATTENZIONE: uguale a field2 ? */
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
}

static array_o *array_load(char *path, int record_read) {
  FILE *file;
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE); /* meglio NULL? */
  }

  array_o *array = array_new(MAX_ARRAY_SIZE);
  size_t buff_size = BUFFER_LENGTH;
  char *buffer;
  buffer = (char *) malloc(buff_size * (sizeof(char)));
  if  (buffer == NULL) {
    fprintf(stderr, "Not enough space for new buffer\n");
    errno = ENOMEM;
    exit(EXIT_FAILURE);
  }

  int count = 0;
  while (fgets(buffer, buff_size, file) != NULL && count < record_read) {
    record *row = (record *) malloc(sizeof(record));
    if (row == NULL) {
      fprintf(stderr, "Not enough space for new record\n");
      errno = ENOMEM;
      exit(EXIT_FAILURE);
    }
    char *raw_id = strtok(buffer, ",");
    char *raw_field1 = strtok(NULL, ",");
    char *raw_field2 = strtok(NULL, ",");
    char *raw_field3 = strtok(NULL, ",");

    int id = atoi(raw_id);
    char *field1 = malloc((strlen(raw_field1) + 1)*sizeof(char));  /* +1 di \0 */ /*controllare riuscita */
    if (field1 == NULL) {
      fprintf(stderr, "Not enough space for new field1\n");
      errno = ENOMEM;
      exit(EXIT_FAILURE);
    }
    strcpy(field1, raw_field1);
    int field2 = atoi(raw_field2);
    float field3 = atof(raw_field3);

    row->id = id;
    row->field1 = field1;
    row->field2 = field2;
    row->field3 = field3;

    array_insert(array, row);

    if (record_read != 0) /*ATTENZIONE: out of bound con 0 */
      count++;
  } /* potrebbe arrivare qui se la fgets fallisce (controllare errno?)*/
  
  free(buffer);
  fclose(file);
  return array;
}

int main(int argc, char *argv[]) {
  array_o *array;
  clock_t timer;
  int record_read;
  int algorithm;
  int field;
  int order;

  ArrayCompare compare_pnt;

  /* default settings */
  record_read = 0; /* ATTENZIONE */
  algorithm = Q_SORT;
  field = FIELD1;
  order = ASCENDING;
      
  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }
  
  if (argc >= 3){record_read = atoi(argv[2]);}  
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


  fprintf(stdout, "array_load\n");
  TIMER_START(timer);
  array = array_load(argv[1], record_read); /* ATTENZIONE: potrebbe resistuire array vuoto */
  TIMER_STOP(timer);
  fprintf(stdout, "array_size: %u\n", (unsigned int) array_size(array));

  sleep(1);

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
      TIMER_START(timer);
      insertion_sort(array, compare_pnt);
      TIMER_STOP(timer);
      break;
    case S_SORT:
      fprintf(stdout, " selection_sort\n");
      TIMER_START(timer);
      selection_sort(array, compare_pnt);
      TIMER_STOP(timer);
      break;
    case Q_SORT:
      fprintf(stdout, " quicksort\n");
      TIMER_START(timer);
      quick_sort(array, compare_pnt);
      TIMER_STOP(timer);
      break;
  }
  
  sleep(1);
  array_print(array, PRINT_RATE);
  
  memory_free(array);

  return 0;
}
