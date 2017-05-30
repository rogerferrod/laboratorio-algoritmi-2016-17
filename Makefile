#Parametri per l'esercizio 1
COUNT = 1000		#anche per es 2 e 5
ALG = qsort
FIELD = field1
ORDER = ascending
#Parametri per l'esercizio 2
CSV = "data/multywaytree_1.csv"

default: es1 es2 es5

es1:
	$(MAKE) -C lib build_es1
	$(MAKE) -C esercizi bin/esercizio1 exec_es1 COUNT=${COUNT} ALG=${ALG} FIELD=${FIELD} ORDER=${ORDER}
es2:
	$(MAKE) -C lib build_es2
	$(MAKE) -C esercizi bin/esercizio2 exec_es2 CSV=${CSV} COUNT=${COUNT}
es5:
	$(MAKE) -C lib build_es5
	$(MAKE) -C esercizi bin/esercizio5 exec_es5 COUNT=${COUNT}

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