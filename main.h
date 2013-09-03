/*
 * main.h
 *
 *  Created on: 27/set/2012
 *      Author: Matteo Ragni
 */

#ifndef MAIN_H_
#define MAIN_H_

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
//#include "timer.h"

/*
 * Definizioni
 *
 */

#ifdef __DEBUG
#define __BEBUG_MAIN
#endif

/*
 * Protipi
 *
 */

// Funzione che inizializza il clock di sistema
inline void mcu_clock_init();


#endif /* MAIN_H_ */
