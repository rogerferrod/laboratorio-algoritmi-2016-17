# Laboratorio per il corso di Algoritmi e Strutture Dati

Il presente documento riporta i testi degli esercizi da svolgere e consegnare al fine di poter
sostenere la prova di laboratorio per il corso di Algoritmi e Strutture Dati, preceduti da alcune
indicazioni e suggerimenti relativi allo svolgimento degli stessi.


## Uso di ```Git```


Durante la scrittura del codice è richiesto di usare in modo appropriato il
sistema di versioning ```Git```. Questa richiesta implica quanto segue:

- il progetto di laboratorio va inizializzato "clonando" il repository del
  laboratorio come descritto nel file [Git](Git.md);
- come è prassi nei moderni ambienti di sviluppo, è richiesto di effettuare
  commit frequenti. L'ideale è un commit per ogni blocco di lavoro terminato
  (es. creazione e test di una nuova funzione, soluzione di un baco, creazione
    di una nuova interfaccia, ...);
- ogni membro del gruppo dovrebbe effettuare il commit delle modifiche che lo
  hanno visto come principale sviluppatore;
- al termine del lavoro si dovrà consegnare l'intero repository.

Il file [Git.md](Git.md) contiene un esempio di come usare Git per lo sviluppo degli
esercizi proposti per questo laboratorio.

**Nota importante**: su git dovrà essere caricato solamente il codice sorgente, in particolare nessun file dati dovrà essere oggetto di commit!

Si rammenta che la valutazione del progetto di laboratorio considererà anche l'uso adeguato di git da parte di ciascun membro del gruppo.

## Unit testing

Come indicato esplicitamente nei testi degli esercizi, il progetto di laboratorio comprende anche la definizione di opportune suite di unit tests.
Si rammenta, però, che il focus del laboratorio è l'implementazione di strutture dati e algoritmi. Relativamente agli unit-test sarà quindi sufficiente che gli studenti dimostrino di averne colto il senso e di saper realizzare una semplice suite di test sufficiente a coprire i casi più comuni (compresi, in particolare, i casi limite).

## Linguaggio in cui sviluppare il laboratorio

È lasciata libertà allo studente di implementare il codice usando Java o C.
Come potrete verificare gli esercizi chiedono di realizzare
strutture generiche. Seguono alcuni suggerimenti sul modo di realizzarle nei
due linguaggi accettati.

**Nota importante**: con "strutture dati generiche" si fa riferimento al fatto
che le strutture dati realizzate devono poter essere utilizzate con tipi di dato
non noti a tempo di compilazione. Sebbene in Java la soluzione più  in linea con
il moderno utilizzo del linguaggio richiederebbe la creazione di classi
parametriche, tutte le scelte implementative  (compresa la decisione di usare o
meno classi parametriche) sono lasciate agli studenti.

**Suggerimenti (C)**: Nel caso del C è necessario capire come meglio
approssimare l'idea di strutture generiche utilizzando quanto permesso dal
linguaggio. Un approccio comune è far sì che le funzioni che manipolano le
strutture dati prendano in input puntatori a void e utilizzino qualche funzione
fornita dall'utente per accedere alle componenti necessarie.  *Nota*: chi è in
grado di realizzare tipi di dato astratto tramite tipi opachi è incoraggiato a
procedere in questa direzione.

**Suggerimenti (Java)**: Nel caso si scelga di utilizzare Java è possibile (e
consigliato) usare gli ArrayList invece degli array nativi al fine di
semplificare l'implementazione delle strutture generiche.

## Uso di librerie esterne e/o native del linguaggio scelto

A parte gli ArrayList è vietato usare altre strutture dati *di base* offerte dal
linguaggio in uso (es. code, liste, stack, ...). È lecito (ma non obbligatorio)
avvalersi di strutture dati più complesse quando la loro realizzazione non è
richiesta da uno degli esercizi proposti. Ad esempio è lecito utilizzare una
libreria che implementa un dizionario (e.g., HashTable), ma non una che implementa gli alberi
(perché questi ultimi sono oggetto di un esercizio).

