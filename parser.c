/*
 * parser.h
 *
 * Created on: 3/ott/2012
 * 		Author: Matteo Ragni
 */

#include "parser.h"

PipedStruct InitialParse;
TokenStruct CmdStruct[MAX_PIPE];
void (*parserCall)(TokenStruct[MAX_PIPE]) = NULL;

void init_PipedStruct(PipedStruct* P) {

	unsigned char i;
	unsigned char f;
	for (i=MAX_PIPE; i>0; i--) {
		for (f=CHAR_PIPE; f>0; f--) {
			P->Token[i-1][f-1] = '\0';
		}
	}
	P->nToken=0;

}

void init_TokenStruct(TokenStruct* P) {

	unsigned char i;
	unsigned char f;
	for (i=MAX_TOKEN; i>0; i--) {
		for (f=CHAR_CMD; f>0; f--)
			P->Token[i-1][f-1] = '\0';
	}
	P->nToken=0;

}

void copyTokenStruct (TokenStruct* p, const TokenStruct* v){

	init_TokenStruct(p);

	for(p->nToken = 0; p->nToken<v->nToken; p->nToken++){
		strcpy(p->Token[p->nToken],v->Token[p->nToken]);
	}
	p->nToken = v->nToken;
}

char SaveNext_Pipe(const char* input, PipedStruct* P) {

	if (P->nToken < MAX_PIPE) {
		strcpy(P->Token[P->nToken], input);
		P->nToken++;
		return 0;
	}
	return 1;

}

char SaveNext_Token(const char* input, TokenStruct* P) {

	if (P->nToken < MAX_TOKEN) {
		strcpy(P->Token[P->nToken], input);
		P->nToken++;
		return 0;
	}
	return 1;

}


void (*ParseCmd(TokenStruct TokenC))(TokenStruct[MAX_PIPE]) {

	if ( strcmp(TokenC.Token[0], "help") == 0 ) return &parser_help;
	else if ( strcmp(TokenC.Token[0], "adc") == 0 ) return &parser_adc;
	else if ( strcmp(TokenC.Token[0], "timer") == 0 ) return &parser_timer;
	else return NULL;

}

char parser(char* cmdLine) {

	unsigned char i;

	char *pch;

	init_PipedStruct(&InitialParse);

	pch = strtok(cmdLine, pipeDel);
	while (pch != NULL) {
		SaveNext_Pipe(pch, &InitialParse);
		pch = strtok(NULL, pipeDel);
	}

	if (InitialParse.nToken > MAX_PIPE) {
		UART_write(TOO_PIPED_CMD, TOO_PIPED_CMDN);
		return 1;
	}
	if ( InitialParse.Token[0][0]=='\0' ) {
		return 1;
	}

	for (i=MAX_PIPE; i>0; i--) {
		init_TokenStruct(&(CmdStruct[MAX_PIPE-i]));

		pch = strtok(InitialParse.Token[MAX_PIPE-i],tokenDel);
		while (pch != NULL) {
			SaveNext_Token(pch, &(CmdStruct[MAX_PIPE-i]));
			pch = strtok(NULL, tokenDel);
		}
	}

	parserCall = ParseCmd(CmdStruct[0]);
	if (parserCall != NULL) {
		(*parserCall)(CmdStruct);
		parserCall = NULL;
		return 0;
	}
	else {
		UART_write(UNKNOW_CMD, UNKNOW_CMDN);
		return 1;
	}
	//return 0;
}


// FUNZIONI DI PARSING
// help
#define HELP_PIPE "pipe"
#define HELP_ADC "adc"
#define HELP_TIMER "timer"
#define HELP_HELP "help"

void parser_help(TokenStruct TokenC[MAX_PIPE]) {

	if (TokenC[0].Token[1][0] == '\0') helpExec(0);
	else if (strcmp(HELP_HELP,TokenC[0].Token[1])==0) helpExec(1);
	else if (strcmp(HELP_ADC,TokenC[0].Token[1])==0) helpExec(2);
	else if (strcmp(HELP_TIMER,TokenC[0].Token[1])==0) helpExec(3);
	else if (strcmp(HELP_PIPE,TokenC[0].Token[1])==0) helpExec(4);
	//else if (strcmp(__EG,TokenC[0]->Token[1])==0) helpExec(99);
	else helpExec(100); // Non riconosciuto


}

// adc
#define LACK_PARAMETER "\n\r[ADC]: Manca un parametro\n\r"
#define LACK_PARAMETER_N 29
#define CH_ERROR "\n\r[ADC]: Regola chiamata canale violata (fuori dal range 1..16 o temp)\n\r"
#define CH_ERROR_N 70

void parser_adc(TokenStruct TokenC[MAX_PIPE]) {

	if (TokenC[0].Token[1][0] == '\0') {
		UART_write(LACK_PARAMETER, LACK_PARAMETER_N);
		return;
	}
	char ch;
	if (strcmp(TokenC[0].Token[1],"temp")==0) {
		ch=11;
	}
	else {
		ch = (char)atoi(TokenC[0].Token[1]);
		if (ch < 1 || ch > 16) {
			UART_write(CH_ERROR, CH_ERROR_N);
			return;
		}
	}
	adcExec(ch);

}

// timer
#define MODE_UNKNOWN "\n\t[TIMER]: Modo non riconosciuto\n\r"
#define MODE_UNKNOWN_N 34
#define MODELESS "\n\t[TIMER]: Modo non impostato\n\r"
#define MODELESS_N 31
#define OUTOFTIME "\n\t[TIMER]: Inserire intervallo tra 500 e 65534\n\r"
#define OUTOFTIME_N 48
#define TIMELESS "\n\t[TIMER]: Tempo non impostato\n\r"
#define TIMELESS_N 34

extern void (*function)(TokenStruct[MAX_PIPE]);
extern TokenStruct TempTimerCmd[MAX_PIPE];

void parser_timer(TokenStruct TokenC[MAX_PIPE]) {

	char mode;
	unsigned int interval;

	if ( TokenC[0].Token[1][0] != '\0' ) {
	// Parsing modo
		if(strcmp(TokenC[0].Token[1],"off")==0) mode = 0;
		else if(strcmp(TokenC[0].Token[1],"on")==0) mode = 1;
		else if(strcmp(TokenC[0].Token[1],"periodic")==0) mode = 2;
		else {
			UART_write(MODE_UNKNOWN,MODE_UNKNOWN_N);
			return;
		}
	}
	else {
		UART_write(MODELESS,MODELESS_N);
		return;
	}
	if ( TokenC[0].Token[2][0] != '\0' ) {

		if (atol(TokenC[0].Token[2]) <= 65534 && atol(TokenC[0].Token[2])>=500) interval = atol(TokenC[0].Token[2]);
		else {
			UART_write(OUTOFTIME,OUTOFTIME_N);
			return;
		}
	}
	else {
		if (mode != 0) {
				UART_write(TIMELESS,TIMELESS_N);
				return;
		}
	}

	if (TokenC[1].Token[0][0] != '\0') {
					function = ParseCmd(TokenC[1]);
					copyTokenStruct(&TempTimerCmd[0], &TokenC[1]);
				}

	TimerExec(mode,interval);

}

// EVENT HANDLER
extern char TimerEvent;

void eventHandler(){
	if (TimerEvent == 1) {
		TimerEvent = 0;
		TimerEventHandler();
		UART_printPrompt();
	}
}
