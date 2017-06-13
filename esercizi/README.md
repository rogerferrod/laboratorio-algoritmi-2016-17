# Esercizio 1

Implementazione dei seguenti algoritmi di ordinamento:
- Insertion Sort
- Selection Sort
- Quick Sort

#### Sintassi
```
./esercizio1 path count alg field order
```
- path: percorso da cui leggere il file
- count: numero di righe da leggere dal file
- alg: algoritmo da usare (qsort, ssort, isort)
- field: campo secondo cui ordinare (field1, field2, field3)
- order: ordine di ordinamento (ascending, descending)

#### Makefile
Compilazione & Esecuzione
```
make es1 SRC=path COUNT=count ALG=alg FIELD=field ORDER=order
```
- path: percorso da cui leggere il file, assoluto o relativo da esercizi/ (default: data/records.csv) 
- count: numero di righe da leggere dal file (se negativo allora tutte) (default: 1000)
- alg: algoritmo da usare (qsort, ssort, isort) (default: qsort)
- field: campo secondo cui ordinare (field1, field2, field3) (default: field1)
- order: ordine di ordinamento (ascending, descending) (default: ascending)


# Esercizio 2

Implementazione della struttura dati Albero n-ario (realizzato con nodi aventi  puntatori al genitore, al figlio sinistro e al fratello destro).\
Implementazione dei seguenti algoritmi:
- calcolo del massimo grado dei nodi dell'albero
- verifica se l'albero è binario
- calcolo della dimensione dell'albero
- calcolo della profondità dell'albero
- costruzione di un albero binario di ricerca bilanciato avente per nodi gli stessi valori dell'albero in input

#### Sintassi
```
./esercizio2 path count
```
- path: percorso da cui leggere il file
- count: numero di righe da leggere dal file

#### Makefile
Compilazione & Esecuzione
```
make es2 SRC=path COUNT=count
```
- path: percorso da cui leggere il file, assoluto o relativo da esercizi/ (default: data/multywaytree_1.csv) 
- count: numero di righe da leggere dal file (se negativo allora tutte) (default: 1000)


# Esercizio 5

Implementazione della struttura dati Grafo diretto, ottimale per dati sparsi.\
Implementazione di una funzione che restituisce il peso del grafo.\
Implementazione dell’algoritmo di Kruskal.

#### Sintassi
```
./esercizio5 path count 
```
- path: percorso da cui leggere il file
- count: numero di righe da leggere dal file

#### Makefile
Compilazione & Esecuzione
```
make es5 SRC=path COUNT=count
```
- path: percorso da cui leggere il file, assoluto o relativo da esercizi/ (default: data/italian_dist_graph.csv) 
- count: numero di righe da leggere dal file (se negativo allora tutte) (default: 1000)


# Others
```
make all
```
Compilazionedi tutti gli esercizi con i parametri di default

```
make compile_esX
```
Compilazione dell'esercizio X

```
make exec_esX
```
Esecuzione dell'esercizio X

# Authors

* **Riccardo Ferrero Regis** - *821770* 
* **Roger Ferrod** - *813766* 
* **Luca Chironna** - *811890* 