## Qualità dell'implementazione

È parte del mandato degli esercizi la realizzazione di codice di buona qualità.
Per "buona qualità" intendiamo codice ben modularizzato, ben commentato e
ben testato.

**Alcuni suggerimenti**:

- verificare che il codice sia suddiviso correttamente in package o moduli;
- aggiungere un commento, prima di una definizione, che spiega il funzionamento
  dell'oggetto definito. Evitare quando possibile di commentare direttamente
  il codice in sé (se il codice è ben scritto, i commenti in genere non servono);
- la lunghezza di un metodo/funzione è in genere un campanello di allarme:
  se essa cresce troppo, probabilmente è necessario rifattorizzare il codice
  spezzando la funzione in più parti. In linea di massima si può consigliare
  di intervenire quando la funzione cresce sopra le 30 righe (considerando anche
  commenti e spazi bianchi);
- sono accettabili commenti in italiano, sebbene siano preferibili in inglese;
- tutti i nomi (e.g., nomi di variabili, di metodi, di classi, etc.) devono
  essere significativi e in inglese;
- il codice deve essere correttamente indentato; impostare l'indentazione a
  2 caratteri (un'indentazione di 4 caratteri è ammessa ma scoraggiata) e
  impostare l'editor in modo che inserisca "soft tabs" (i.e., deve inserire il
  numero corretto di spazi invece che un carattere di tabulazione).
- per dare i nomi agli identificatori, seguire le convenzioni in uso per il
  linguaggio scelto:
  - Java: i nomi dei  package sono tutti in minuscolo senza separazione fra le
    parole; i nomi dei tipi (classi, interfacce, ecc.) iniziano con una lettera
    maiuscola e proseguono in camel case (es. TheClass), i nomi dei metodi e
    delle variabili iniziano con una lettera minuscola e proseguono in camel
    case (es. theMethod), i nomi delle costanti sono tutti in maiuscolo e in
    formato snake case (es. THE_CONSTANT);
  - C:  macro e costanti sono tutti in maiuscolo e in formato snake case (es.
    THE_MACRO, THE_CONSTANT); i nomi di tipo (e.g.  struct, typedefs, enums, ...)
    iniziano con una lettera maiuscola e proseguono in camel case (e.g., TheType,
    TheStruct); i nomi di funzione iniziano con una lettera minuscola e
    proseguono in snake case (e.g., the_function());
- i file vanno salvati in formato UTF8.

**Importante**:

Gli esercizi sono divisi in una parte di sviluppo di una struttura dati e/o di un algoritmo e una
(eventuale) parte in cui si esegue il codice sviluppato su un dataset dato. È importante tenere
presente che nello sviluppare la prima parte degli esercizi si deve assumere di stare sviluppando
una libreria generica intesa come fondamento di futuri programmi. Non è pertanto lecito fare
assunzioni semplificative legate alla particolare applicazione della libreria ai dati forniti. Ad
esempio non si può assumere che l'input di un algoritmo di ordinamento sia un vettore di un
particolare tipo di elementi o che i valori dei nodi di un grafo siano necessariamente di tipo
stringa.

È inoltre importante tenere presente che le scelte implementative che farete dovranno essere
giustificate in relazione alle nozioni presentate durante le lezioni in aula.



## Esercizio 1

Implementare i seguenti algoritmi di ordinamento:

- Insertion Sort
- Selection Sort
- Quick Sort

Ogni algoritmo va implementato in modo tale da poter essere utilizzato su
un generico tipo ```T```. L'implementazione degli algoritmi deve permettere di
specificare il criterio secondo cui ordinare i dati. *Suggerimento*: Usare
l'interfaccia java.util.Comparator (o, nel caso di una implementazione C,
un puntatore a funzione).

### Unit testing

Implementare gli unit-test degli algoritmi secondo le indicazioni
suggerite nel documento [Unit Testing](UnitTesting.md).

### Confronti

