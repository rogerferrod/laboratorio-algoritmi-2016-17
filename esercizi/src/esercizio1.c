#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/src/array.h"

#define ARRAY_CAPACITY 20
#define BUFFER_LENGHT  100

typedef struct {
  char *string;
  int field1;
} record;


static void array_print(array_o *array){
  size_t i;
  record *elem;
  elem = (record*)malloc(sizeof(record));
  for(i = 0; i < array_size(array); i++){
    elem = (record*)array_at(array, i);
    printf("array[%d] = {%s,%d}\n", i, elem->string, elem->field1);
  }
  return;
}

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


  array_o* array = array_new(ARRAY_CAPACITY);
  size_t buff_size = BUFFER_LENGHT;
  char *buffer;
  buffer = (char*)malloc(buff_size*(sizeof(char)));

  while(fgets(buffer,buff_size,file) != NULL){
    record* row = (record*)malloc(sizeof(record));
    char *string = strtok(buffer,",");
    char *integer = strtok(NULL,",");
    
    char *field0 = malloc((strlen(string)+1)*sizeof(char));  /* +1 di \0 */  
    strcpy(field0,string);    
    int field1 = atoi(integer);  

    row->string = field0;
    row->field1 = field1; /* no malloc? implicita */
    
    array_insert(array, row);

  }
  /*teoricamente dovrebbe aver fatto la free di string e integer */
  
  array_print(array);

  free(buffer);			 
  fclose(file);
  array_free(array);
}
