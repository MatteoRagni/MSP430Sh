/*
 * help.h
 *
 *  Created on: 04/ott/2012
 *      Author: Mattero Ragni
 */

#ifndef HELP_H_
#define HELP_H_

/*
 * Inclusioni
 *
 */

#include "msp430g2553.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "parser.h"

/*
 * Definizioni
 *
 */

#ifdef __DEBUG
#define __BEBUG_HELP
#endif

#define MAX_PIPE 2

//////// MODULARITA' //////////
// Quando si aggiunge un nuovo modulo è necessario inserire qui i messaggi che
// devono essere stampati dal comando help. Inserire messaggio formattato
// e lunghezza del messaggio. Aggiungere il comando alla lista dei comandi (HELP_VOID)

#define HELP_TIMER "timer"
#define HELP_TIMER_MSG "\n\rtimer [mode:off|on|periodic] [intms:500..65534]\n\n\r\tProgramma che pilota il Timer. Il primo parametro imposta\n\r\til modo, mentre il secondo l'intervallo in millisecondi"
#define HELP_TIMER_MSGN 168

#define HELP_ADC "adc"
#define HELP_ADC_MSG "\n\radc [canale:1..16|temp]\n\n\r\tProgramma che pilota il modulo adc. Il canale del sensore di\n\r\ttemperatura è il numero 11, selezionabile anche con temp.\n\r\tI canali dal 12 al 16 sono cortocircuitati a (Vr-Vg)/2."
#define HELP_ADC_MSGN 207

#define HELP_PIPE "pipe"
#define HELP_PIPE_MSG "\n\r[comando] | [comando] \n\r\n\tLa pipe reindirizza, se disponibile, l'output del primo programma al \n\r\t al secondo programma\n\r"
#define HELP_PIPE_MSGN 123

#define HELP_HELP "help"
#define HELP_HELP_MSG "\n\rhelp [comando]\n\n\r\tFornisce una descrizione rapida del [comando], se indicato, altrimenti\n\r\tfornisce una lista di comandi disponibili.\n\r"
#define HELP_HELP_MSGN 137

#define HELP_WHAT_THE_HELL "\n\r[HELP]: Comando non riconosciuto\n\r"
#define HELP_WHAT_THE_HELLN 36

#define HELP_VOID "\n\rCOMANDI DISPONIBILI \n\rhelp\n\rtimer [mode] [intervallo ms]\n\racd [canale]\n\r| (Usa: help pipe)\n\r"
#define HELP_VOID_N 94

/*
 * Prototipi
 *
 */

// IMPLEMENTAZIONE INTERFACCIA PARSER //
// In: riferimento programma
void helpExec(char);
////////////////////////////////////////

#endif /* HELP_H_ */