Il file `records.csv` che potete trovare seguendo il path
`/usr/NFS/Linux/labalgoritmi/datasets/` (in laboratorio von Neumann, selezionare
il disco Y) contiene 20 milioni di record da ordinare. Ogni record è descritto
su una riga e contiene i seguenti campi:

- id: (tipo intero) identificatore univoco del record;
- field1: (tipo stringa) contiene parole estratte dalla divina commedia,
  potete assumere che i valori non contengano spazi o virgole;
- field2: (tipo intero);
- field3: (tipo floating point);

Il formato è un CSV standard: i campi sono separati da virgole; i record sono
separati da "\n".

Usando ciascuno degli algoritmi implementati, si ordinino i *record* (non è sufficiente ordinare i
singoli campi) contenuti nel file `records.csv` in ordine non decrescente secondo i valori contenuti
nei tre campi "field" (cioè, per ogni algoritmo, è necessario ripetere l'ordinamento tre volte, una
volta per ciascun campo).

Si misurino i tempi di risposta e si crei una breve relazione in cui si riportano i risultati
ottenuti insieme a un loro commento. Nel caso l'ordinamento si  protragga per più di 10 minuti
potete interrompere l'esecuzione e riportare un fallimento dell'operazione. I risultati sono quelli
che vi sareste aspettati? Se sì, perché? Se no, fate delle ipotesi circa il motivo per cui gli
algoritmi non funzionano come vi aspettate, verificatele e riportate quanto scoperto nella
relazione.

**Nota**: il file `records.csv` non deve essere oggetto di commit su git!



## Esercizio 2

Si implementi la struttura dati Albero n-ario (realizzato con nodi aventi  puntatori al genitore,
al figlio sinistro e al fratello destro).

La struttura dati deve gestire tipi generici, consentire un numero qualunque e non noto a priori di
nodi e di figli per ogni nodo e consentire la costruzione di un albero tramite aggiunta di nodi.

Si implementino inoltre gli algoritmi le cui specifiche sono riportate di seguito (tenendo presente che ogni algoritmo manipola un albero n-ario):

- algoritmo che restituisce in output il massimo grado dei nodi dell'albero (il grado di un nodo
  è il numero dei suoi figli)
- algoritmo che verifica se l'albero è binario
- algoritmo che restituisce la dimensione dell'albero (cioè il numero di nodi)
- algoritmo che restituisce la profondità dell'albero (cioè la lunghezza del più lungo ramo dalla radice a una foglia)

- algoritmo che che costruisce un albero binario di ricerca bilanciato avente per nodi gli stessi valori dell'albero in input. Precisazioni:
  - l'algoritmo deve costruire l'albero binario usando la stessa struttura dati già implementata
    per gli alberi n-ari;
  - l'algoritmo deve costruire il nuovo albero "da zero" e non deve modificare l'albero in input;
  - l'algoritmo **deve costruire il nuovo albero in modo bilanciato "al volo"**, aggiungendo all'albero inizialmente vuoto i nodi in un ordine opportuno: non si devono quindi implementare
    algoritmi di bilanciamento di alberi.

**Suggerimento**: siccome l'implementazione richiesta per gli alberi n-ari (con n qualunque) è pensata per gli alberi non posizionali (cioè per i quali non è specificata la posizione dei figli di un nodo), mentre negli alberi binari di ricerca tale posizione è specificata (per ogni figlio di un nodo, è sempre noto se esso è il figlio sinistro o il figlio destro ) e, inoltre, in essi è possibile che un nodo abbia il solo figlio destro, si suggerisce il seguente semplice accorgimento per poter usare la struttura implementata anche per rappresentare alberi binari di ricerca:
definire un particolare valore fittizio (che qui chiamiamo *epsilon*) per i nodi dell'albero che rappresenti "l'assenza di nodo": in questo modo, la mancanza di un figlio per un nodo *n* può essere rappresentata inserendo nella struttura dati come figlio di *n* un nodo il cui valore è epsilon.

La struttura dati e gli algoritmi implementati dovranno essere utilizzati con i dati contenuti nei file `multywaytree_1.csv` e `multywaytree_2.csv`.

