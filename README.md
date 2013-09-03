MSP430Sh
--------

``Ragni Matteo :: 156994 :: Embedded Systems``

Due Date: ``08 Ottobre 2012``

### Obbiettivi ###

##### Implementare una shell per MSP430 #####
La shell deve avere il prompt e il cursore lampeggiante. La shell fornisce una funzione di help che permette
di avere un elenco dei comandi disponibili. ``help [nome comando]`` deve fornire una spiegazione del comando.
##### Implementare un comando per il modulo timer #####
Il timer deve poter essere impostato per funzionare a singolo evento o periodicamente, secondo un intervallo
espresso in millisecondi
##### Implementare un comando per il modulo adc #####
Il comando legge il canale specificato e restituisce la lettura in forma binaria. Il canale ``11``, dedicato 
al sensore di temperatura, fornisce la temperatura in gradi centigradi.
##### Implementare il comando pipe #####
Il comando pipe ``|`` reindirizza, se disponibile, l'output del comando di sinistra al comando a destra.
Ad esempio ``timer on 1000 | adc 11`` converte il segnale sul canale ``11`` passato un secondo.
	
### Note ###

La implementazione di un eventuale modulo nuovo si basa sulla seguente metodologia:

  * Implementare i metodi del modulo o del task come libreria statica, includendo la libreria
    ``uart.h`` per avere a disposizione i metodi per scrivere sulla console (``UART_write``).

  * Implementare una funzione di esecuzione del task principale del modulo

  * Implementare una funzione di parsing all'interno della libreria "parser". Includere i metodi
    del modulo all'interno di ``parser.h``. La nuova funzione di parsing deve avere dichiarazione:
    ``void parser_modulo(TokenStruct[MAX_PIPE]``);
    Inserire mediante ``#define`` eventuali messaggi di errore dove si implementa la funzione di parsing
 
  * Inserire una nuova riga con il puntatore alla funzione ``parser_modulo`` nella funzione ``parserCmd``
 
  * Inserire la spiegazione dell'uso del modulo all'interno della libreria help
 
  * Se si vogliono utilizzare eventuali eventi si possono inserire le funzioni apposite in una funzione
    ``modulo_event``, che viene poi richiamato nella funzione ``eventHandler`` del parser

Se il nuovo modulo fa uso di interrupt, ricordarsi di eliminare le ISR necessarie dalla libreria ``isr_hdl``.
Se il nuovo modulo ha più di due opzioni si può aumentare la dimensione del numero di token nella struct 
