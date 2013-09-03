/*
 * escapeVT100.h
 *
 *  Created on: 29/set/2012
 *      Author: Matteo Ragni
 *      	 	Derivano dallo standard Vt100:
 *      	 	source: VT100 Series Technical Manual (EK-VT100-TM-002)
 */

#ifndef ESCAPEVT100_H_
#define ESCAPEVT100_H_

/*
 * Definizioni
 *
 */

// Svuota terminale
#define E_CLC   "\x1B[2J\x1B[H"
#define E_CLC_N	7

// Colore Testo
#define E_BLACK       "\x1B[30m"
#define E_RED         "\x1B[31m"
#define E_GREEN       "\x1B[32m"
#define E_YELLOW      "\x1B[33m"
#define E_BLUE        "\x1B[34m"
#define E_MAGENTA     "\x1B[35m"
#define E_CYAN        "\x1B[36m"
#define E_WHITE       "\x1B[37m"
#define E_COLOR_N	  5

// Colore background
#define E_BG_BLACK    "\x1B[40m"
#define E_BG_RED      "\x1B[41m"
#define E_BG_GREEN    "\x1B[42m"
#define E_BG_YELLOW   "\x1B[43m"
#define E_BG_BLUE     "\x1B[44m"
#define E_BG_MAGENTA  "\x1B[45m"
#define E_BG_CYAN     "\x1B[46m"
#define E_BG_WHITE    "\x1B[47m"
#define E_BCOLOR_N	  5

// Effetti del testo
#define E_F_RST         "\x1B[0m"
#define E_F_BRIGHT      "\x1B[1m"
#define E_F_DIM         "\x1B[2m"
#define E_F_UNDERLINE   "\x1B[4m"
#define E_F_BLINK       "\x1B[5m"
#define E_F_REVERSE     "\x1B[7m"
#define E_F_HIDDEN      "\x1B[8m"
#define E_EFFECT_N	  	4

// Cursore
#define E_CURSOR_INVIS	"\x1B[?25l"
#define E_CURSOR_VIS	"\x1B[?25h"
#define	E_CURSOR_N		6

#endif /* ESCAPEVT100_H_ */
