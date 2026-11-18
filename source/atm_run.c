//atm_run.c
// Include declarations for LCD control and display functions.
#include "lcd.h"
// Include declarations for LCD commands and pin definitions.
#include "lcd_defines.h"
// Include declarations for matrix keypad scanning and input functions.
#include "kpm.h"
// Include declarations for millisecond and second delay functions.
#include "delay.h"
// Include declarations for balance, withdrawal, and deposit functions.
#include "transaction.h"
// Include declarations for transaction history display functions.
#include "transaction_history.h"
// Include declarations for UART serial transmission functions.
#include "uart.h"
// Include declarations for interrupt-related declarations.
#include "interrupt.h"
// Include declarations for real-time clock functions.
#include "rtc.h"
// Include declarations for ATM application function declarations.
#include "atm_run.h"
// Include declarations for fixed-width integer type aliases.
#include "types.h"

// Define the account number accepted by this ATM simulation.
#define ACC_NO 1111
// Set the maximum number of incorrect PIN attempts to three.
#define MAX 3
// Include declarations for standard input/output functions such as sprintf.
#include<stdio.h>
// Include declarations for LPC21xx GPIO and peripheral register definitions.
#include<lpc21xx.h>
extern volatile int flag;

// Access RTC time values defined in another source file.
extern s32 sec,min,hour;
// Access RTC date values defined in another source file.
extern s32 day,month,year;
// Access the shared buffer used to format UART transaction logs.
extern char log[200];
//volatile unsigned char flag=0;

// Initialize the account PIN to 3333.
u32 PIN=3333;
// Store the entered account number, entered PIN, failed-attempt count, and menu choice.
u32 acc_num,pin,cnt=0,val;

