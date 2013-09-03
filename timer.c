/*
 * timer.c
 *
 *  Created on: 30/set/2012
 *      Author: Matteo Ragni
 */

#include "timer.h"

static unsigned int timer_count = 0;
static unsigned int timer_target = 0;
static unsigned int continuos_count = 0;

// Variabili per l'interfaccia parser
void (*function)(TokenStruct[MAX_PIPE]) = NULL;  // ATTENZIONE: QUI DEVO CHIAMARE IL PARSER NON IL PROGRAMMA!!!
TokenStruct TempTimerCmd[MAX_PIPE];
char TimerEvent = 0;

void timer_start() {
	TA0CCTL0 |= CCIE;				// Abilita interrupt in modalità compare del timer A0
}

void timer_stop() {
	TA0CCTL0 &= ~CCIE;				// Disabilita gli interrupt
	TA0CTL &= ~(TASSEL_2 + MC_3);	// Disattiva la sorgente di clock e imposta halt mode (~MC_3 = MC_0 -> ~(11) = 00)
	continuos_count = 0;
}

void timer_setMode(char Mode) {
	switch(Mode) {
	case 0: TA0CTL = TASSEL_2 | MC_0; break;	// Halt mode
	case 1: TA0CTL = TASSEL_2 | MC_1; break;	// Up mode
	case 2: TA0CTL = TASSEL_2 | MC_2; break;	// Continuos mode
	}
}

void timer_setInterval(unsigned int interval) {
	timer_target = interval;
	timer_count = timer_target;
	TA0CCR0 = 1000; 		// conta intervalli di un millisecondo
}

void timer_fire() {
	UART_write("\n\rTimerA0 has fired!", 20);
	TimerEvent = 1;
	if ( TA0CTL & MC_1 )  {
		timer_stop();
		UART_write("\n\r", 2);
	}
	else {
		continuos_count++;
		timer_count = timer_target;
		char temp_cont[10];
		char ntemp_cont;
		ntemp_cont = sprintf(temp_cont," CM: %d\n\r", continuos_count);
		UART_write(temp_cont, ntemp_cont);
	}
}

#ifdef __DEBUG_TIMER
void ProvaTimer(unsigned int interval, char mode) {
	timer_setInterval(interval);
	timer_start();
	timer_setMode(mode);
}
#endif

// IMPLEMENTAZIONE INTERFACCIA AL PARSER

void TimerExec(char mode, unsigned int interval){
	timer_setInterval(interval);
	timer_start();
	timer_setMode(mode);
}

void TimerEventHandler(){
	if (function != NULL) (*function)(TempTimerCmd);
	return;
}

// Routine di interrupt del timer 1

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER_A0(void) {

	if (timer_count == 0) timer_fire();
	else timer_count--;
	TA0R = 0;
}
