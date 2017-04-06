#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../lib/src/array.h"
#include "../../lib/src/sort.h"

#define ARRAY_CAPACITY 20000000
#define BUFFER_LENGTH  100

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


int compare_record_field1(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return strcmp(first->field1, last->field1);
}

int compare_record_field2(void *a, void *b) {
  record *first = (record *) a;
  record *last = (record *) b;
  return first->field2 - last->field2;
}

int compare_record_field3(void *a, void *b) {  /* ATTENZIONE: uguale a field2 ? */
  record *first = (record *) a;
  record *last = (record *) b;
  return (first->field3 - last->field3);
}

static void array_print(array_o *array, float rate) {
  size_t i;
  record *elem;
  int delta;
  delta = (int)(rate * (float)array_size(array));

  elem = (record *) malloc(sizeof(record));
  for (i = 0; i < array_size(array); i+=delta) {
    elem = (record *) array_at(array, i);
    printf("array[%d] = {%d,%s,%d,%f}\n", (int)i, elem->id, elem->field1, elem->field2, elem->field3);
  }
  i = array_size(array)-1;
  elem = (record *) array_at(array, i);
  printf("array[%d] = {%d,%s,%d,%f}\n", (int)i, elem->id, elem->field1, elem->field2, elem->field3);
  return;
}

static array_o *array_load(char *path, int record_read) {
  FILE *file;
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE); /* meglio NULL? */
  }

  array_o *array = array_new(ARRAY_CAPACITY);
  size_t buff_size = BUFFER_LENGTH;
  char *buffer;
  buffer = (char *) malloc(buff_size * (sizeof(char)));

  int count = 0;
  while (fgets(buffer, buff_size, file) != NULL && count < record_read) {
    record *row = (record *) malloc(sizeof(record));
    char *raw_id = strtok(buffer, ",");
    char *raw_field1 = strtok(NULL, ",");
    char *raw_field2 = strtok(NULL, ",");
    char *raw_field3 = strtok(NULL, ",");

    int id = atoi(raw_id);
    char *field1 = malloc((strlen(raw_field1) + 1) * sizeof(char));  /* +1 di \0 */
    strcpy(field1, raw_field1);
    int field2 = atoi(raw_field2);
    float field3 = atof(raw_field3);

    row->id = id; /* malloc implicita? */
    row->field1 = field1;
    row->field2 = field2;
    row->field3 = field3;

    array_insert(array, row);

    if (record_read != 0)
      count++;
  }
  /*teoricamente dovrebbe aver fatto la free dei raw */

  free(buffer);
  fclose(file);
  return array;
}

int main(int argc, char *argv[]) {
  /*
  char* s1 = "zuzzurellone";
  char* s2 = "prova";
  printf("%d\n",strcmp(s1, s2));
  record* r1 = malloc(sizeof(record));
  record* r2 = malloc(sizeof(record));
  r1->field1 = s1;
  r2->field1 = s2;
  r1->field2 = 5;
  r2->field2 = 3;
  printf("%d\n", compare_record_field1(r1, r2));
  printf("%d\n", compare_record_field2(r1, r2));
  */

  array_o *array;
  clock_t timer;
  int record_read;
  int algorithm;

  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  record_read = 0;
  if (argc >= 3) {
    record_read = atoi(argv[2]);
  }
  /* da mettere insieme i parametri */
  algorithm = Q_SORT;
  if (argc >= 4) {
    if(strcmp(argv[3], "isort") == 0){algorithm = I_SORT;}
    else if(strcmp(argv[3], "ssort") == 0){algorithm = S_SORT;}
    else if(strcmp(argv[3], "qsort") == 0){algorithm = Q_SORT;}
  }

  fprintf(stdout, "array_load\n");
  TIMER_START(timer);
  array = array_load(argv[1], record_read);
  TIMER_STOP(timer);
  fprintf(stdout, "array_size: %u\n", (unsigned int) array_size(array));

  sleep(1);
  
  switch(algorithm){
  case I_SORT:
    fprintf(stdout, "insertion_sort\n");
    TIMER_START(timer);
    insertion_sort(array, compare_record_field1);
    TIMER_STOP(timer);
    break;
  case S_SORT:
    fprintf(stdout, "selection_sort\n");
    TIMER_START(timer);
    selection_sort(array, compare_record_field1);
    TIMER_STOP(timer);
    break;
  case Q_SORT:
    fprintf(stdout, "quick_sort\n");
    TIMER_START(timer);
    quick_sort(array, compare_record_field1);
    TIMER_STOP(timer);
    break;
  default:
    fprintf(stderr, "error\n");
  }
  
  sleep(2);
  array_print(array, 0.125);

  array_free(array);

  return 0;
}
