**Specifiche Tecniche**

**Agenzia immobiliare**

Il caso di studio deve simulare **una piccola parte delle funzionalità** di una piattaforma per
un’agenzia immobiliare. Le piattaforme consentono di far incontrare domanda e offerta di
vendita o affitto di case, appartamenti, case vacanza, esercizi commerciali, box auto, etc.

Il sistema deve prevedere dei **clienti** (descritti da caratteristiche come nome cliente, nome,
cognome, tipologia di cliente, budget, tipologia di immobile cercato, etc.), dei **professionisti**
(descritti da codice identificativo, nominativo, area di competenza, numero di case vendute,
totale venduto, etc.) e **degli immobili** (descritti codice identificativo, data di presa in carico,
tipologia di immobile, prezzo, località, etc.). L’elenco delle caratteristiche dei clienti, dei
professionisti e degli immobili è una scelta di progetto, ed è libera. Deve essere inoltre
possibile registrare le potenzialità dei professionisti su quali tipologie di contratti abbiano
concluso, con quale tipologia di cliente (famiglia, single, commerciante,...) riescono a
concludere più facilmente, etc.

Nello specifico bisogna implementare le seguenti funzionalità.

**(1) Caricamento da file dell’elenco dei clienti**

Caricare in memoria i clienti registrati al sistema. Il file deve essere esistente e può essere
gestito sia come file testuale che come file binario. In caso di file testuale, si suggerisce
l’uso del formato CSV. La funzionalità può essere implementata sia come procedura, che
come funzione booleana di caricamento.

**(2) Caricamento da file dell’elenco dei professionisti**
Caricare in memoria i professionisti disponibili sulla piattaforma. Il file deve essere
esistente e può essere gestito sia come file testuale che come file binario. In caso di file
testuale, si suggerisce l’uso del formato CSV. La funzionalità può essere implementata sia
come procedura, che come funzione booleana di caricamento.

**(3) Caricamento da file dell’elenco delle offerte di immobili**
Caricare in memoria le informazioni relative alle offerte sulla piattaforma. Il file deve
essere esistente e può essere gestito sia come file testuale che come file binario. In caso
di file testuale, si suggerisce l’uso del formato CSV. La funzionalità può essere
implementata sia come procedura, che come funzione booleana di caricamento.

**(4) Caricamento da file dell’elenco delle potenzialità dei professionisti**
Caricare in memoria le informazioni relative ai comportamenti dei professionisti (es. il
professionista1 riesce a vendere meglio case a famiglie). Il file deve essere esistente e
può essere gestito sia come file testuale che come file binario. In caso di file testuale, si
suggerisce l’uso del formato CSV. La funzionalità può essere implementata sia come
procedura, che come funzione booleana di caricamento.

**(5) Aggiunta-Modifica-Cancellazione dell’elenco degli immobili**

Dato l’insieme delle offerte di immobili presenti in memoria, permettere di aggiungere
nuove offerte, modificare le informazioni relative a quelle esistenti e cancellarle.
Ovviamente, una volta effettuate le modifiche la nuova versione del file dovrà essere
salvata su disco, nuovamente. La funzionalità può essere implementata sia come
procedura, che come funzione booleana.

**(6) Visualizzazione dei clienti e cancellazione dei clienti**

Il sistema deve, ad una richiesta dell’utente, visualizzare tutti i clienti e da quanto tempo
sono iscritti nel sistema. Se l’arco temporale è maggiore di una certa soglia chiedere
all’utente se si vuole eliminare il cliente, eliminarlo eventualmente. La definizione della
soglia è una scelta progettuale. Per ogni progetto visualizzare le informazioni utili
all’utente. Sarà valutata anche la chiarezza nella visualizzazione e la scelta delle
informazioni da visualizzare.

**(7) Suggerimento Immobile**

Dato un criterio di ricerca (tipologia di contratto, tipologia di immobile, tipologia di
utente, località, etc.), mostrare l’elenco degli immobili disponibili. Il numero di criteri di
ricerca da definire è a scelta. In generale la funzionalità deve prendere in input l’insieme
degli immobili, un criterio di ricerca e restituire come output i risultati della ricerca. Sarà
valutata la capacità di progettare funzioni di ricerca generiche e riusabili. La ricerca deve
preferibilmente lavorare anche sulle sottostringhe, non solo sul ‘matching’ esatto.

**(8) Visualizzazione risultati di agenzia**

Il sistema deve mostrare i risultati raggiunti dall’agenzia in un arco temporale deciso
dall’utente. Cosa mostrare e come mostrare (es. grafico a istogramma o valori espliciti,
etc. ) è una scelta progettuale. Sarà valutata la comunicabilità di quanto visualizzato.

**(9) Funzionalità di Ordinamento**

Mostrare all’utente i clienti/professionisti/immobili ordinati secondo uno o più criteri
scelti dal progettista. Sarà valutata la capacità di progettare funzioni di ordinamento
generiche e riusabili.

**(10) Gestione Funzionalità tramite Menu Utente**

Tutte le funzionalità devono essere gestite attraverso un menu iniziale che dia la
possibilità all’utente/amministratore di selezionare l’operazione da eseguire.