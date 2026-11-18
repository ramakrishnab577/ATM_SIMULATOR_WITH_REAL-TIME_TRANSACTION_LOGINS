// Include LPC21xx microcontroller register definitions for RTC operations.
#include <lpc21xx.h>

// Include standard input/output functions.
#include <stdio.h>

// Include user-defined data types such as u32.
#include "types.h"

// Include LCD commands and cursor position definitions.
#include "lcd_defines.h"

// Include LCD function declarations for displaying messages.
#include "lcd.h"

// Include RTC function declarations for date and time operations.
#include "rtc.h"

// Include keypad function declarations for reading user input.
#include "kpm.h"

// Include ATM Simulator function declarations.
#include "atm_run.h"

// Include standard library function declarations.
#include <stdlib.h>

// Include software delay function declarations.
#include "delay.h"

//void atm_login(void);


// Initialize the Real-Time Clock and enable RTC operation.
void InitRTC(void)
{
    // Reset the RTC counter by setting the counter reset bit in CCR.
    CCR=0x02; // Reset RTC

    //CCR|=(1<<4);

    //PREINT=0x1C8;
    //PREFRAC=0x61C0;

    /*SEC=30;
    MIN=22;
    HOUR=6;
    DOM=16;
    MONTH=10;
    YEAR=2026;*/

    // Enable the RTC counter and select the clock source using CCR.
    CCR=0x11; // Start RTC
}


// Read the hour from the keypad and update the RTC hour register.
void set_Hour()
{
    // Declare a variable to store the hour entered by the user.
    u32 hour;

    // Clear the LCD before requesting the hour.
    CmdLCD(0x01);

// Label used to retry hour input when an invalid value is entered.
chg:StrLCD("set Hour");

    // Read the hour value entered through the keypad.
    hour=set_number();

    // Check whether the entered hour is between 1 and 23.
    if(hour>0 && hour<24)
    {
        // Update the RTC hour register with the entered hour.
        HOUR=hour;

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display a message confirming that the hour was updated.
        StrLCD("Updated");

        // Wait for one second to allow the user to read the message.
        delay_s(1);

        // Clear the LCD after updating the hour.
        CmdLCD(0x01);
    }

    // Handle an invalid hour value.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Display an invalid hour message.
        StrLCD("Invalid Hour");

        // Wait for 500 milliseconds before requesting another value.
        delay_ms(500);

        // Clear the LCD before retrying.
        CmdLCD(0x01);

        // Return to the hour input section to enter a valid hour.
        goto chg;
    }
}


// Read the minutes from the keypad and update the RTC minute register.
void set_Min()
{
    // Declare a variable to store the minutes entered by the user.
    u32 min;

    // Clear the LCD before requesting the minutes.
    CmdLCD(0x01);

// Label used to retry minute input when an invalid value is entered.
chg:StrLCD("set Min");

    // Read the minute value entered through the keypad.
    min=set_number();

    // Check whether the entered minute value is between 1 and 59.
    if(min>0 && min<60)
    {
        // Update the RTC minute register with the entered value.
        MIN=min;

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display a message confirming that the minutes were updated.
        StrLCD("Updated");

        // Wait for one second to display the confirmation message.
        delay_s(1);

        // Clear the LCD after updating the minutes.
        CmdLCD(0x01);
    }

    // Handle an invalid minute value.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Display an invalid minute message.
        StrLCD("Invalid Min");

        // Wait for 500 milliseconds before retrying.
        delay_ms(500);

        // Clear the LCD before requesting another minute value.
        CmdLCD(0x01);

        // Return to the minute input section to enter a valid value.
        goto chg;
    }
}


// Read the seconds from the keypad and update the RTC second register.
void set_Sec()
{
    // Declare a variable to store the seconds entered by the user.
    u32 sec;

    // Clear the LCD before requesting the seconds.
    CmdLCD(0x01);

// Label used to retry second input when an invalid value is entered.
chg:StrLCD("set sec");

    // Read the second value entered through the keypad.
    sec=set_number();

    // Check whether the entered second value is between 1 and 59.
    if(sec>0 && sec<60)
    {
        // Update the RTC second register with the entered value.
        SEC=sec;

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display a message confirming that the seconds were updated.
        StrLCD("Updated");

        // Wait for one second to display the confirmation message.
        delay_s(1);

        // Clear the LCD after updating the seconds.
        CmdLCD(0x01);
    }

    // Handle an invalid second value.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Display an invalid second message.
        StrLCD("Invalid Sec");

        // Wait for 500 milliseconds before retrying.
        delay_ms(500);

        // Clear the LCD before requesting another second value.
        CmdLCD(0x01);

        // Return to the second input section to enter a valid value.
        goto chg;
    }
}


