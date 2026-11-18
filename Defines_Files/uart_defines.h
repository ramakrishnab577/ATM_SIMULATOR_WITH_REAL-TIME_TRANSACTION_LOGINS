//uart_defines.h
// Define PINSEL function selection bit position for UART0 TXD0 (P0.0).
#define TXD0_PIN_FUNC 0

// Define PINSEL function selection bit position for UART0 RXD0 (P0.1).
#define RXD0_PIN_FUNC 1

// Set the UART communication baud rate to 9600 bits per second.
#define BAUD 9600

// Define the external crystal oscillator frequency as 12 MHz.
#define FOSC 12000000

// Set the CPU clock frequency to 5 times the oscillator frequency (60 MHz).
#define CCLK 5*FOSC

// Set the peripheral clock frequency to one-fourth of the CPU clock (15 MHz).
#define PCLK (CCLK/4)

// Calculate the UART baud rate divisor using peripheral clock and baud rate.
#define DIVISOR (PCLK/(16*BAUD))


// UART LINE CONTROL REGISTER (UxLCR)

// Define the value 3 to configure UART communication with 8 data bits.
#define _8BIT 3

// Define bit position 7 to enable or disable Divisor Latch Access (DLAB).
#define DLAB_BIT 7

// Define bit position 0 as the starting bit for UART word length selection.
#define WORD_LEN_SEL_BITS 0


// UART LINE STATUS REGISTER (UxLSR)

// Define bit position 6 to check whether the UART transmitter is completely empty.
#define TEMT_BIT 6

// Define bit position 0 to check whether received data is available in the UART receiver.
#define DR_BIT 0
