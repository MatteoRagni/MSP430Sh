/*
 * parser.h
 *
 * Created on: 3/ott/2012
 * 		Author: Matteo Ragni
 */

#ifndef PARSER_H_
#define PARSER_H_

/*
 * Inclusioni
 *
 */

#include "msp430g2553.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "help.h"

/*
 * Definizioni
 *
 */

#ifdef __DEBUG
#define __BEBUG_PARSER
#endif

#define MAX_TOKEN 3			// Massimo numero di token in una struttura
#define MAX_CMD_CHAR 40		// Lunghezza massima di una riga di comando
#define CHAR_CMD 10			// Massimo numero di caratteri di un token comando
#define CHAR_PIPE 25		// Massimo numero di caratteri di un token pipe
#define MAX_PIPE 2			// Elementi massimi in una pipe
#define tokenDel " \t"		// Delimitatore dei token
#define pipeDel "|"			// Delimitatori della pipe

// STRINGHE DI ERRORE DEL MODULO
#define TOO_PIPED_CMD "\n\r[PARSER]: Pipe troppo lunga!\n\r"
#define TOO_PIPED_CMDN 32
#define TOKEN_NULL "\n\r[PARSER]: Impossibile allocare memoria!\n\r"
#define TOKEN_NULLN 43
#define UNKNOW_CMD "\n\r[PARSER]: Comando non riconosciuto\n\r"
#define UNKNOW_CMDN 38

/*
 * Prototipi
 *
 */

// Struttura di suddivisione della pipe
typedef struct {
	char Token[MAX_PIPE][CHAR_PIPE];
	char nToken;
} PipedStruct;

// Struttura di suffivisione dei token
typedef struct {
	char Token[MAX_TOKEN][CHAR_CMD];
	char nToken;
} TokenStruct;

// Inizializza la struttura
// In: TokenStruct da inizializzare
void init_PipedStruct(PipedStruct* P);
void init_TokenStruct(TokenStruct* P);

// Salva valore nel prossimo elemento della struttura
// In: stringa da salvare
//     Struttura in cui salvare (usa indice interno)
// Out: risultato operazione
char SaveNext_Pipe(const char* input, PipedStruct* P);
char SaveNext_Token(const char* input, TokenStruct* P);

// Copia il contenuto della seconda TokenStruct nella
// prima TokenStruct
// In: TokenStruct in cui salvare
//     TokenStruct da cui prendere i dati
void copyTokenStruct (TokenStruct*, const TokenStruct*);

// Funzione che suddivide la comand line in token e provvede
// a chiamare il parser specifico
// In: Linea di commando
char parser(char* cmdLine);

// FUNZIONI DI PARSING
// Prende in ingresso una token struct e fornisce in
// uscita il puntatore a funzione di parsing specifica del
// comando
// In: TokenStruct contenente il comando
// Out: puntatore a funzione di parsing
void (*ParseCmd(TokenStruct TokenC))(TokenStruct[MAX_PIPE]);

//////// MODULARITA' //////////
// Funzioni specifiche di parsing di ogni comando che si
// aggiunge. Notare che le funzioni di parsing devono
// avere tutte la stessa dichiarazione
// In: Strutture suddivise dalle pipe
void parser_help(TokenStruct TokenC[MAX_PIPE]);
void parser_adc(TokenStruct TokenC[MAX_PIPE]);
void parser_timer(TokenStruct TokenC[MAX_PIPE]);

// EVENT HANDLER
// Se un modulo genera un evento (se non gestito con ISR)
// può essere gestito con una flag e un check da aggiungere
// in questa funzione
void eventHandler();

#endif
