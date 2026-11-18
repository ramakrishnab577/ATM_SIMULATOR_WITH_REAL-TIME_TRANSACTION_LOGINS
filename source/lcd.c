//lcd.c
// Include the header needed for this module.
#include "lcd_defines.h"
// Include the header needed for this module.
#include "defines.h"
// Include the header needed for this module.
#include "types.h"
// Include the header needed for this module.
#include "delay.h"
// Include the header needed for this module.
#include<lpc21xx.h>

// Define the function that performs this operation.
void WriteLCD(u8 byte)
{
        //select write operation
        // Set the selected microcontroller output pin LOW.
        IOCLR0=1<<LCD_RW;
        //place any byte on data pins d0 to d7
        // Call this function to perform the requested operation.
        WRITEBYTE(IOPIN0,LCD_DATA,byte);
        //provide high to low pulse for latching
        // Set the selected microcontroller output pin HIGH.
        IOSET0=1<<LCD_EN;
        // Wait for the requested number of microseconds.
        delay_us(1);
        // Set the selected microcontroller output pin LOW.
        IOCLR0=1<<LCD_EN;
        // Wait for the requested number of milliseconds.
        delay_ms(2);
}
// Define the function that performs this operation.
void CmdLCD(u8 cmd)
{
        //select cmd register
        // Set the selected microcontroller output pin LOW.
        IOCLR0=1<<LCD_RS;
        //write any cmd to lcd
        // Call this function to perform the requested operation.
        WriteLCD(cmd);
}

// Define the function that performs this operation.
void InitLCD(void)
{
        //cfg lcd connection gpio output pins
        //WRITEBYTE(IODIR0,LCD_DATA,0xFF);
        //SETBIT(IODIR0,LCD_RS);
        //SETBIT(IODIR0,LCD_RW);
        //SETBIT(IODIR0,LCD_EN);
        // Configure the selected GPIO pins as inputs or outputs.
        IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|
                // Call this function to perform the requested operation.
                (1<<LCD_RW)|(1<<LCD_EN);
        //power on delay
        // Wait for the requested number of milliseconds.
        delay_ms(15);
        // Send a control command to the LCD.
        CmdLCD(0x30);
        // Wait for the requested number of milliseconds.
        delay_ms(4);
        // Wait for the requested number of microseconds.
        delay_us(100);
        // Send a control command to the LCD.
        CmdLCD(0x30);
        // Wait for the requested number of microseconds.
        delay_us(100);
        // Send a control command to the LCD.
        CmdLCD(0x30);
        // Send a control command to the LCD.
        CmdLCD(MODE_8BIT_2LINE);
        // Send a control command to the LCD.
        CmdLCD(DSP_ON_CUR_OFF);
        // Clear the LCD before showing new information.
        CmdLCD(CLEAR_LCD);
        // Send a control command to the LCD.
        CmdLCD(SHIFT_CUR_RIGHT);
}

// Define the function that performs this operation.
void CharLCD(u8 asciiVal)
{
        //select data register
        // Set the selected microcontroller output pin HIGH.
        IOSET0=1<<LCD_RS;
        //write to ddram via data register
        // Call this function to perform the requested operation.
        WriteLCD(asciiVal);
}

// Define the function that performs this operation.
void StrLCD(char *s)
{
        // Repeat these steps while the condition is true.
        while(*s)
                // Display one character on the LCD.
                CharLCD(*s++);
}

// Define the function that performs this operation.
void U32LCD(u32 n)
{
        // Declare variables used to store data for this operation.
        s32 i=0; u8 a[10];
        // Check this condition before continuing.
        if(n==0)
        {
                // Display one character on the LCD.
                CharLCD('0');
        }
  // Handle the case when the previous condition is false.
  else
        {
                // Repeat these steps while the condition is true.
                while(n>0)
                {
                        // Update this value as part of the current operation.
                        a[i++]=(n%10)+48;
                        // Update this value as part of the current operation.
                        n/=10;
                }
                // Repeat these steps using the loop counter.
                for(--i;i>=0;i--)
                {
                        // Display one character on the LCD.
                        CharLCD(a[i]);
                }
        }
}

// Define the function that performs this operation.
void S32LCD(s32 n)
{
        // Check this condition before continuing.
        if(n<0)
        {
                // Display one character on the LCD.
                CharLCD('-');
                // Update this value as part of the current operation.
                n=-n;
        }
        // Display this number on the LCD.
        U32LCD(n);
}

// Define the function that performs this operation.
void F32LCD(f32 fn,u8 nDP)
{
   // Declare variables used to store data for this operation.
   u32 n,i;
         // Check this condition before continuing.
         if(fn<0.0)
         {
                 // Display one character on the LCD.
                 CharLCD('-');
                 // Update this value as part of the current operation.
                 fn=-fn;
         }
   		  // Update this value as part of the current operation.
   		  n=fn;
  		  // Display this number on the LCD.
  		  U32LCD(n);
          // Display one character on the LCD.
          CharLCD('.');
         // Repeat these steps using the loop counter.
         for(i=0;i<nDP;i++)
         {
                // Update this value as part of the current operation.
                fn=(fn-n) * 10;
                // Update this value as part of the current operation.
                n=fn;
			    // Display one character on the LCD.
			    CharLCD(n+48);
         }
}
	     