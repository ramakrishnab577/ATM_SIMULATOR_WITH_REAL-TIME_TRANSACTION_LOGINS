// lcd.c

// Include LCD command definitions and GPIO pin configurations.
#include "lcd_defines.h"

// Include macros for bit, nibble, and byte operations.
#include "defines.h"

// Include user-defined data types such as u8, u32, s32, and f32.
#include "types.h"

// Include software delay function declarations.
#include "delay.h"

// Include LPC21xx microcontroller register definitions.
#include <lpc21xx.h>


// Send an 8-bit command or data value to the LCD.
void WriteLCD(u8 byte)
{
    // Select the LCD write operation by making the RW pin LOW.
    IOCLR0=1<<LCD_RW;

    // Place the 8-bit value on LCD data pins D0 to D7.
    WRITEBYTE(IOPIN0,LCD_DATA,byte);

    // Make the LCD Enable pin HIGH to start the data transfer.
    IOSET0=1<<LCD_EN;

    // Maintain the Enable signal HIGH for 1 microsecond.
    delay_us(1);

    // Make the Enable pin LOW to latch the data into the LCD.
    IOCLR0=1<<LCD_EN;

    // Wait for 2 milliseconds to allow the LCD to process the data.
    delay_ms(2);
}


// Send a command to the LCD instruction register.
void CmdLCD(u8 cmd)
{
    // Select the LCD instruction register by making RS LOW.
    IOCLR0=1<<LCD_RS;

    // Send the command byte to the LCD.
    WriteLCD(cmd);
}


// Initialize the LCD in 8-bit, 2-line mode.
void InitLCD(void)
{
    // Configure LCD data pins D0 to D7 and control pins as GPIO outputs.
    //WRITEBYTE(IODIR0,LCD_DATA,0xFF);
    //SETBIT(IODIR0,LCD_RS);
    //SETBIT(IODIR0,LCD_RW);
    //SETBIT(IODIR0,LCD_EN);

    // Configure P0.8 to P0.15 as LCD data output pins.
    // Configure RS, RW, and EN pins as GPIO outputs.
    IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|
            (1<<LCD_RW)|(1<<LCD_EN);

    // Wait for 15 milliseconds after power ON for LCD stabilization.
    delay_ms(15);

    // Send the initial function-set command to select 8-bit interface mode.
    CmdLCD(0x30);

    // Wait for 4 milliseconds before sending the next initialization command.
    delay_ms(4);

    // Provide an additional 100-microsecond initialization delay.
    delay_us(100);

    // Repeat the function-set command to initialize the 8-bit interface.
    CmdLCD(0x30);

    // Wait for 100 microseconds before the next function-set command.
    delay_us(100);

    // Send the function-set command again to complete initial synchronization.
    CmdLCD(0x30);

    // Configure the LCD for 8-bit communication and 2-line display mode.
    CmdLCD(MODE_8BIT_2LINE);

    // Turn ON the LCD display and turn OFF the cursor.
    CmdLCD(DSP_ON_CUR_OFF);

    // Clear all characters from the LCD and return the cursor home.
    CmdLCD(CLEAR_LCD);

    // Set the entry mode to move the cursor right after writing each character.
    CmdLCD(SHIFT_CUR_RIGHT);
}


// Display a single ASCII character on the LCD.
void CharLCD(u8 asciiVal)
{
    // Select the LCD data register by making RS HIGH.
    IOSET0=1<<LCD_RS;

    // Send the ASCII character to the LCD for display.
    WriteLCD(asciiVal);
}


// Display a null-terminated string on the LCD.
void StrLCD(char *s)
{
    // Continue displaying characters until the null terminator is reached.
    while(*s)

        // Display the current character and advance to the next character.
        CharLCD(*s++);
}


// Display an unsigned 32-bit integer on the LCD.
void U32LCD(u32 n)
{
    // Initialize a digit index and an array to store ASCII digits.
    s32 i=0;
    u8 a[10];

    // Check whether the given number is zero.
    if(n==0)
    {
        // Display the ASCII character '0' on the LCD.
        CharLCD('0');
    }

    // Convert and display the number if it is greater than zero.
    else
    {
        // Extract decimal digits until the entire number is converted.
        while(n>0)
        {
            // Extract the last digit, convert it to ASCII, and store it.
            a[i++]=(n%10)+48;

            // Remove the last digit from the number.
            n/=10;
        }

        // Display the stored digits in reverse order to obtain the correct number.
        for(--i;i>=0;i--)
        {
            // Display the current ASCII digit on the LCD.
            CharLCD(a[i]);
        }
    }
}


// Display a signed 32-bit integer on the LCD.
void S32LCD(s32 n)
{
    // Check whether the given integer is negative.
    if(n<0)
    {
        // Display the negative sign before the number.
        CharLCD('-');

        // Convert the negative number to its positive magnitude.
        n=-n;
    }

    // Display the integer value using the unsigned integer display function.
    U32LCD(n);
}


// Display a floating-point number with the specified decimal places.
void F32LCD(f32 fn,u8 nDP)
{
    // Declare variables to store the integer part and decimal digit counter.
    u32 n,i;

    // Check whether the floating-point number is negative.
    if(fn<0.0)
    {
        // Display the negative sign before the number.
        CharLCD('-');

        // Convert the negative floating-point number to a positive value.
        fn=-fn;
    }

    // Extract the integer part of the floating-point number.
    n=fn;

    // Display the integer part of the floating-point number.
    U32LCD(n);

    // Display the decimal point on the LCD.
    CharLCD('.');

    // Repeat the process for the requested number of decimal places.
    for(i=0;i<nDP;i++)
    {
        // Extract the next decimal digit by removing the integer part and multiplying by 10.
        fn=(fn-n)*10;

        // Store the extracted decimal digit as an integer.
        n=fn;

        // Convert the decimal digit to ASCII and display it on the LCD.
        CharLCD(n+48);
    }
}