// Start the ATM login process and return 1 after successful authentication.
int atm_login()
{
	// Configure GPIO P0.2 as an output.
	IODIR0|=1<<2;
	// Drive P0.2 LOW.
	IOCLR0=1<<2;
	// Keep processing this ATM stage until an explicit exit occurs.
	while(1)
	{
	   // Display the ATM welcome message on the LCD.
	   StrLCD("Welcome!....");
	   // Position the LCD cursor at the beginning of line 2.
	   CmdLCD(GOTO_LINE2_POS0);
	   // Display the ATM simulator title on the second LCD line.
	   StrLCD("ATM SIMULATOR!...");
	   // Wait one second.
	   delay_s(1);
		// Keep processing this ATM stage until an explicit exit occurs.
		while(1)
		{
		    // Display the current RTC date and time on the LCD.
		    Display_RTC();
			// Check whether the date/time update flag has been set.
			if(flag==1)
	   		{
	       		// Run the date/time-setting routine when the interrupt flag is set.
	       		Set_date_time();
		   		// Clear the interrupt/event flag after handling it.
		   		flag=0;
	   		}
			// Wait two seconds.
			delay_s(2);
			// Exit the current loop or switch branch.
			break;
		}
	    // Clear the LCD screen before the next display.
	    CmdLCD(0x01);
// Mark the account-number retry point and move the LCD cursor to line 1.
acc:   CmdLCD(GOTO_LINE1_POS0);
	    // Prompt the user to enter the account number.
	    StrLCD("Enter Account No");
		// Read the account number from the keypad.
		acc_num=set_number();
		// Clear the LCD screen before the next display.
		CmdLCD(0x01);
		// Reject an account number that does not match ACC_NO.
		if(ACC_NO!=acc_num)
		// Call this function to perform the requested operation.
		{	CmdLCD(GOTO_LINE1_POS0);
			// Display an invalid-account-number message.
			StrLCD("INVALID ACC NO");
			// Wait three seconds.
			delay_s(3);
			// Clear the LCD screen before the next display.
			CmdLCD(0x01);
			// Repeat account-number entry after a mismatch.
			goto acc;
		}
		// Handle the case where the preceding condition is false.
		else 
		{
		    // Clear the LCD screen before the next display.
		    CmdLCD(0x01);
// Mark the PIN retry point and move the LCD cursor to line 1.
pwd:	    CmdLCD(GOTO_LINE1_POS0);
	    	// Prompt the user to enter the account PIN.
	    	StrLCD("Enter Pin");
		    // Read the masked PIN from the keypad.
		    pin=Read_Password();
			// Clear the LCD screen before the next display.
			CmdLCD(0x01);
			// Check whether the entered PIN matches the stored PIN.
			if(pin==PIN)
			{
			  // Position the LCD cursor at the beginning of line 1.
			  CmdLCD(GOTO_LINE1_POS0);
			  // Confirm successful PIN authentication on the LCD.
			  StrLCD("LOGIN SUCCESS");
			  // Read the current RTC date and time for the event log.
			  RTC_Read(&sec,&min,&hour,&day,&month,&year);
			  // Print a separator line to the UART terminal.
			  U0_TxStr("\r\n=======================================================================\r\n");
			  // Format the timestamp, account number, and login success event for the UART log.
			  sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :LOGIN SUCCESS\r\n",day,month,year,hour,min,sec,acc_num);
		   	  // Transmit the formatted event log over UART0.
		   	  U0_TxStr(log);
			  // Print a separator line to the UART terminal.
			  U0_TxStr("\r\n=======================================================================\r\n");
			  // Wait two seconds.
			  delay_s(2);
			  // Clear the LCD screen before the next display.
			  CmdLCD(0x01);
			   // Report a successful login to the caller.
			   return 1;
			}
			// Handle the case where the preceding condition is false.
			else
			{
			   // Position the LCD cursor at the beginning of line 1.
			   CmdLCD(GOTO_LINE1_POS0);
			   // Notify the user that the entered PIN is incorrect.
			   StrLCD("INVALID PASSWORD");
			   // Wait two seconds.
			   delay_s(2);
			   // Clear the LCD screen before the next display.
			   CmdLCD(0x01);
			   cnt++;
			   // Check whether the failed-PIN attempt limit has been reached.
			   if(cnt==MAX)
			   {
			     // Position the LCD cursor at the beginning of line 1.
			     CmdLCD(GOTO_LINE1_POS0);
			     // Display the lockout warning after three failed attempts.
			     StrLCD("TRY AFTER 24Hrs!..");
				 // Drive P0.2 HIGH after the maximum number of failed PIN attempts.
				 IOSET0=1<<2;
				 // Wait 500 milliseconds.
				 delay_ms(500);
				 // Drive P0.2 LOW.
				 IOCLR0=1<<2;
				 //delay_ms(500);
				 // Clear the LCD screen before the next display.
				 CmdLCD(0x01);	
			   }
			   // Handle the case where the preceding condition is false.
			   else
			   {
			   		// Allow another PIN entry while attempts remain.
			   		goto pwd;
			   }	
			}		 
		}
	}		
}
// Verify the old PIN and replace it with a new PIN.
void change_pin()
{
    // Declare variables used to store data for this operation.
    u32 old_pin,new_pin;
	// Clear the LCD screen before the next display.
	CmdLCD(0x01);
// Mark the old-PIN retry point and prompt for the current PIN.
old:StrLCD("Enter old pin");
    // Read the current PIN from the keypad.
    old_pin=Read_Password();
    // Verify that the old PIN matches the stored PIN.
    if(old_pin==PIN)
    {
	   // Clear the LCD screen before the next display.
	   CmdLCD(0x01);
       // Prompt the user to enter a replacement PIN.
       StrLCD("Enter new pin");
       // Read the new PIN from the keypad.
       new_pin=Read_Password();
       // Update the stored PIN with the new value.
       PIN=new_pin;
       // Clear the LCD screen before the next display.
       CmdLCD(0x01);
	   // Read the current RTC date and time for the event log.
	   RTC_Read(&sec,&min,&hour,&day,&month,&year);
	   // Print a separator line to the UART terminal.
	   U0_TxStr("\r\n=======================================================================\r\n");
	   // Format the timestamp, account number, and PIN change event for the UART log.
	   sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :PIN CHANGED SUCCESSFULLY\r\n",day,month,year,hour,min,sec,ACC_NO);
	   // Transmit the formatted event log over UART0.
	   U0_TxStr(log);
	   // Print a separator line to the UART terminal.
	   U0_TxStr("\r\n=======================================================================\r\n");
       // Show confirmation that the PIN was changed.
       StrLCD("chg successful");
    
    }
    // Handle the case where the preceding condition is false.
    else
    {
       // Clear the LCD screen before the next display.
       CmdLCD(0x01);
       // Display an error when the old PIN is incorrect.
       StrLCD("Invalid Pin");
	   // Clear the LCD screen before the next display.
	   CmdLCD(0x01);
       // Return to old-PIN entry after a mismatch.
       goto old;
    }

}
// Display the ATM menu and process keypad selections until logout.
void atm_menu()
{
			  // Keep processing this ATM stage until an explicit exit occurs.
			  while(1)
			  {
			  		// Check whether the date/time update flag has been set.
			  		if(flag==1)
	 				{
	    				// Run the date/time-setting routine when the interrupt flag is set.
	    				Set_date_time();
						// Clear the interrupt/event flag after handling it.
						flag=0;
	 				}
			         // Position the LCD cursor at the beginning of line 1.
			         CmdLCD(GOTO_LINE1_POS0);
					 // Display balance, withdrawal, and deposit menu options.
					 StrLCD("1.BAL 2.WDL 3.DEP");
					 // Position the LCD cursor at the beginning of line 2.
					 CmdLCD(GOTO_LINE2_POS0);
					 // Display PIN change, history/transfer label, and exit options.
					 StrLCD("4.PIN CHG 5.TRF 6.EX");
					 // Wait one second.
					 delay_s(1);
			  		 // Read the selected menu key from the keypad.
			  		 val=KeyScan();
					 // Clear the LCD screen before the next display.
					 CmdLCD(0x01);
					 // Wait until the keypad column scan condition changes.
					 while(ColScan()==0);
					 // Dispatch the ATM operation selected by the keypad.
					 switch(val)
					 {
					 	// Option 1: display the account balance.
					 	case 1:Balance(ACC_NO);
						       // Exit the current loop or switch branch.
						       break;
						// Option 2: perform a withdrawal.
						case 2:Withdraw(ACC_NO);
							   // Exit the current loop or switch branch.
							   break;
						// Option 3: perform a deposit.
						case 3:Deposit(ACC_NO);
							   // Exit the current loop or switch branch.
							   break;
						// Option 4: change the account PIN.
						case 4:change_pin();
							   // Exit the current loop or switch branch.
							   break;
						// Option 5: display transaction history.
						case 5:Display_History();
							   // Exit the current loop or switch branch.
							   break;
						// Option 6: leave the menu switch and proceed to logout.
						case 6:break;	
					 }
					 // Check whether the user selected the logout option.
					 if(val==6)
					 {
					   	// Read the current RTC date and time for the event log.
					   	RTC_Read(&sec,&min,&hour,&day,&month,&year);
						// Print a separator line to the UART terminal.
						U0_TxStr("\r\n=======================================================================\r\n");
			  			// Format the timestamp, account number, and logout event for the UART log.
			  			sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :LOGOUT\r\n",day,month,year,hour,min,sec,ACC_NO);
		   	  			// Transmit the formatted event log over UART0.
		   	  			U0_TxStr(log);
						// Clear the LCD screen before the next display.
						CmdLCD(0x01);
						// Print a separator line to the UART terminal.
						U0_TxStr("\r\n=======================================================================\r\n");
						// Display the farewell message on the LCD.
						StrLCD("THANK YOU!.....");
						// Send the farewell message to the UART terminal.
						U0_TxStr("THANK YOU!...........\r\n\r\n");
						// Wait one second.
						delay_s(1);
						// Clear the LCD screen before the next display.
						CmdLCD(0x01);
					 	// Exit the current loop or switch branch.
					 	break;
					 }
					// Check whether the date/time update flag has been set.
					if(flag==1)
	   				{
	       				// Run the date/time-setting routine when the interrupt flag is set.
	       				Set_date_time();
		   				// Clear the interrupt/event flag after handling it.
		   				flag=0;
	   				}
			  }
}
// Continuously handle ATM login and menu sessions.
void atm_run()
{
  // Keep processing this ATM stage until an explicit exit occurs.
  while(1)
  {
     // Check whether the date/time update flag has been set.
     if(flag==1)
	 {
	    // Run the date/time-setting routine when the interrupt flag is set.
	    Set_date_time();
		// Clear the interrupt/event flag after handling it.
		flag=0;
	 }
	// Open the ATM menu only after a successful login.
	if(atm_login())
	{
		// Call this function to perform the requested operation.
		atm_menu();
    }
  }
}
