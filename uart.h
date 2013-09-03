/*
 * uart.h
 *
 *  Created on: 27/set/2012
 *      Author: Matteo Ragni
 */

#ifndef UART_H_
#define UART_H_

/*
 * Inclusioni
 *
 */

#include "msp430g2553.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "escapeVT100.h"

/*
 * Definizioni
 *
 */

// Commentare per disattivare eventuali sezioni di debug
#define __DEBUG_UART

// La prossima definizione contiene la lunghezza massima del buffer in
// ingresso
#define MAX_BUFF_VECTOR 40

// Le prossime due definizioni contengono quelli che sono i
// possibili delimitatori per la shell
#define DELIMITER1 '\n'
#define DELIMITER2 '\r'

// Definisce l'hostname
#define HOSTNAME "\n\rMSP430"
#define HOSTNAMEN 10
#define SH_PROMPT "> "
#define SH_PROMPTN 2
#define HOSTNAME_COLOR	E_GREEN
#define HOSTNAME_COLORN 	E_COLOR_N

// Le prossime definizioni contengono i possibili messaggi di errore
// che sono stati gestiti da questo modulo

#define ERR_UART_BUFFER_OVERFLOW	"\n\rInserimento troppo lungo! Max 50 caratteri...\n"
#define ERRN_UART_BUFFER_OVERFLOW 47

#define ERR_WDT_INT_UNHAND "\n\r[SYSINFO]: Rilevato interrupt WDT non gestito!\n"
#define ERRN_WDT_INT_UNHAND 50


// Abilitare il blink char nella console. Per alcuni terminali
// risulta essere già presente quindi se si vuole bloccare
// questa feature bisogna solo commentare la prossima linea
#define BLINK_CUR
#ifdef BLINK_CUR
	#define BLINKFREQ 27
#endif

/*
 * Prototipi
 *
 */

// Inizializza la comunicazione seriale
// All'interno di questa funzione troviamo
// la configurazione specifica della seriale
void UART_init();

// Invia un singolo byte sulla seriale.
// In: byte da inviare
void UART_SendByte(char);

// Riceve un byte attraverso la UART
// Ritorna il byte nel buffer
inline char UART_getByte();

// Scrive una stringa sulla seriale
// In: puntatore al vettore di caratteri,
//     la lunghezza della stringa da inviare
void UART_write(const char *, int);

// Legge un vettore di caratteri dalla seriale
// che termina con il carattere
// specificato
// In: ultimo carattere letto
//     carattere che termina il vettore
void UART_read(char,char);

// Azzera il buffer di lettura della seriale
void UART_ClearBuff();

// Genera il prompt della shell
void UART_printPrompt();

#endif /* UART_H_ */
