/*
 * uart.c
 *
 *  Created on: 27/set/2012
 *      Author: Matteo Ragni
 */

/*
 * Inclusioni
 *
 */

#include "uart.h"

/*
 * Variabili Globali
 *
 */

char UART_counter = 0;
char UART_buffer[MAX_BUFF_VECTOR] = {0};
char CallParserFlag = 0;

#ifdef BLINK_CUR
char BLINK_CUR_last=2;
#endif

/*
 * Implementazione
 *
 */

void UART_ClearBuff() {
	unsigned char j;
	UART_counter = 0;
	for (j=MAX_BUFF_VECTOR; j>0; j--) UART_buffer[MAX_BUFF_VECTOR-j] = '\0';
}


void UART_init()
{
  P1SEL = BIT1 + BIT2;                    // Set il mux1 di P1 a USCI_A0
  P1SEL2 = BIT1 + BIT2;                   // Set il mux2 di P1 a USCI_A0
  P1DIR |= BIT2;                          // Set 1.2 to output
  UCA0CTL1 |= UCSSEL_2;                   // SMCLK come sorgente del clock
  UCA0BR0 = 104;                          // 1 MHz/9.6kHz = 104.0     -> 104 (A)
  UCA0BR1 = 0;                            // 1 MHz/9.6kHz - 104 = 0.0 -> 0   (A)
  UCA0MCTL = UCBRS1;                      // Modulazione UCBRSx = 1          (A)
  UCA0CTL1 &= ~UCSWRST;                   // **Avvia USCI** Usci Software Reset
  IE2 |= UCA0RXIE;                        // Abilita interrupt in ricezione

#ifdef BLINK_CUR
  WDTCTL = WDT_ADLY_250;				  // Abilita il watchdog per 1s: fACLK (32KHz)
  IE1 = WDTIE;							  // Abilita l'interrupt per il wdtimer
#endif

#ifdef __DEBUG_UART
  P1DIR |= (BIT0+BIT6);					  // leds per debug
  P1OUT &= ~(BIT0+BIT6);				  // Forza leds spento
  P1REN  = BIT3;                          // P1.2 pull-up/down R enabled
  P1OUT  = BIT3;                          // P1.2 pull-up  R enabled
  P1IE   = BIT3;                          // P1.2 interrupt enabled
  P1IES  = BIT3;                          // P1.2 Low edge: 1: quando premi, 0: quando rilasci
  P1IFG  &= ~BIT3;                        // P1.2 IFG cleared
#endif

}
// Documentazione particolare per questo elemento:
// A: MSP430 UART Communication interface. Application report (Table 2)


void UART_SendByte(char c){
  while (!(IFG2 & UCA0TXIFG));
  UCA0TXBUF  = c;
}


inline char UART_getByte(){
  return UCA0RXBUF;
}


void UART_write(const char *buff, int n_buff) {

	unsigned char i;
	for (i=n_buff; i>0; i--) {
		UART_SendByte(buff[n_buff-i]);
	}

}

void UART_read(char in_buff, char endToken) {

	// Controlla se possibile scrivere nel vettore UART_buffer
	if ( UART_counter < MAX_BUFF_VECTOR ) {

		// Identifica eventuali delimitatori
		if ( in_buff != DELIMITER1 && in_buff != DELIMITER2 ) {
			UART_buffer[UART_counter++] = in_buff;
		}

		// Inserisci termine di stringa al posto del delimitatore
		// passa il buffer e la sua lunghezza al parser
		// e libera il buffer
		else {
			UART_buffer[UART_counter] = '\0';
			CallParserFlag = 1;
		}
	}
	// Se non è possibile scrivere lo segnala all'utente e libera
	// il buffer
	else {
		UART_write(ERR_UART_BUFFER_OVERFLOW, ERRN_UART_BUFFER_OVERFLOW);
		UART_ClearBuff();
	}
}

void UART_printPrompt() {

	UART_write(HOSTNAME_COLOR, HOSTNAME_COLORN);
	UART_write(HOSTNAME,HOSTNAMEN);
	UART_write(E_WHITE, E_COLOR_N);
	UART_write(SH_PROMPT, SH_PROMPTN);

}

/*
 * Implementazioni degli interrupt della libreria
 *
 */

// Interrupt dell'USCI in ricezione
// Ogni carattere ricevuto è salvato all'interno della variabile
// globale UART_buffer
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {

	char in_buff;
	in_buff = UART_getByte();

	// echo
	UART_SendByte(in_buff);

	// salva nel buffer
	UART_read(in_buff,'\0');
}


// Routine di interrupt del watchdog timer
// Utilizzato per far lampeggiare il cursore mediante
// macros VT100. Nel caso il led lampeggiante dia stato disabilitato
// dovrebbe essere disabilitato anche il watchdog
// la routine stampa un errore nel caso a wdt disabilitato si genera un
// interrupt
#pragma vector=WDT_VECTOR
__interrupt void Watchdog(void){
#ifdef BLINK_CUR
	if (BLINK_CUR_last > 0) {
		UART_write(E_CURSOR_INVIS,E_CURSOR_N);
		BLINK_CUR_last=0;
		return;
	}
	else {
		UART_write(E_CURSOR_VIS,E_CURSOR_N);
		BLINK_CUR_last=1;
		return;
	}
#endif
#ifndef BLINK_CUR
	UART_write(ERR_WDT_INT_UNHAND,ERRN_WDT_INT_UNHAND);
#endif
}

#ifdef __DEBUG_UART
#pragma vector=PORT1_VECTOR
__interrupt void Port1(void) {
	UART_write("\n\rDEBUG - RAGNI MATTEO - 156994\n\r", 33);
	P1IFG  &= ~BIT3;
	UART_printPrompt();
}
#endif
