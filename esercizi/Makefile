CC = gcc
# Parametri per l'esercizio 1
COUNT = 1000	# Parametro anche per l'esercizio 2 e il 5
ALG = qsort
FIELD = field1
ORDER = ascending
# Parametri per l'esercizio 2
CSV = "data/multywaytree_1.csv"
# Flags per il compilatore
CFLAGS = -g -Wall -pedantic -Wno-padded -std=c99 -O3 -march=native
# Lista degli header files
INCLUDES = src/*.h

# Tutti i target vanno ricompilati se cambiano gli header o questo Makefile
#COMMON_DEPS = $(INCLUDES) Makefile
COMMON_DEPS = Makefile
JAVA_COMPILE_PARAMS = -d bin/ -Xlint:all -Xdiags:verbose -cp .:../lib/bin/Tree.jar
JAVA_RUN_PARAMS = -cp bin:../lib/bin/Tree.jar


# Lista dei target da eseguire sempre
all: compile_all

compile: compile_es5
compile_all: compile_es1 compile_es2 compile_es5

#compile esN and its libs
compile_es1:
	$(MAKE) -C ../lib build_es1
	$(MAKE) bin/esercizio1

compile_es2:
	$(MAKE) -C ../lib build_es2
	javac ${JAVA_COMPILE_PARAMS} src/esercizio2.java

compile_es5:
	$(MAKE) -C ../lib build_es5
	$(MAKE) bin/esercizio5


#exec: exec_es5
#esegue l'esercizio n
exec_es1: #compile_es1
	bin/esercizio1 data/records.csv ${COUNT} ${ALG} ${FIELD} ${ORDER}
exec_es2: #compile_es2
	java ${JAVA_RUN_PARAMS} esercizio2 ${CSV} ${COUNT}
exec_es5: #compile_es5
	bin/esercizio5 data/italian_dist_graph.csv ${COUNT}

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

bin/esercizio1: src/esercizio1.c build/esercizio1.o $(COMMON_DEPS)
	$(CC) -o bin/esercizio1 build/esercizio1.o ../lib/build/array.o ../lib/build/sort.o ../lib/build/lib.o

bin/esercizio2: src/esercizio2.java
	javac $(JAVA_COMPILE_PARAMS) src/esercizio2.java

bin/esercizio5: src/esercizio5.c build/esercizio5.o $(COMMON_DEPS)
	$(CC) -o bin/esercizio5 build/esercizio5.o ../lib/build/kruskal.o ../lib/build/set.o ../lib/build/graph.o ../lib/build/hash.o ../lib/build/list.o ../lib/build/array.o ../lib/build/sort.o ../lib/build/lib.o

clean:
	rm -fr build/* bin/*
