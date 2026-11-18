//RTC.c
// Include the header needed for this module.
#include<lpc21xx.h>
// Include the header needed for this module.
#include<stdio.h>
// Include the header needed for this module.
#include "types.h"
// Include the header needed for this module.
#include "lcd_defines.h"
// Include the header needed for this module.
#include "lcd.h"
// Include the header needed for this module.
#include "rtc.h"
// Include the header needed for this module.
#include "kpm.h"
// Include the header needed for this module.
#include "atm_run.h"
// Include the header needed for this module.
#include<stdlib.h>
// Include the header needed for this module.
#include "delay.h"
//void atm_login(void);
// Define the function that performs this operation.
void InitRTC(void)
{		 
	// Configure the real-time clock control register.
	CCR=0x02;//Reset RTC
	//CCR|=(1<<4);
	//PREINT=0x1C8;
	//PREFRAC=0x61C0;
	/*SEC=30;
	MIN=22;
	HOUR=6;
	DOM=16;
	MONTH=10;
	YEAR=2026;*/
	// Configure the real-time clock control register.
	CCR=0x11;//Start RTC
}
// Define the function that performs this operation.
void set_Hour()
{
	// Declare variables used to store data for this operation.
	u32 hour;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
chg:StrLCD("set Hour");
    // Read a number entered using the keypad.
    hour=set_number();
	// Check this condition before continuing.
	if(hour>0 && hour<24)
	{
	   // Update the selected real-time clock field.
	   HOUR=hour;
	   // Move the LCD cursor to the required display position.
	   CmdLCD(GOTO_LINE2_POS0);
	   // Show this message on the LCD.
	   StrLCD("Updated");
	   // Wait for the requested number of seconds.
	   delay_s(1);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	}
	// Handle the case when the previous condition is false.
	else
	{ 
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Show this message on the LCD.
	   StrLCD("Invalid Hour");
	   // Wait for the requested number of milliseconds.
	   delay_ms(500);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Return to the named input step to try again.
	   goto chg;
	}
}
// Define the function that performs this operation.
void set_Min()
{
	// Declare variables used to store data for this operation.
	u32 min;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
chg:StrLCD("set Min");
    // Read a number entered using the keypad.
    min=set_number();
	// Check this condition before continuing.
	if(min>0 && min<60)
	{
	   // Update the selected real-time clock field.
	   MIN=min;
	   // Move the LCD cursor to the required display position.
	   CmdLCD(GOTO_LINE2_POS0);
	   // Show this message on the LCD.
	   StrLCD("Updated");
	   // Wait for the requested number of seconds.
	   delay_s(1);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	}
	// Handle the case when the previous condition is false.
	else
	{ 
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Show this message on the LCD.
	   StrLCD("Invalid Min");
	   // Wait for the requested number of milliseconds.
	   delay_ms(500);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Return to the named input step to try again.
	   goto chg;
	}
}
// Define the function that performs this operation.
void set_Sec()
{
	// Declare variables used to store data for this operation.
	u32 sec;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
chg:StrLCD("set sec");
    // Read a number entered using the keypad.
    sec=set_number();
	// Check this condition before continuing.
	if(sec>0 && sec<60)
	{
	   // Update the selected real-time clock field.
	   SEC=sec;
	   // Move the LCD cursor to the required display position.
	   CmdLCD(GOTO_LINE2_POS0);
	   // Show this message on the LCD.
	   StrLCD("Updated");
	   // Wait for the requested number of seconds.
	   delay_s(1);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	}
	// Handle the case when the previous condition is false.
	else
	{ 
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Show this message on the LCD.
	   StrLCD("Invalid Sec");
	   // Wait for the requested number of milliseconds.
	   delay_ms(500);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Return to the named input step to try again.
	   goto chg;
	}
}
// Define the function that performs this operation.
void set_Day()
{
    // Declare variables used to store data for this operation.
    u32 date;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
chg:StrLCD("Set Date");
	// Read a number entered using the keypad.
	date=set_number();
	// Check this condition before continuing.
	if(date>0&&date<=31)
	{
	     // Update the selected real-time clock field.
	     DOM=date;
		 // Move the LCD cursor to the required display position.
		 CmdLCD(GOTO_LINE2_POS0);
		 // Show this message on the LCD.
		 StrLCD("Updated");
		 // Wait for the requested number of seconds.
		 delay_s(1);
		 // Clear the LCD before showing new information.
		 CmdLCD(0x01);
    }
	// Handle the case when the previous condition is false.
	else
	{ 
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Show this message on the LCD.
	   StrLCD("Invalid Date");
	   // Wait for the requested number of milliseconds.
	   delay_ms(500);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Return to the named input step to try again.
	   goto chg;
	}
}
// Define the function that performs this operation.
void set_Month()
{
   // Declare variables used to store data for this operation.
   u32 month;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
chg:StrLCD("Set month");
	// Read a number entered using the keypad.
	month=set_number();
	// Check this condition before continuing.
	if(month>0&&month<13)
	{
	     // Update the selected real-time clock field.
	     MONTH=month;
		 // Move the LCD cursor to the required display position.
		 CmdLCD(GOTO_LINE2_POS0);
		 // Show this message on the LCD.
		 StrLCD("Updated");
		 // Wait for the requested number of seconds.
		 delay_s(1);
		 // Clear the LCD before showing new information.
		 CmdLCD(0x01);
    }
	// Handle the case when the previous condition is false.
	else
	{ 
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Show this message on the LCD.
	   StrLCD("Invalid month");
	   // Wait for the requested number of milliseconds.
	   delay_ms(500);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Return to the named input step to try again.
	   goto chg;
	}
}			 
// Define the function that performs this operation.
void set_Year()
{
   // Declare variables used to store data for this operation.
   u32 year;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
chg:StrLCD("Set year");
	// Read a number entered using the keypad.
	year=set_number();
	// Check this condition before continuing.
	if(year>2025 && year<3000)
	{
	     // Update the selected real-time clock field.
	     YEAR=year;
		 // Move the LCD cursor to the required display position.
		 CmdLCD(GOTO_LINE2_POS0);
		 // Show this message on the LCD.
		 StrLCD("Updated");
		 // Wait for the requested number of seconds.
		 delay_s(1);
		 // Clear the LCD before showing new information.
		 CmdLCD(0x01);
    }
	// Handle the case when the previous condition is false.
	else
	{ 
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Show this message on the LCD.
	   StrLCD("Invalid Year");
	   // Wait for the requested number of milliseconds.
	   delay_ms(500);
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
	   // Return to the named input step to try again.
	   goto chg;
	}
}
// Define the function that performs this operation.
void set_Date()
{
     // Declare variables used to store data for this operation.
     u32 n;
     // Clear the LCD before showing new information.
     CmdLCD(0x01);
	 // Repeat these steps while the condition is true.
	 while(1)
	 {
	  		// Show this message on the LCD.
	  		StrLCD("1:DATE 2:MONTH");
			// Move the LCD cursor to the required display position.
			CmdLCD(GOTO_LINE2_POS0);
			// Show this message on the LCD.
			StrLCD("3:YEAR 4:Exit");
			// Read the key pressed on the keypad.
			n=KeyScan();
			// Wait for the requested number of milliseconds.
			delay_ms(500);
			// Choose an action based on the selected value.
			switch(n)
			{
			    // Handle this keypad or menu selection.
			    case 1:set_Day();
					   // Exit the current loop or switch case.
					   break;
				// Handle this keypad or menu selection.
				case 2:set_Month();
						// Exit the current loop or switch case.
						break;
				// Handle this keypad or menu selection.
				case 3:set_Year();
						// Exit the current loop or switch case.
						break;
				// Handle this keypad or menu selection.
				case 4:CmdLCD(0x01);
				       // Finish this function and return to its caller.
				       return;
			}
	 }
}
// Define the function that performs this operation.
void set_Time()
{
     // Declare variables used to store data for this operation.
     u32 n;
     // Clear the LCD before showing new information.
     CmdLCD(0x01);
	 // Repeat these steps while the condition is true.
	 while(1)
	 {
	  		// Show this message on the LCD.
	  		StrLCD("1:HOUR 2:MIN");
			// Move the LCD cursor to the required display position.
			CmdLCD(GOTO_LINE2_POS0);
			// Show this message on the LCD.
			StrLCD("3:SEC 4:Exit");
			// Read the key pressed on the keypad.
			n=KeyScan();
			// Wait for the requested number of milliseconds.
			delay_ms(500);
			// Choose an action based on the selected value.
			switch(n)
			{
			    // Handle this keypad or menu selection.
			    case 1:set_Hour();
					   // Exit the current loop or switch case.
					   break;
				// Handle this keypad or menu selection.
				case 2:set_Min();
						// Exit the current loop or switch case.
						break;
				// Handle this keypad or menu selection.
				case 3:set_Sec();
						// Exit the current loop or switch case.
						break;
				// Handle this keypad or menu selection.
				case 4:CmdLCD(0x01);	
				       // Finish this function and return to its caller.
				       return;
			}
	 }
}
// Define the function that performs this operation.
void RTC_Read(s32 *s,s32 *m,s32 *h,s32 *d,s32 *M,s32 *y)
{
	*s=SEC;
	*m=MIN;
	*h=HOUR;
	*d=DOM;
	*M=MONTH;
	*y=YEAR;
}
// Define the function that performs this operation.
void Display_RTC(void)
{
	// Declare variables used to store data for this operation.
	s32 sec,min,hour;
	// Declare variables used to store data for this operation.
	s32 day,month,year;
    // Declare variables used to store data for this operation.
    char line[17];
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Read the current date and time from the real-time clock.
	RTC_Read(&sec,&min,&hour,&day,&month,&year);
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE1_POS0);
	// Format the transaction or date details as text.
	sprintf(line,"DATE:%02u/%02u/%04u",day,month,year);
	// Show this message on the LCD.
	StrLCD(line);
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE2_POS0);
	// Format the transaction or date details as text.
	sprintf(line,"TIME:%02u:%02u:%02u",hour,min,sec);
	// Show this message on the LCD.
	StrLCD(line);
}
// Define the function that performs this operation.
void Set_date_time(void)
{
	// Declare variables used to store data for this operation.
	u32 val;
   // Clear the LCD before showing new information.
   CmdLCD(0x01);
   // Repeat these steps while the condition is true.
   while(1)
   {
        // Move the LCD cursor to the required display position.
        CmdLCD(GOTO_LINE1_POS0);
   		// Show this message on the LCD.
   		StrLCD("1:Date 2:Time 3:EXIT");
		// Read the key pressed on the keypad.
		val=KeyScan();
		// Wait for the requested number of milliseconds.
		delay_ms(500);
		// Choose an action based on the selected value.
		switch(val)
		{
		   // Handle this keypad or menu selection.
		   case 1:set_Date();
		   		 // Exit the current loop or switch case.
		   		 break;
		   // Handle this keypad or menu selection.
		   case 2:set_Time();
		   		// Exit the current loop or switch case.
		   		break;
		   // Handle this keypad or menu selection.
		   case 3:CmdLCD(0x01);
		          // Finish this function and return to its caller.
		          return;
		}
   }
}
