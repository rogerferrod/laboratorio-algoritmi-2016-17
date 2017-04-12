#default
CC = gcc

# lista dei target da eseguire sempre
all: build

# compila (grazie alla dipendenza)
build: build_array build_sort

build_array: bin/array_tests
build_sort: bin/sort_tests
build_tree: src/edu/unito/tree/Tree.java
	javac -d bin/ -cp .:resources/hamcrest-core-1.3.jar:resources/junit-4.12.jar src/edu/unito/tree/Tree.java
build_treeTest: build_tree src/edu/unito/tree/TreeTests.java
	javac -d bin/ -cp .:resources/hamcrest-core-1.3.jar:resources/junit-4.12.jar -sourcepath src/ src/edu/unito/tree/TreeTests.java

# compila (grazie alla dipendenza) e esegue i test
tests: tests_array tests_sort

tests_array: build_array
	bin/array_tests
tests_sort: build_sort
	bin/sort_tests
tests_tree: build_treeTest
	java -cp .:resources/hamcrest-core-1.3.jar:resources/junit-4.12.jar:bin/ org.junit.runner.JUnitCore edu.unito.tree.TreeTests

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
	rm -fr build/* bin/*
