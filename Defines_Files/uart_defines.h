//uart_defines.h
#define TXD0_PIN_FUNC 0
#define RXD0_PIN_FUNC 1
#define BAUD 9600
#define FOSC 12000000
#define CCLK 5*FOSC
#define PCLK (CCLK/4)
#define DIVISOR (PCLK/(16*BAUD))
//defines for UxLCR sfr's
#define _8BIT 3
#define DLAB_BIT 7
#define WORD_LEN_SEL_BITS 0
//define for UxLSR sfr's
#define TEMT_BIT 6
#define DR_BIT 0
