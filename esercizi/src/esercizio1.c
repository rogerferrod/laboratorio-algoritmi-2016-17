#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../lib/src/array.h"

#define ARRAY_CAPACITY 20000000
#define BUFFER_LENGHT  100

#define TIMER_START(timer)  (timer = clock());
#define TIMER_STOP(timer)   (printf("Processor time used: %f s\n", \
				    ((double) ((clock_t)clock() - timer)) / CLOCKS_PER_SEC));
  
typedef struct {
  int id;
  char *field1;
  int field2;
  float field3;
} record;


static void array_print(array_o *array){
  size_t i;
  record *elem;
  elem = (record*)malloc(sizeof(record));
  for(i = 0; i < array_size(array); i++){
    elem = (record*)array_at(array, i);
    printf("array[%d] = {%d,%s,%d,%f}\n", (int)i, elem->id, elem->field1, elem->field2, elem->field3);
  }
  return;
}

static array_o* array_load(char *path){
  FILE* file;
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "No such file or directory\n");
    errno = ENOENT;
    exit(EXIT_FAILURE); /* meglio NULL? */
  }
 
  array_o* array = array_new(ARRAY_CAPACITY);
  size_t buff_size = BUFFER_LENGHT;
  char *buffer;
  buffer = (char*)malloc(buff_size*(sizeof(char)));

  while(fgets(buffer,buff_size,file) != NULL){
    record* row = (record*)malloc(sizeof(record));
    char *raw_id = strtok(buffer,",");
    char *raw_field1 = strtok(NULL,",");
    char *raw_field2 = strtok(NULL,",");
    char *raw_field3 = strtok(NULL,",");
    
    int id = atoi(raw_id);
    char *field1 = malloc((strlen(raw_field1)+1)*sizeof(char));  /* +1 di \0 */  
    strcpy(field1,raw_field1);    
    int field2 = atoi(raw_field2);
    float field3 = atof(raw_field3);

    row->id = id; /* malloc implicita? */
    row->field1 = field1;
    row->field2 = field2;
    row->field3 = field3;
    
    array_insert(array, row);
  }
  /*teoricamente dovrebbe aver fatto la free dei raw */

  free(buffer);			 
  fclose(file);
  return array;
}

int main(int argc, char* argv[]) {
  array_o* array;
  clock_t timer;

  if (argc < 2) {
    fprintf(stderr, "No such argument\n");
    errno = EINVAL;
    exit(EXIT_FAILURE);
  }

  
  TIMER_START(timer);
  array = array_load(argv[1]);
  TIMER_STOP(timer);

  sleep(1);
  
  TIMER_START(timer);
  array_print(array);
  TIMER_STOP(timer);
  
  array_free(array);

  return 0;
}
