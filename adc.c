/*
 * adc.c
 *
 *  Created on: 29/set/2012
 *      Author: Matteo Ragni
 */

/*
 * Inclusioni
 *
 */

#include "adc.h"

/*
 * Variabili Globali
 *
 */

#ifdef __DEBUG_ADC
// Variabile usate per simulare il blocco della cpu
// se si impostasse il bit CPUOFF, sarebbe impossibile
// usare il FET debugger e il watch delle variabili
// all'interno di CCS
static int cpuoff=1;
static int lpm0 = 1;
#endif

// Variabile che contiene la lettura dell'adc
static long adc_buffer=0;


/*
 * Implementazione
 *
 */

void adc_init() {

#ifdef __DEBUG_ADC
	P1DIR |= (BIT6 + BIT0);
	P1OUT &= ~(BIT6 + BIT0);
#endif

	ADC10CTL0 = ( SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE);
	// SREF_1 : Vref = 1.5V internal ref. (per il sens. temp.)
	// ADC10SHT_3 : Sample and Hold time = 64 x ADC10CLK. Sample time per temperatura >30micros (pag. 563)
	// REFON : Attiva il generatore interno della tens. di riferimento
	// ADC10ON : Attiva il modulo dell'adc
	// ADC10IE : Abilita l'interrupt dell'adc

	// Uso un timer  per generare
	// un ritardo che permetta al riferimento Vref int
	// di arrivare a regime (come consigliato nel datasheet a pag. 551)
		TA1CCR0 = 30;	  // delay = 30*10^-6s / 10^-6 = 30;
		TA1CCTL0 |= CCIE;			// Abilito interrupt in compare mode
		TA1CTL = TASSEL_2 | MC_1 ;	// Sorg. di clock SMCLK=1MHz, conta fino a TA1CCR0
#ifdef __DEBUG_ADC
		while(lpm0){}
#endif
#ifndef __DEBUG_ADC
		LPM0;						// entro in Low power mode aspettando l'interrupt del timer
#endif
		TA1CCTL0 &= ~CCIE;			// disabilito interrupt del timer
		TA1CTL = 0;					// disabilito timer

}

inline void adc_stop() {
	ADC10CTL0 ^= ENC;
	ADC10CTL0 ^= (REFON + ADC10ON);
#ifdef __DEBUG_ADC
	P1OUT ^= BIT6;
#endif
}

inline void adc_selCh(char ch) {

	switch (ch) {
	case 1:		ADC10CTL1 = INCH_0;  				break; // A0
	case 2:		ADC10CTL1 = INCH_1;  				break; // A1
	case 3:		ADC10CTL1 = INCH_2;  				break; // A2
	case 4:		ADC10CTL1 = INCH_3;  				break; // A3
	case 5:		ADC10CTL1 = INCH_4;  				break; // A4
	case 6:		ADC10CTL1 = INCH_5;  				break; // A5
	case 7:		ADC10CTL1 = INCH_6;  				break; // A6
	case 8:		ADC10CTL1 = INCH_7;  				break; // A7
	case 9:		ADC10CTL1 = INCH_8;  				break; // Vref+
	case 10:	ADC10CTL1 = INCH_9;  				break; // Vref-
	case 11:	ADC10CTL1 = INCH_10 + ADC10DIV_3;	break; // sensore temperatura + sample 4 volte per oscillazione
	case 12:	ADC10CTL1 = INCH_11; 				break; // (Vcc-Vss)/2
	case 13:	ADC10CTL1 = INCH_12; 				break; // (Vcc-Vss)/2
	case 14:	ADC10CTL1 = INCH_13; 				break; // (Vcc-Vss)/2
	case 15:	ADC10CTL1 = INCH_14; 				break; // (Vcc-Vss)/2
	case 16:	ADC10CTL1 = INCH_15; 				break; // (Vcc-Vss)/2
	};

}

inline long adc_TempCal(long raw_read) { return ((raw_read - 673) * 423) / 1024 + ADC_T_CALIBRATION; }


int adc_read(){

	ADC10CTL0 |= (ENC + ADC10SC);	// Abilita encoding e comincia conversione

	// La parte successiva è una implementazione mediante interrupt di
	// while ( !(ADC10CTL0 & ADC10IFG) ) {}
#ifndef __DEBUG_ADC
	__bis_SR_register(CPUOFF + GIE);	// CPUOFF durante la conversione, attende l'interrupt dell'adc
#endif
#ifdef __DEBUG_ADC
	while(cpuoff) {}
#endif
	return (long)ADC10MEM;
}


void displayBits( long value, char* converted ) {
	unsigned char c;
	static const unsigned displayMask = 1<<10;   // 10 0000 0000
	for (c=10; c>0; c--) {
		converted[10-c] = ( value & displayMask ? '1' : '0' );
		value <<= 1;
		}
}


void adcExec(char ch) {

	char OutString[30] = {0};

	UART_write("\n\rLettura ADC\n\r",15);
	adc_init();
	adc_selCh(ch);
	adc_buffer = adc_read();
	char bitrap[10];

	if (ch == 11) {
		adc_buffer= adc_TempCal(adc_buffer);
		displayBits(adc_buffer, bitrap);
		sprintf(OutString, "\n\r[ADC]:\tch: %d\tread: %d *C\n\r", ch, adc_buffer);
		UART_write(OutString, strlen(OutString));
		//UART_write(bitrap,10);
		//UART_write("\n\r",2);
	}
	else {
		displayBits(adc_buffer, bitrap);
		sprintf(OutString, "\n\r[ADC]:\tch: %d\tread: %d\tbit: ", ch, adc_buffer);
		UART_write(OutString, strlen(OutString));
		UART_write(bitrap,10);
		UART_write("\n\r",2);

	}
	adc_stop();

}

////////////////////////////////////////

/*
 * Implementazioni degli interrupt della libreria
 *
 */

// Routine di interrupt del timer 1

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER_A1(void) {

#ifndef __DEBUG_ADC
	LPM0_EXIT;	// Esce dallo stato di attesa quando il riferimento si è assestato
#endif
#ifdef __DEBUG_ADC
	lpm0 = 0;
	P1OUT ^= BIT6;
#endif
}


// ADC10 routine di interrupt dell'adc

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
#ifndef __DEBUG_ADC
	__bic_SR_register_on_exit(CPUOFF);        // Riattiva la CPU quando ha finito la conversione
#endif
#ifdef __DEBUG_ADC
	cpuoff=0;
#endif
}

