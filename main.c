/*
 * main.c
 *
 *  Created on: 27/set/2012
 *      Author: Matteo Ragni
 */

/* RAGNI MATTEO 156994
 * PROGETTO EMBEDDED SYSTEMS
 *
 * Specifiche del progetto:
 * 1 - Implementare una shell in grado di comunicare tramite modulo UART
 *   - Implementare nella shell il comando di help
 *   - Implementare nella shell il blinking led
 * 2 - Implementare il comando: timer $1 $2
 *     $1 : ON/OFF/PERIODIC
 *     $2 : [time] in ms
 *     genera un evento (fire) dopo intervello di tempo [time] (o ogni [time] se
 *     impostato periodic
 * 3 - Implementare il comando: adc $1
 *     $1 : ch (canale ADC)
 *     scrive un messaggio che riporta il valore della lettura del
 *     canale selezionato in binario
 * 4 - Implementare timer | adc ovvero fornire la lettura all'evento
 * 	   generato da timer.
 *
 * 	   SVILUPPATO MEDIANTE CODE COMPOSER STUDIO 5.2.1
 * 	   Modalità DEBUG -> definto __DEBUG
 * 	   					 abilitate tutte le sezioni di debug all'interno
 * 	   					 dei singoli moduli
 * 	   Modalità RELEASE - > Le sezioni di debug dei singoli moduli sono
 * 	   						automaticamente escluse dalla compilazione
 */

// DEFINITIONS
#include "main.h"

extern char UART_buffer[MAX_BUFF_VECTOR];
extern char UART_counter;
extern char CallParserFlag;


// Inizializza il clock del microcontrollore
inline void mcu_clock_init() {

  WDTCTL = WDTPW + WDTHOLD;    // Stop WDT: Lo reinizializzo nella UART
  BCSCTL1 = CALBC1_1MHZ;       // Basic Clock @ 1 MHz
  DCOCTL = CALDCO_1MHZ;        // DCO @ 1 MHz (ACLK divider = 1 -> 32kHz)
}


int main( void ) {

  // Imposto il clock
  mcu_clock_init();

  // Abilito gli interrupt
  __bis_SR_register(GIE);

  // Inizializzo la porta seriale
  UART_init();

  // Inizializza shell
  UART_printPrompt();
  while(1){

	  while(CallParserFlag == 0) {eventHandler();}
	  parser(UART_buffer);
	  CallParserFlag = 0;
	  UART_ClearBuff();
	  UART_printPrompt();

  }
}
