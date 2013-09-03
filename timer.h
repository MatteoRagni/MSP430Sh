/*
 * timer.h
 *
 *  Created on: 30/set/2012
 *      Author: Matteo Ragni
 */

#ifndef TIMER_H_
#define TIMER_H_

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
#include "parser.h"

/*
 * Definizioni
 *
 */

#define MAX_PIPE 2

#ifdef __DEBUG
#define __DEBUG_TIMER
#endif

/*
 * Prototipi
 *
 */

// Funzione che inizializza il timer
void timer_start();

// Funzione che arresta il timer
void timer_stop();

// Funzione che imposta la modalità, se on, off
// o periodico
// In: riferimento al modo
void timer_setMode(char);

// Imposta l'intervallo: il valore massimo è
// 65535 millisecondi
// In: intervallo in millisecondi
void timer_setInterval(unsigned int);

// Funzione che viene chiamata dall'interrupt quando è
// trascorso l'intervallo di tempo specificato
void timer_fire();

#ifdef __DEBUG_TIMER
void ProvaTimer(unsigned int, char);
#endif

// IMPLEMENTAZIONE INTERFACCIA AL PARSER //
// In: modo
//     intervallo in ms
void TimerExec(char, unsigned int);
void TimerEventHandler();
///////////////////////////////////////////

#endif /* TIMER_H_ */
