// kpm.c

// Include LPC21xx microcontroller register definitions.
#include <LPC21xx.h>

// Include macros for bit, nibble, and byte operations.
#include "defines.h"

// Include user-defined data types such as u32.
#include "types.h"

// Include keypad row and column pin definitions.
#include "kpm_defines.h"

// Include LCD function declarations.
#include "lcd.h"

// Include LCD command and pin definitions.
#include "lcd_defines.h"

// Include software delay function declarations.
#include "delay.h"

// Define the maximum count value as 100000.
#define MAX 100000

// Declare the external keypad lookup table containing key values.
extern u32 kpmLUT[][4];

// Declare variables to store the detected row, column, and key value.
u32 row,col,keyV;


// Scan the keypad columns to detect whether any key is pressed.
u32 ColScan(void)
{
    // Declare a variable to store the status of the four column pins.
    u32 status;

    // Read the four column bits from P1.20 to P1.23.
    status = READNIBBLE(IOPIN1,COL0);

    // Return 0 if any column is LOW (key pressed), otherwise return 1.
    return ((status<15) ? 0 : 1);
}


// Identify the row containing the pressed key.
u32 RowCheck(void)
{
    // Declare a variable to store the detected row number.
    u32 r;

    // Scan each keypad row from row 0 to row 3.
    for(r=0;r<=3;r++)
    {
        // Make the selected row LOW and the remaining rows HIGH.
        WRITENIBBLE(IOPIN1,ROW0,~(1<<r));

        // Check whether any column becomes LOW.
        if(ColScan()==0)
        {
            // Stop scanning when the pressed key's row is detected.
            break;
        }
    }

    // Make all four keypad rows LOW after completing row detection.
    WRITENIBBLE(IOPIN1,ROW0,0);

    // Return the detected row number.
    return r;
}


// Identify the column containing the pressed key.
u32 ColCheck(void)
{
    // Declare a variable to store the detected column number.
    u32 c;

    // Scan each keypad column from column 0 to column 3.
    for(c=0;c<=3;c++)
    {
        // Check whether the current column pin is LOW.
        if(READBIT(IOPIN1,COL0+c)==0)

            // Stop scanning when the pressed key's column is detected.
            break;
    }

    // Return the detected column number.
    return c;
}


// Scan the keypad and return the value of the pressed key.
u32 KeyScan(void)
{
    // Wait until any key is pressed on the keypad.
    while(ColScan());

    // Identify and store the row number of the pressed key.
    row=RowCheck();

    // Identify and store the column number of the pressed key.
    col=ColCheck();

    //delay_ms(200);

    // Get the corresponding key value from the keypad lookup table.
    keyV=kpmLUT[row][col];

    //while(ColScan());

    // Return the detected key value.
    return keyV;
}


// Initialize the GPIO pins used for the 4x4 matrix keypad.
void InitKPM(void)
{
    // Configure P1.16 to P1.19 as output pins for keypad rows.
    IODIR1|=15<<ROW0;

    // Configure P1.20 to P1.23 as input pins for keypad columns.
    //IODIR1 &=~(15<<COL0); //default
}