// Read the date from the keypad and update the RTC day-of-month register.
void set_Day()
{
    // Declare a variable to store the date entered by the user.
    u32 date;

    // Clear the LCD before requesting the date.
    CmdLCD(0x01);

// Label used to retry date input when an invalid value is entered.
chg:StrLCD("Set Date");

    // Read the date entered through the keypad.
    date=set_number();

    // Check whether the entered date is between 1 and 31.
    if(date>0 && date<=31)
    {
        // Update the RTC day-of-month register with the entered date.
        DOM=date;

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display a message confirming that the date was updated.
        StrLCD("Updated");

        // Wait for one second to display the confirmation message.
        delay_s(1);

        // Clear the LCD after updating the date.
        CmdLCD(0x01);
    }

    // Handle an invalid date value.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Display an invalid date message.
        StrLCD("Invalid Date");

        // Wait for 500 milliseconds before retrying.
        delay_ms(500);

        // Clear the LCD before requesting another date.
        CmdLCD(0x01);

        // Return to the date input section to enter a valid date.
        goto chg;
    }
}
// Read the month from the keypad and update the RTC month register.
void set_Month()
{
    // Declare a variable to store the month entered by the user.
    u32 month;

    // Clear the LCD before requesting the month.
    CmdLCD(0x01);

// Label used to retry month input when an invalid value is entered.
chg:StrLCD("Set month");

    // Read the month value entered through the keypad.
    month=set_number();

    // Check whether the entered month is between 1 and 12.
    if(month>0&&month<13)
    {
        // Update the RTC month register with the entered month.
        MONTH=month;

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display a message confirming that the month was updated.
        StrLCD("Updated");

        // Wait for one second to display the confirmation message.
        delay_s(1);

        // Clear the LCD after updating the month.
        CmdLCD(0x01);
    }

    // Handle an invalid month value.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Display an invalid month message.
        StrLCD("Invalid month");

        // Wait for 500 milliseconds before retrying.
        delay_ms(500);

        // Clear the LCD before requesting another month value.
        CmdLCD(0x01);

        // Return to the month input section to enter a valid month.
        goto chg;
    }
}


// Read the year from the keypad and update the RTC year register.
void set_Year()
{
    // Declare a variable to store the year entered by the user.
    u32 year;

    // Clear the LCD before requesting the year.
    CmdLCD(0x01);

// Label used to retry year input when an invalid value is entered.
chg:StrLCD("Set year");

    // Read the year value entered through the keypad.
    year=set_number();

    // Check whether the entered year is between 2026 and 2999.
    if(year>2025 && year<3000)
    {
        // Update the RTC year register with the entered year.
        YEAR=year;

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display a message confirming that the year was updated.
        StrLCD("Updated");

        // Wait for one second to display the confirmation message.
        delay_s(1);

        // Clear the LCD after updating the year.
        CmdLCD(0x01);
    }

    // Handle an invalid year value.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Display an invalid year message.
        StrLCD("Invalid Year");

        // Wait for 500 milliseconds before retrying.
        delay_ms(500);

        // Clear the LCD before requesting another year value.
        CmdLCD(0x01);

        // Return to the year input section to enter a valid year.
        goto chg;
    }
}


// Display the date-setting menu and allow the user to update date fields.
void set_Date()
{
    // Declare a variable to store the selected date menu option.
    u32 n;

    // Clear the LCD before displaying the date-setting menu.
    CmdLCD(0x01);

    // Continuously display the date menu until the user selects Exit.
    while(1)
    {
        // Display the date and month menu options on the LCD.
        StrLCD("1:DATE 2:MONTH");

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display the year and exit menu options on the LCD.
        StrLCD("3:YEAR 4:Exit");

        // Read the selected menu option from the keypad.
        n=KeyScan();

        // Wait for 500 milliseconds after reading the keypad input.
        delay_ms(500);

        // Execute the corresponding date-setting operation.
        switch(n)
        {
            // Select option 1 to update the RTC day of the month.
            case 1:set_Day();

                   // Exit the current switch case after updating the date.
                   break;

            // Select option 2 to update the RTC month.
            case 2:set_Month();

                   // Exit the current switch case after updating the month.
                   break;

            // Select option 3 to update the RTC year.
            case 3:set_Year();

                   // Exit the current switch case after updating the year.
                   break;

            // Select option 4 to exit the date-setting menu.
            case 4:CmdLCD(0x01);

                   // Return to the calling function.
                   return;
        }
    }
}


