//uart_defines.h
// Give a readable name to a fixed value or setting.
#define TXD0_PIN_FUNC 0
// Give a readable name to a fixed value or setting.
#define RXD0_PIN_FUNC 1
// Give a readable name to a fixed value or setting.
#define BAUD 9600
// Give a readable name to a fixed value or setting.
#define FOSC 12000000
// Give a readable name to a fixed value or setting.
#define CCLK 5*FOSC
// Give a readable name to a fixed value or setting.
#define PCLK (CCLK/4)
// Give a readable name to a fixed value or setting.
#define DIVISOR (PCLK/(16*BAUD))
//defines for UxLCR sfr's
// Give a readable name to a fixed value or setting.
#define _8BIT 3
// Give a readable name to a fixed value or setting.
#define DLAB_BIT 7
// Give a readable name to a fixed value or setting.
#define WORD_LEN_SEL_BITS 0
//define for UxLSR sfr's
// Give a readable name to a fixed value or setting.
#define TEMT_BIT 6
// Give a readable name to a fixed value or setting.
#define DR_BIT 0
