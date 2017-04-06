#default
CC = gcc

# lista dei target da eseguire sempre
all: tests

# compila (grazie alla dipendenza)
build: bin/array_tests bin/sort_tests

# compila (grazie alla dipendenza) e esegue i test
tests: build
	bin/array_tests
	bin/sort_tests

# Flags per il compilatore -- su gcc -Weverything non esiste
#    sostituire con -Wall -Wpedantic
CFLAGS = -g -Wall -pedantic -Wno-padded -std=c99 -O3 -march=native

# Lista degli header files
INCLUDES = src/*.h

# tutti i target vanno ricompilati se cambiano gli header o
# questo Makefile
COMMON_DEPS = $(INCLUDES) Makefile

# regola per compilare un .c in un .o
# viene applicata ogni volta che una dipendenza richiede di compilare un file in
#    `build` e con suffisso .o. Il simbolo % effettua pattern matching con quanto
#    compreso tra 'build/' e '.o', la stringa in questione viene quindi usata sul lato
#    destro della regola per indicare il file da compilare.
# Le variabili $< e $@ sono gestite automaticamente da `make` esse corrispondono:
#   $@ : l'intero target della regola (in questo caso: build/<nomefile>.o)
#   $< : la prima dipendenza della regola (in questo caso: src/<nomefile>.c)
build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/array: build/array.o build/array_main.o $(COMMON_DEPS)
	$(CC) -o bin/array build/array.o build/array_main.o

bin/array_tests: build/array_tests.o build/array.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/array_tests  build/array_tests.o build/array.o build/unity.o

bin/sort: build/sort.o build/array.o $(COMMON_DEPS)
	$(CC) -o bin/sort build/sort.o build/array.o

bin/sort_tests: build/sort_tests.o build/sort.o build/array.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/sort_tests build/sort_tests.o build/sort.o build/array.o build/unity.o

clean:
	rm -f build/* bin/*
