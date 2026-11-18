// Include user-defined data types required by UART functions.
#include "types.h"

// Declare the function to initialize UART0 for serial communication.
void UART0_Init(void);

// Declare the function to transmit one character through UART0.
void UART0_Tx(u8 sDat);

// Declare the function intended to receive one character through UART0.
void UART0_Rx(void);

// Secondary UART driver functions.

// Declare the function to transmit a null-terminated string.
void U0_TxStr(char *);

// Declare the function to transmit an unsigned 32-bit integer.
void U0_TxU32(u32);

// Declare the function to transmit a signed 32-bit integer.
void U0_TxS32(s32);

// Declare the function to transmit a floating-point value.
void U0_TxF32(f32,u8);

// Declare the function to receive a string and return its buffer address.
s8* U0_RxStr(void);
