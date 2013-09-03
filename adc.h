/*
 * adc.h
 *
 *  Created on: 29/set/2012
 *      Author: Matteo Ragni
 */

#ifndef ADC_H_
#define ADC_H_

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

// Commentare per eliminare dalla compilazione
// le sezioni di debug
#ifdef __DEBUG
#define __DEBUG_ADC
#endif

#define MAX_PIPE 2


// Costante di calibrazione del sensore di temperatura
// offset in gradi non in bit!
#define ADC_T_CALIBRATION 	 -12 //DegC

/*
 * Prototipi
 *
 */

// Inizializza la configurazione dell'adc. Per farla semplice
// è inizializzato in maniera utile per poter leggere
// il sensore di temperatura
void adc_init();

// Disabilita il modulo dell'adc dopo la lettura
inline void adc_stop();

// Formula di calibrazione del sensore di temperatura per Ref 1.5V:
// oC = ((A10/1024)*1500mV)-986mV)*1/3.55mV
// Dalle specifiche del microcontrollore (pag 564)
// RICHIEDE CALIBRAZIONE!
// In: lettura dell'adc
// Out: temperatura in gradi centigradi
inline long adc_TempCal(long);


// Imposta il canale dell'ADC
// Notare che il canale 10 è la temperatura
// In: canale in forma numerica
inline void adc_selCh(char);

// Abilita l'encoding e comincia la conversione
// ritorna la lettura dell'adc
int adc_read();

// Salva nella stringa in ingresso la rappresentazione
// binaria della lettura dell'encoder
// In: valore numerico che deve essere convertito (mx 10bit)
// 	   stringa in cui salvare il valore convertito
void displayBits( long, char*);

// IMPLEMENTAZIONE INTERFACCIA PARSER //
// In: canale
void adcExec(char);
////////////////////////////////////////

#endif /* ADC_H_ */