// Display the time-setting menu and allow the user to update time fields.
void set_Time()
{
    // Declare a variable to store the selected time menu option.
    u32 n;

    // Clear the LCD before displaying the time-setting menu.
    CmdLCD(0x01);

    // Continuously display the time menu until the user selects Exit.
    while(1)
    {
        // Display the hour and minute menu options on the LCD.
        StrLCD("1:HOUR 2:MIN");

        // Move the LCD cursor to the beginning of the second line.
        CmdLCD(GOTO_LINE2_POS0);

        // Display the second and exit menu options on the LCD.
        StrLCD("3:SEC 4:Exit");

        // Read the selected menu option from the keypad.
        n=KeyScan();

        // Wait for 500 milliseconds after reading the keypad input.
        delay_ms(500);

        // Execute the corresponding time-setting operation.
        switch(n)
        {
            // Select option 1 to update the RTC hour.
            case 1:set_Hour();

                   // Exit the current switch case after updating the hour.
                   break;

            // Select option 2 to update the RTC minutes.
            case 2:set_Min();

                   // Exit the current switch case after updating the minutes.
                   break;

            // Select option 3 to update the RTC seconds.
            case 3:set_Sec();

                   // Exit the current switch case after updating the seconds.
                   break;

            // Select option 4 to exit the time-setting menu.
            case 4:CmdLCD(0x01);

                   // Return to the calling function.
                   return;
        }
    }
}


// Read the current date and time from the RTC registers.
void RTC_Read(s32 *s,s32 *m,s32 *h,s32 *d,s32 *M,s32 *y)
{
    // Read the RTC seconds register and store its value at the supplied address.
    *s=SEC;

    // Read the RTC minutes register and store its value at the supplied address.
    *m=MIN;

    // Read the RTC hours register and store its value at the supplied address.
    *h=HOUR;

    // Read the RTC day-of-month register and store its value at the supplied address.
    *d=DOM;

    // Read the RTC month register and store its value at the supplied address.
    *M=MONTH;

    // Read the RTC year register and store its value at the supplied address.
    *y=YEAR;
}


// Read the current RTC date and time and display them on the LCD.
void Display_RTC(void)
{
    // Declare variables to store the current seconds, minutes, and hours.
    s32 sec,min,hour;

    // Declare variables to store the current day, month, and year.
    s32 day,month,year;

    // Declare a character array to store the formatted LCD display text.
    char line[17];

    // Clear the LCD before displaying the current date and time.
    CmdLCD(0x01);

    // Read the current date and time from the RTC registers.
    RTC_Read(&sec,&min,&hour,&day,&month,&year);

    // Move the LCD cursor to the first position of the first line.
    CmdLCD(GOTO_LINE1_POS0);

    // Format the date as DATE:DD/MM/YYYY and store it in the character array.
    sprintf(line,"DATE:%02u/%02u/%04u",day,month,year);

    // Display the formatted date on the first line of the LCD.
    StrLCD(line);

    // Move the LCD cursor to the first position of the second line.
    CmdLCD(GOTO_LINE2_POS0);

    // Format the time as TIME:HH:MM:SS and store it in the character array.
    sprintf(line,"TIME:%02u:%02u:%02u",hour,min,sec);

    // Display the formatted time on the second line of the LCD.
    StrLCD(line);
}


// Display the RTC settings menu to select date or time configuration.
void Set_date_time(void)
{
    // Declare a variable to store the selected RTC settings menu option.
    u32 val;

    // Clear the LCD before displaying the RTC settings menu.
    CmdLCD(0x01);

    // Continuously display the RTC settings menu until Exit is selected.
    while(1)
    {
        // Move the LCD cursor to the first position of the first line.
        CmdLCD(GOTO_LINE1_POS0);

        // Display the date, time, and exit options on the LCD.
        StrLCD("1:Date 2:Time 3:EXIT");

        // Read the selected menu option from the keypad.
        val=KeyScan();

        // Wait for 500 milliseconds after reading the keypad input.
        delay_ms(500);

        // Execute the corresponding RTC configuration operation.
        switch(val)
        {
            // Select option 1 to open the date-setting menu.
            case 1:set_Date();

                   // Exit the current switch case after returning from the date menu.
                   break;

            // Select option 2 to open the time-setting menu.
            case 2:set_Time();

                   // Exit the current switch case after returning from the time menu.
                   break;

            // Select option 3 to exit the RTC settings menu.
            case 3:CmdLCD(0x01);

                   // Return to the calling function.
                   return;
        }
    }
}