I file `multywaytree_1.csv` e `multywaytree_2.csv` che potete recuperare seguendo il path /usr/NFS/Linux/labalgoritmi/datasets/ (in laboratorio von Neumann, selezionare il disco Y) contengono ciascuno la serializzazione di un albero n-ario. Il formato è un CSV standard: i campi sono separati da virgole; i record (le righe) sono separati da `\n`. In ogni record, il primo campo rappresenta il nodo di cui si parla e i campi che seguono rappresentano i figli del nodo in questione (il primo campo della prima riga rappresenta la radice dell'albero), es le due righe seguenti:

```
N:0000,N:0001,N:0002
N:0001,N:0003
```

specificano che il nodo `N:0000` ha come figli i nodi `N:0001` e `N:0002`; inoltre, il nodo `N:0001` ha come figlio il nodo `N:0003`. In altri termini, esse codificano l'albero:

```
N:0000 -- N:0001 -- N:0003
       \_ N:0002
```


**Nota**: i file `multywaytree_1.csv` e `multywaytree_2.csv` non devono essere oggetto di commit su git!

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni
suggerite nel documento [Unit Testing](UnitTesting.md).



## Esercizio 3
Si implementino la versione iterativa e la versione ricorsiva di un
algoritmo che accetta in input un vettore e controlla se esso rappresenta un Max Heap.
Il tipo degli elementi del vettore non è noto a priori e il criterio di ordinamento
deve poter essere specificato dall'utente.

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni
suggerite nel documento [Unit Testing](UnitTesting.md).



## Esercizio 4

Si implementi la struttura dati UnionFind. La struttura dati deve permettere di inserire oggetti di
tipo generico e non prevedere un insieme iniziale finito di elementi.

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni
suggerite nel documento [Unit Testing](UnitTesting.md).

## Esercizio 5

Si implementi la struttura dati Grafo diretto in modo che sia ottimale per dati sparsi.

Si implementi una funzione che restituisce il peso del grafo. Si implementi l’algoritmo di
Kruskal per la determinazione di un minimo albero ricoprente di un grafo.
L’implementazione dell’algoritmo di Kruskal dovrà utilizzare la struttura dati Union Find
implementata nell’ esercizio precedente.

Calcolare il minimo albero ricoprente del grafo specificato nel file `italian_dist_graph.csv`.

Il file `italian_dist_graph.csv` che potete recuperare seguendo il path
`/usr/NFS/Linux/labalgoritmi/datasets/` (in laboratorio von Neumann, selezionare
il disco Y) contiene le distanze in metri tra varie località italiane e una frazione
delle località a loro più vicine. Il formato è un CSV standard: i campi sono
separati da virgole; i record sono separati da `\n`.

Ogni record contiene i seguenti dati:

- località 1: (tipo stringa) nome della località "sorgente". La stringa può
  contenere spazi, non può contenere virgole;
- località 2: (tipo stringa) nome della località "destinazione". La stringa
  può contenere spazi, non può contenere virgole;
- distanza: (tipo float) distanza in metri tra le due località.

*Note:*

- dovrete interpretare le informazioni presenti nelle righe del file come
  archi **non diretti** (i.e., probabilmente vorrete inserire nel vostro grafo
  sia l'arco di andata che quello di ritorno a fronte di ogni riga letta).
- il file è stato creato a partire da un dataset poco accurato. I dati
  riportati contengono inesattezze e imprecisioni.

**Nota**: il file `italian_dist_graph.csv` non deve essere oggetto di commit su git!**

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni
suggerite nel documento [Unit Testing](UnitTesting.md).

### Controlli

Una implementazione corretta dell’algoritmo di Kruskal, eseguita sui dati contenuti nel file
`italian_dist_graph.csv`, dovrebbe determinare un minimo albero ricoprente con 18.640 nodi, 18.637
archi (non orientati) e di peso complessivo pari a circa 89.939,913 Km.
<!---/DIEGO_NEW-->
