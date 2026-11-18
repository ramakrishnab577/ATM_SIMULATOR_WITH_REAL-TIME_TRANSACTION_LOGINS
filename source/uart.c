// uart.c

// Include LPC21xx microcontroller register definitions for UART0 configuration.
#include <lpc21xx.h>

// Include user-defined data types such as u8, u32, s32, and f32.
#include "types.h"

// Include UART function declarations for serial communication.
#include "uart.h"

// Include UART configuration macros for baud rate, word length, and register bits.
#include "uart_defines.h"


// Initialize UART0 for serial communication using the configured baud rate.
void UART0_Init(void)
{
    // Clear the function selection bits of P0.0 and P0.1.
    PINSEL0 &=~((3<<2)|(3<<0));

    // Alternative pin configuration using predefined UART pin macros.
    //PINSEL0 |=(1<<TXD0_PIN_FUNC|1<<RXD0_PIN_FUNC);

    // Configure P0.0 as TXD0 and P0.1 as RXD0 for UART0 communication.
    PINSEL0|=0x05;

    // Enable divisor latch access and configure UART0 for 8-bit data transmission.
    U0LCR=((1<<DLAB_BIT)|(_8BIT<<WORD_LEN_SEL_BITS));

    // Load the lower 8 bits of the baud rate divisor into U0DLL.
    U0DLL=DIVISOR;

    // Load the upper 8 bits of the baud rate divisor into U0DLM.
    U0DLM=DIVISOR>>8;

    // Disable divisor latch access to enable normal UART data register operation.
    U0LCR &=~(1<<DLAB_BIT);
}


// Transmit a single 8-bit character through UART0.
void UART0_Tx(u8 sDat)
{
    // Write the character into the UART0 transmit holding register.
    U0THR=sDat;

    // Wait until the transmit holding register and shift register are empty.
    while(((U0LSR>>TEMT_BIT)&1)==0);
}


// Receive a single character through UART0 (currently commented out).
/*
void UART0_Rx(void)
{
    // Wait until UART0 receives a character.
    while(((U0LSR>>DR_BIT)&1)==0);

    // Read the received character from the UART0 receive buffer register.
    return U0RBR;
}
*/


// Transmit a null-terminated string through UART0.
void U0_TxStr(char *s)
{
    // Continue transmitting characters until the null terminator is reached.
    while(*s)
    {
        // Transmit the current character and advance to the next character.
        UART0_Tx(*s++);
    }
}


// Convert an unsigned 32-bit integer into ASCII digits and transmit through UART0.
void U0_TxU32(u32 n)
{
    // Initialize a digit index and an array to store converted ASCII digits.
    s32 i=0;
    u8 a[10];

    // Check whether the given unsigned integer is zero.
    if(n==0)
    {
        // Transmit the ASCII character '0' through UART0.
        UART0_Tx('0');
    }

    // Convert a nonzero unsigned integer into individual ASCII digits.
    else
    {
        // Extract decimal digits until the entire number is converted.
        while(n>0)
        {
            // Extract the last digit, convert it to ASCII, and store it in the array.
            a[i++]=(n%10)+48;

            // Remove the last decimal digit from the number.
            n/=10;
        }
    }

    // Transmit the stored ASCII digits in reverse order to display the correct number.
    for(--i;i>=0;i--)
    {
        // Transmit the current ASCII digit through UART0.
        UART0_Tx(a[i]);
    }
}


// Transmit a signed 32-bit integer through UART0.
void U0_Tx32(s32 n)
{
    // Check whether the given integer is negative.
    if(n<0)
    {
        // Transmit the negative sign before the integer value.
        UART0_Tx('-');

        // Convert the negative integer to its positive magnitude.
        n=-n;
    }

    // Pass the integer value to UART0 as a single 8-bit character.
    UART0_Tx(n);
}


// Transmit a floating-point value with the specified decimal places through UART0.
void U0_F32(f32 fn,u8 nDP)
{
    // Declare variables to store the integer part and decimal digit counter.
    u32 n,i;

    // Check whether the floating-point value is negative.
    if(fn<0.0)
    {
        // Transmit the negative sign before the number.
        UART0_Tx('-');

        // Convert the negative floating-point value to a positive value.
        fn=-fn;
    }

    // Extract the integer part of the floating-point number.
    n=fn;

    // Pass the integer part to UART0 as a single 8-bit character.
    UART0_Tx(n);

    // Transmit the decimal point through UART0.
    UART0_Tx('.');

    // Extract and transmit the requested number of decimal digits.
    for(i=0;i<nDP;i++)
    {
        // Remove the integer part and multiply the fractional part by 10.
        fn=(fn-n)*10;

        // Extract the next decimal digit from the floating-point value.
        n=fn;

        // Convert the decimal digit to ASCII and transmit it through UART0.
        UART0_Tx(n+48);
    }
}


// Receive a string through UART0 (currently commented out).
/*
s8* U0_RxStr(void)
{
    // Declare a static buffer to retain the received string after function return.
    static s8 rBuff[100];

    // Declare variables to store the received character and buffer index.
    s8 t,i=0;

    // Continuously receive characters until Enter is pressed.
    while(1)
    {
        // Receive one character through UART0.
        t=UART0_Rx();

        // Store the received character in the buffer.
        rBuff[i]=t;

        // Check whether the received character is newline or carriage return.
        if((t=='\n')||(t=='\r'))
        {
            // Replace the line-ending character with the null terminator.
            rBuff[i]='\0';

            // Stop receiving characters.
            break;
        }

        // Move to the next buffer position.
        i++;
    }

    // Transmit newline and carriage return characters.
    U0_TxStr("\n\r");

    // Return the address of the received string buffer.
    return rBuff;
}
*/
