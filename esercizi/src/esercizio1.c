#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/src/array.h"

typedef struct {
    int* id;
    char* field1;
    int* field2;
    float* field3;
} record;

static int* new_int(int value) {
  int* elem = (int*) malloc(sizeof(int));
  *elem = value;
  return elem;
}

/*
static float* new_float(float value) {
  float* elem = (float*) malloc(sizeof(float));
  *elem = value;
  return elem;
}
*/

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  FILE* file;
  file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE);
  }

/*
  int id, field2;
  char field1[50];
  float field3;
*/
  char* field1;
  field1 = (char*)malloc(sizeof(char)*50);
  int field2;

//  array_o* array = array_new(20000000);
  array_o* array = array_new(20);
  record* row = (record*)malloc(sizeof(record));

//  while (fscanf(file, "%d,%s,%d,%f,", &id, field1, &field2, &field3)!=EOF){
  while (fscanf(file, "%s,%d", field1, &field2)!=EOF){
/*
    row->id = new_int(id);
    row->field1 = strdup(field1);
    row->field2 = new_int(field2);
    row->field3 = new_float(field3);
*/
    row->field1 = strdup(field1);
    row->field2 = new_int(field2);
    array_insert(array, row);
  }
  fclose(file);

  array_free(array);
  free(row);
}