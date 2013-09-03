/*
 * isr_hdl.c
 *
 *  Created on: 07/ott/2012
 *      Author: nirvana1289
 */

/*
 * Inclusioni
 *
 */

#include "isr_hdl.h"

/*
 * Implementazioni degli interrupt della libreria
 *
 */

#pragma vector=COMPARATORA_VECTOR
__interrupt void COMPARATORA_ISR (void) {
	UART_write("\n\r[ISR]: ComparatorA \?\?\n\r", 25);
	UART_printPrompt();
}

#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR (void) {
	UART_write("\n\r[ISR]: Non Maskable Interrupt \?\?\n\r", 36);
	UART_printPrompt();
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR (void) {
	UART_write("\n\r[ISR]: Port2 \?\?\n\r", 19);
	UART_printPrompt();
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void) {
	UART_write("\n\r[ISR]: Timer0_A1 \?\?\n\r", 23);
	UART_printPrompt();
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void) {
	UART_write("\n\r[ISR]: Timer1_A1 \?\?\n\r", 23);
	UART_printPrompt();
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR (void) {
	UART_write("\n\r[ISR]: USCI Tx \?\?\n\r", 21);
	UART_printPrompt();
}

#ifndef __DEBUG_ISR_HDL
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR (void) {
	UART_write("\n\r[ISR]: Port1 \?\?\n\r", 19);
	UART_printPrompt();
}
#endif