// Define the 4x4 keypad lookup table to map row and column positions to keys.
u32 kpmLUT[4][4]=
{
    {1,2,3,'A'},
    {4,5,6,'B'},
    {7,8,9,'C'},
    {'*',0,'#','D'}
};
// Read the PIN from the keypad and hide the entered digits using '*'.
u32 Read_Password()
{
    // Initialize variables to store the PIN, key value, digit count, and LCD position.
    u32 num=0,val,digit=0,i=0;

    // Continuously accept keypad input until the user confirms the PIN.
    while(1)
    {
        // Read the key pressed on the 4x4 matrix keypad.
        val=KeyScan();

        // Wait until the pressed key is released.
        while(ColScan()==0);

        // Check whether the pressed key is a digit from 0 to 9.
        if(val>=0 && val<=9)
        {
            // Move the LCD cursor to the next position on the second line.
            CmdLCD(GOTO_LINE2_POS0+(i++));

            // Display '*' instead of the actual PIN digit for security.
            CharLCD('*');

            // Check whether the number of entered digits is below MAX.
            if(digit<MAX)
            {
                // Append the entered digit to the existing PIN.
                num=num*10+val;

                // Increment the number of entered PIN digits.
                digit++;
            }
        }

        // Check whether the '#' key (ASCII 35) is pressed to confirm the PIN.
        else if(val==35)
        {
            // Return the entered PIN only if at least one digit was entered.
            if(digit>0)
                return num;

            //CmdLCD(0x01);
        }

        // Check whether the '*' key (ASCII 42) is pressed to delete a digit.
        else if(val==42)
        {
            // Delete the last PIN digit only if at least one digit was entered.
            if(digit>0)
            {
                // Decrease the number of entered PIN digits.
                digit--;

                // Move the LCD position back by one character.
                i--;

                // Remove the last digit from the stored PIN.
                num=num/10;

                // Move the LCD cursor to the last entered digit position.
                CmdLCD(GOTO_LINE2_POS0+i);

                // Erase the last displayed '*' character.
                StrLCD(" ");

                // Move the LCD cursor back to the erased position.
                CmdLCD(GOTO_LINE2_POS0+i);
            }
        }
    }
}
// Read the transaction amount from the keypad and validate it.
u32 transaction_amnt()
{
    // Initialize variables to store the amount, key value, digit count, and LCD position.
    u32 num=0,val,digit=0,i=0;

    // Continuously read keypad input until a valid amount is entered.
    while(1)
    {
        // Read the key pressed on the 4x4 matrix keypad.
        val=KeyScan();

        // Wait until the pressed key is released.
        while(ColScan()==0);

        // Check whether the pressed key is a digit from 0 to 9.
        if(val>=0 && val<=9)
        {
            // Move the LCD cursor to the next position on the second line.
            CmdLCD(GOTO_LINE2_POS0+(i++));

            // Display the entered digit on the LCD.
            U32LCD(val);

            // Check whether the number of entered digits is below MAX.
            if(digit<MAX)
            {
                // Append the entered digit to the transaction amount.
                num=num*10+val;

                // Increment the number of entered digits.
                digit++;
            }
        }

        // Check whether the '#' key (ASCII 35) is pressed to confirm the amount.
        else if(val==35)
        {
            // Proceed with validation only if at least one digit was entered.
            if(digit>0)
            {
                // Check whether the entered transaction amount is zero.
                if(num==0)
                {
                    // Move the LCD cursor to the beginning of the second line.
                    CmdLCD(GOTO_LINE2_POS0);

                    // Clear the previously entered amount from the LCD.
                    StrLCD("                 ");

                    // Move the LCD cursor back to the beginning of the second line.
                    CmdLCD(GOTO_LINE2_POS0);

                    // Display an invalid amount message.
                    StrLCD("Invalid!......");

                    // Wait for one second before clearing the input.
                    delay_s(1);

                    // Jump to the input reset section.
                    goto e;
                }

                // Check whether the amount is not a multiple of 100.
                if(num%100!=0)
                {
                    // Move the LCD cursor to the beginning of the second line.
                    CmdLCD(GOTO_LINE2_POS0);

                    // Clear the previously entered amount from the LCD.
                    StrLCD("                 ");

                    // Move the LCD cursor back to the beginning of the second line.
                    CmdLCD(GOTO_LINE2_POS0);

                    // Display an invalid amount message.
                    StrLCD("Invalid!......");

                    // Wait for one second before clearing the input.
                    delay_s(1);

                    // Jump to the input reset section.
                    goto e;
                }

                // Return the valid transaction amount to the calling function.
                return num;
            }
        }

        // Check whether the '*' key (ASCII 42) is pressed to delete a digit.
        else if(val==42)
        {
            // Delete the last digit only if at least one digit was entered.
            if(digit>0)
            {
                // Decrease the number of entered digits.
                digit--;

                // Move the LCD position back by one character.
                i--;

                // Remove the last digit from the transaction amount.
                num=num/10;

                // Move the LCD cursor to the position of the last digit.
                CmdLCD(GOTO_LINE2_POS0+i);

                // Erase the last displayed digit by writing a space.
                StrLCD(" ");

                // Move the LCD cursor back to the erased digit position.
                CmdLCD(GOTO_LINE2_POS0+i);
            }
        }

        // Handle any other key by resetting the entered amount.
        else
        {
            // Label used to reset the transaction amount after invalid input.
            e:num=0;

            // Reset the entered digit count to zero.
            digit=0;

            // Move the LCD cursor to the beginning of the second line.
            CmdLCD(GOTO_LINE2_POS0);

            // Clear the previously displayed transaction amount.
            StrLCD("                  ");
        }
    }
}
// Read a number from the keypad and return it when '#' is pressed.
u32 set_number()
{
    // Initialize variables to store the number, key value, digit count, and LCD position.
    u32 num=0,val,digit=0,i=0;

    // Continuously accept keypad input until the user confirms the number.
    while(1)
    {
        // Read the key pressed on the 4x4 matrix keypad.
        val=KeyScan();

        // Wait until the pressed key is released.
        while(ColScan()==0);

        // Check whether the pressed key is a digit from 0 to 9.
        if(val>=0 && val<=9)
        {
            // Move the LCD cursor to the next position on the second line.
            CmdLCD(GOTO_LINE2_POS0+(i++));

            // Display the entered digit on the LCD.
            U32LCD(val);

            // Check whether the number of entered digits is below MAX.
            if(digit<MAX)
            {
                // Append the entered digit to the existing number.
                num=num*10+val;

                // Increment the number of entered digits.
                digit++;
            }
        }

        // Check whether the '#' key (ASCII 35) is pressed to confirm the number.
        else if(val==35)
        {
            // Return the entered number only if at least one digit was entered.
            if(digit>0)
                return num;

            //CmdLCD(0x01);
        }

        // Check whether the '*' key (ASCII 42) is pressed to delete a digit.
        else if(val==42)
        {
            // Delete the last digit only if at least one digit was entered.
            if(digit>0)
            {
                // Decrement the number of entered digits.
                digit--;

                // Move the LCD position back by one character.
                i--;

                // Remove the last digit from the entered number.
                num=num/10;

                // Move the LCD cursor to the position of the last digit.
                CmdLCD(GOTO_LINE2_POS0+i);

                // Erase the last displayed digit by writing a space.
                StrLCD(" ");

                // Move the LCD cursor back to the erased digit position.
                CmdLCD(GOTO_LINE2_POS0+i);
            }
        }
    }
}
