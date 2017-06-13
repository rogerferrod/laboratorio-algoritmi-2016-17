#Parametri per l'esercizio 1
#COUNT anche per es 2 e 5
COUNT = 1000
ALG = qsort
FIELD = field1
ORDER = ascending
#Parametri per l'esercizio 2
SRC :=


default: all
all: es1 es2 es5

es1: SRC := data/records.csv
es1:
	$(MAKE) -C lib build_es1
	$(MAKE) -C esercizi bin/esercizio1
	$(MAKE) -C esercizi exec_es1 SRC=${SRC} COUNT=${COUNT} ALG=${ALG} FIELD=${FIELD} ORDER=${ORDER}
es2: SRC := data/multywaytree_1.csv
es2:
	$(MAKE) -C lib build_es2
	$(MAKE) -C esercizi bin/esercizio2
	$(MAKE) -C esercizi exec_es2 SRC=${SRC} COUNT=${COUNT}
es5: SRC := data/italian_dist_graph.csv
es5:
	$(MAKE) -C lib build_es5
	$(MAKE) -C esercizi bin/esercizio5
	$(MAKE) -C esercizi exec_es5 SRC=${SRC} COUNT=${COUNT}

test_all:
	$(MAKE) -C lib tests_all
test_es1:
	$(MAKE) -C lib tests_es1
test_es2:
	$(MAKE) -C lib tests_es2
test_es3:
	$(MAKE) -C lib tests_es3
test_es4:
	$(MAKE) -C lib tests_es4
test_es5:
	$(MAKE) -C lib tests_es5



clean:
	$(MAKE) -C lib clean
	$(MAKE) -C esercizi clean