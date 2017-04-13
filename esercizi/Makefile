CC = gcc
# Parametri per l'esercizio 1
COUNT = 1000
ALG = qsort
FIELD = field1
ORDER = ascending
# Flags per il compilatore
CFLAGS = -g -Wall -pedantic -Wno-padded -std=c99 -O3 -march=native
# Lista degli header files
INCLUDES = src/*.h

# Tutti i target vanno ricompilati se cambiano gli header o questo Makefile
COMMON_DEPS = $(INCLUDES) Makefile
COMMON_DEPS = Makefile

# Lista dei target da eseguire sempre
all: compile

compile: compile_es1

#compile es1 and its libs
compile_es1:
	$(MAKE) -C ../lib build_es1
	$(MAKE) bin/esercizio1

#  compila e esegue l'esercizio1
exec: exec_es1

exec_es1: compile_es1
	bin/esercizio1 data/records.csv ${COUNT} ${ALG} ${FIELD} ${ORDER}


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

bin/esercizio1: build/esercizio1.o $(COMMON_DEPS)
	$(CC) -o bin/esercizio1  build/esercizio1.o ../lib/build/array.o ../lib/build/sort.o

clean:
	rm -f build/* bin/*
