#default c compiler
CC = gcc
# Flags per il compilatore c
CFLAGS = -g -Wall -pedantic -Wno-padded -std=c99 -O3 -march=native
# Lista degli header files
C_INCLUDES = src/*.h
# Tutti i target vanno ricompilati se cambiano gli header o questo Makefile
C_COMMON_DEPS = $(C_INCLUDES) Makefile
JAVA_CLASS_PATH = .:resources/hamcrest-core-1.3.jar:resources/junit-4.12.jar
JAVA_COMPILE_PARAMS = -cp $(JAVA_CLASS_PATH) -d bin/ -Xlint:all -Xdiags:verbose -sourcepath .:src/
JAVA_RUN_PARAMS = -cp $(JAVA_CLASS_PATH):bin/


# Lista dei target da eseguire sempre
all: build

# compila (grazie alla dipendenza) i sorgenti (crea i binari e i file .class)
build: build_graph
build_all: build_es1 build_es2 build_es4
build_es1: build_array build_sort
build_es2: build_tree build_treeTest build_es2_jar
build_es2_jar:
	jar cf bin/Tree.jar -C src edu/unito/

build_es2: build_tree build_treeTest
build_es3: build_heap build_heapTest
build_es4: build_set
build_es5: build_graph

build_array: bin/array_tests
build_sort: bin/sort_tests
build_tree: src/edu/unito/tree/Tree.java
	javac $(JAVA_COMPILE_PARAMS) src/edu/unito/tree/Tree.java
build_treeTest: build_tree src/edu/unito/tree/TreeTests.java
	javac $(JAVA_COMPILE_PARAMS) src/edu/unito/tree/TreeTests.java
build_heap: src/edu/unito/heap/Heap.java
	javac $(JAVA_COMPILE_PARAMS) src/edu/unito/heap/Heap.java
build_heapTest: build_heap src/edu/unito/heap/HeapTests.java
	javac $(JAVA_COMPILE_PARAMS) src/edu/unito/heap/HeapTests.java
build_set: bin/set_tests
build_list: bin/list_tests
build_graph: bin/graph_tests
build_hash: bin/hash_tests

# compila e esegue i test
tests: tests_hash
tests_all: tests_es1 tests_es2 tests_es4
tests_es1: tests_array tests_sort
tests_es2: tests_tree
tests_es3: tests_heap
tests_es4: tests_unionfind
tests_es5: tests_graph

tests_array: build_array
	bin/array_tests
tests_sort: build_sort
	bin/sort_tests
tests_tree: build_treeTest
	java $(JAVA_RUN_PARAMS) org.junit.runner.JUnitCore edu.unito.tree.TreeTests
tests_heap: build_heapTest
	java $(JAVA_RUN_PARAMS) org.junit.runner.JUnitCore edu.unito.heap.HeapTests
tests_unionfind: build_set
	bin/set_tests
tests_list: build_list
	bin/list_tests
tests_graph: build_graph
	bin/graph_tests
tests_hash: build_hash
	bin/hash_tests


docs: docs_tree docs_heap
docs_tree: src/edu/unito/tree/*.java
	javadoc -d docs -author -private src/edu/unito/tree/Tree.java src/edu/unito/tree/TreeIterator.java
docs_heap: src/edu/unito/heap/*.java
	javadoc -d docs -author -private src/edu/unito/heap/Heap.java

# regola per compilare un .c in un .o
# viene applicata ogni volta che una dipendenza richiede di compilare un file in
#    `build` e con suffisso .o. Il simbolo % effettua pattern matching con quanto
#    compreso tra 'build/' e '.o', la stringa in questione viene quindi usata sul lato
#    destro della regola per indicare il file da compilare.
# Le variabili $< e $@ sono gestite automaticamente da `make` esse corrispondono:
#   $@ : l'intero target della regola (in questo caso: build/<nomefile>.o)
#   $< : la prima dipendenza della regola (in questo caso: src/<nomefile>.c)
build/%.o: src/%.c $(C_COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/array_tests: build/array_tests.o build/array.o build/unity.o $(C_COMMON_DEPS)
	$(CC) -o bin/array_tests  build/array_tests.o build/array.o build/unity.o

bin/sort: build/sort.o build/array.o $(C_COMMON_DEPS)
	$(CC) -o bin/sort build/sort.o build/array.o

bin/sort_tests: build/sort_tests.o build/sort.o build/array.o build/unity.o $(C_COMMON_DEPS)
	$(CC) -o bin/sort_tests build/sort_tests.o build/sort.o build/array.o build/unity.o

bin/set_tests: build/set_tests.o build/set.o build/unity.o $(C_COMMON_DEPS)
	$(CC) -o bin/set_tests build/set_tests.o build/set.o build/unity.o

bin/list_tests: build/list_tests.o build/list.o build/unity.o $(C_COMMON_DEPS)
	$(CC) -o bin/list_tests build/list_tests.o build/list.o build/unity.o

bin/graph_tests: build/graph_tests.o build/graph.o build/array.o build/list.o build/set.o build/unity.o $(C_COMMON_DEPS)
	$(CC) -o bin/graph_tests build/graph_tests.o build/graph.o build/array.o build/list.o build/set.o build/unity.o

bin/hash_tests: build/hash_tests.o build/hash.o build/array.o build/list.o build/unity.o $(C_COMMON_DEPS)
	$(CC) -o bin/hash_tests build/hash_tests.o build/hash.o build/array.o build/list.o build/unity.o



clean:
	rm -fr build/* bin/*
