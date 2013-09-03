/*
 * help.c
 *
 *  Created on: 04/ott/2012
 *      Author: Matteo Ragni
 */

#include "help.h"

void helpExec(char prg) {
	if (prg < 5 ) {
		switch (prg) {
		case 0: UART_write(HELP_VOID, HELP_VOID_N); break;
		case 1: UART_write(HELP_HELP_MSG, HELP_HELP_MSGN); break;
		case 2: UART_write(HELP_ADC_MSG, HELP_ADC_MSGN); break;
		case 3: UART_write(HELP_TIMER_MSG, HELP_TIMER_MSGN); break;
		case 4: UART_write(HELP_PIPE_MSG, HELP_PIPE_MSGN); break;
		//case 99: UART_write(__EG_MSG, __EG_MSGN); break;
		}
	}
	else UART_write(HELP_WHAT_THE_HELL, HELP_WHAT_THE_HELLN);

}
