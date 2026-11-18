// Include the header needed for this module.
#include "lcd.h"
// Include the header needed for this module.
#include "lcd_defines.h"
// Include the header needed for this module.
#include "kpm.h"
// Include the header needed for this module.
#include "delay.h"
// Include the header needed for this module.
#include "transaction.h"
// Include the header needed for this module.
#include "transaction_history.h"
// Include the header needed for this module.
#include "uart.h"
// Include the header needed for this module.
#include "interrupt.h"
// Include the header needed for this module.
#include "rtc.h"
// Include the header needed for this module.
#include "atm_run.h"
// Include the header needed for this module.
#include "types.h"

// Give a readable name to a fixed value or setting.
#define ACC_NO 1111
// Give a readable name to a fixed value or setting.
#define MAX 3
// Include the header needed for this module.
#include<stdio.h>
// Include the header needed for this module.
#include<lpc21xx.h>
//extern volatile int flag;

// Declare shared data used by more than one function.
extern s32 sec,min,hour;
// Declare shared data used by more than one function.
extern s32 day,month,year;
// Declare shared data used by more than one function.
extern char log[200];
//volatile unsigned char flag=0;

// Declare variables used to store data for this operation.
u32 PIN=3333;
// Declare variables used to store data for this operation.
u32 acc_num,pin,cnt=0,val;

// Define the function that performs this operation.
int atm_login()
{
	// Configure the selected GPIO pins as inputs or outputs.
	IODIR0|=1<<2;
	// Set the selected microcontroller output pin LOW.
	IOCLR0=1<<2;
	// Repeat these steps while the condition is true.
	while(1)
	{
	   // Show this message on the LCD.
	   StrLCD("Welcome!....");
	   // Move the LCD cursor to the required display position.
	   CmdLCD(GOTO_LINE2_POS0);
	   // Show this message on the LCD.
	   StrLCD("ATM SIMULATOR!...");
	   // Wait for the requested number of seconds.
	   delay_s(1);
		// Repeat these steps while the condition is true.
		while(1)
		{
		    // Show the current date and time on the LCD.
		    Display_RTC();
			// Check this condition before continuing.
			if(flag==1)
	   		{
	       		// Call this function to perform the requested operation.
	       		Set_date_time();
		   		// Update this value as part of the current operation.
		   		flag=0;
	   		}
			// Wait for the requested number of seconds.
			delay_s(2);
			// Exit the current loop or switch case.
			break;
		}
	    // Clear the LCD before showing new information.
	    CmdLCD(0x01);
// Entry point used when the user needs to retry.
acc:   CmdLCD(GOTO_LINE1_POS0);
	    // Show this message on the LCD.
	    StrLCD("Enter Account No");
		// Read a number entered using the keypad.
		acc_num=set_number();
		// Clear the LCD before showing new information.
		CmdLCD(0x01);
		// Check this condition before continuing.
		if(ACC_NO!=acc_num)
		// Call this function to perform the requested operation.
		{	CmdLCD(GOTO_LINE1_POS0);
			// Show this message on the LCD.
			StrLCD("INVALID ACC NO");
			// Wait for the requested number of seconds.
			delay_s(3);
			// Clear the LCD before showing new information.
			CmdLCD(0x01);
			// Return to the named input step to try again.
			goto acc;
		}
		// Handle the case when the previous condition is false.
		else 
		{
		    // Clear the LCD before showing new information.
		    CmdLCD(0x01);
// Entry point used when the user needs to retry.
pwd:	    CmdLCD(GOTO_LINE1_POS0);
	    	// Show this message on the LCD.
	    	StrLCD("Enter Pin");
		    // Read the PIN from the keypad while hiding the entered digits.
		    pin=Read_Password();
			// Clear the LCD before showing new information.
			CmdLCD(0x01);
			// Check this condition before continuing.
			if(pin==PIN)
			{
			  // Move the LCD cursor to the required display position.
			  CmdLCD(GOTO_LINE1_POS0);
			  // Show this message on the LCD.
			  StrLCD("LOGIN SUCCESS");
			  // Read the current date and time from the real-time clock.
			  RTC_Read(&sec,&min,&hour,&day,&month,&year);
			  // Send this text to the serial terminal through UART0.
			  U0_TxStr("\r\n=======================================================================\r\n");
			  // Format the transaction or date details as text.
			  sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :LOGIN SUCCESS\r\n",day,month,year,hour,min,sec,acc_num);
		   	  // Send this text to the serial terminal through UART0.
		   	  U0_TxStr(log);
			  // Send this text to the serial terminal through UART0.
			  U0_TxStr("\r\n=======================================================================\r\n");
			  // Wait for the requested number of seconds.
			  delay_s(2);
			  // Clear the LCD before showing new information.
			  CmdLCD(0x01);
			   // Finish this function and return to its caller.
			   return 1;
			}
			// Handle the case when the previous condition is false.
			else
			{
			   // Move the LCD cursor to the required display position.
			   CmdLCD(GOTO_LINE1_POS0);
			   // Show this message on the LCD.
			   StrLCD("INVALID PASSWORD");
			   // Wait for the requested number of seconds.
			   delay_s(2);
			   // Clear the LCD before showing new information.
			   CmdLCD(0x01);
			   cnt++;
			   // Check this condition before continuing.
			   if(cnt==MAX)
			   {
			     // Move the LCD cursor to the required display position.
			     CmdLCD(GOTO_LINE1_POS0);
			     // Show this message on the LCD.
			     StrLCD("TRY AFTER 24Hrs!..");
				 // Set the selected microcontroller output pin HIGH.
				 IOSET0=1<<2;
				 // Wait for the requested number of milliseconds.
				 delay_ms(500);
				 // Set the selected microcontroller output pin LOW.
				 IOCLR0=1<<2;
				 //delay_ms(500);
				 // Clear the LCD before showing new information.
				 CmdLCD(0x01);	
			   }
			   // Handle the case when the previous condition is false.
			   else
			   {
			   		// Return to the named input step to try again.
			   		goto pwd;
			   }	
			}		 
		}
	}		
}
// Define the function that performs this operation.
void change_pin()
{
    // Declare variables used to store data for this operation.
    u32 old_pin,new_pin;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
// Entry point used when the user needs to retry.
old:StrLCD("Enter old pin");
    // Read the PIN from the keypad while hiding the entered digits.
    old_pin=Read_Password();
    // Check this condition before continuing.
    if(old_pin==PIN)
    {
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
       // Show this message on the LCD.
       StrLCD("Enter new pin");
       // Read the PIN from the keypad while hiding the entered digits.
       new_pin=Read_Password();
       // Update this value as part of the current operation.
       PIN=new_pin;
       // Clear the LCD before showing new information.
       CmdLCD(0x01);
	   // Read the current date and time from the real-time clock.
	   RTC_Read(&sec,&min,&hour,&day,&month,&year);
	   // Send this text to the serial terminal through UART0.
	   U0_TxStr("\r\n=======================================================================\r\n");
	   // Format the transaction or date details as text.
	   sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :PIN CHANGED SUCCESSFULLY\r\n",day,month,year,hour,min,sec,ACC_NO);
	   // Send this text to the serial terminal through UART0.
	   U0_TxStr(log);
	   // Send this text to the serial terminal through UART0.
	   U0_TxStr("\r\n=======================================================================\r\n");
       // Show this message on the LCD.
       StrLCD("chg successful");
    
    }
    // Handle the case when the previous condition is false.
    else
    {
       // Clear the LCD before showing new information.
       CmdLCD(0x01);
       // Show this message on the LCD.
       StrLCD("Invalid Pin");
	   // Clear the LCD before showing new information.
	   CmdLCD(0x01);
       // Return to the named input step to try again.
       goto old;
    }

}
// Define the function that performs this operation.
void atm_menu()
{
			  // Repeat these steps while the condition is true.
			  while(1)
			  {
			  		// Check this condition before continuing.
			  		if(flag==1)
	 				{
	    				// Call this function to perform the requested operation.
	    				Set_date_time();
						// Update this value as part of the current operation.
						flag=0;
	 				}
			         // Move the LCD cursor to the required display position.
			         CmdLCD(GOTO_LINE1_POS0);
					 // Show this message on the LCD.
					 StrLCD("1.BAL 2.WDL 3.DEP");
					 // Move the LCD cursor to the required display position.
					 CmdLCD(GOTO_LINE2_POS0);
					 // Show this message on the LCD.
					 StrLCD("4.PIN CHG 5.TRF 6.EX");
					 // Wait for the requested number of seconds.
					 delay_s(1);
			  		 // Read the key pressed on the keypad.
			  		 val=KeyScan();
					 // Clear the LCD before showing new information.
					 CmdLCD(0x01);
					 // Repeat these steps while the condition is true.
					 while(ColScan()==0);
					 // Choose an action based on the selected value.
					 switch(val)
					 {
					 	// Handle this keypad or menu selection.
					 	case 1:Balance(ACC_NO);
						       // Exit the current loop or switch case.
						       break;
						// Handle this keypad or menu selection.
						case 2:Withdraw(ACC_NO);
							   // Exit the current loop or switch case.
							   break;
						// Handle this keypad or menu selection.
						case 3:Deposit(ACC_NO);
							   // Exit the current loop or switch case.
							   break;
						// Handle this keypad or menu selection.
						case 4:change_pin();
							   // Exit the current loop or switch case.
							   break;
						// Handle this keypad or menu selection.
						case 5:Display_History();
							   // Exit the current loop or switch case.
							   break;
						// Handle this keypad or menu selection.
						case 6:break;	
					 }
					 // Check this condition before continuing.
					 if(val==6)
					 {
					   	// Read the current date and time from the real-time clock.
					   	RTC_Read(&sec,&min,&hour,&day,&month,&year);
						// Send this text to the serial terminal through UART0.
						U0_TxStr("\r\n=======================================================================\r\n");
			  			// Format the transaction or date details as text.
			  			sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :LOGOUT\r\n",day,month,year,hour,min,sec,ACC_NO);
		   	  			// Send this text to the serial terminal through UART0.
		   	  			U0_TxStr(log);
						// Clear the LCD before showing new information.
						CmdLCD(0x01);
						// Send this text to the serial terminal through UART0.
						U0_TxStr("\r\n=======================================================================\r\n");
						// Show this message on the LCD.
						StrLCD("THANK YOU!.....");
						// Send this text to the serial terminal through UART0.
						U0_TxStr("THANK YOU!...........\r\n\r\n");
						// Wait for the requested number of seconds.
						delay_s(1);
						// Clear the LCD before showing new information.
						CmdLCD(0x01);
					 	// Exit the current loop or switch case.
					 	break;
					 }
					// Check this condition before continuing.
					if(flag==1)
	   				{
	       				// Call this function to perform the requested operation.
	       				Set_date_time();
		   				// Update this value as part of the current operation.
		   				flag=0;
	   				}
			  }
}
// Define the function that performs this operation.
void atm_run()
{
  // Repeat these steps while the condition is true.
  while(1)
  {
     // Check this condition before continuing.
     if(flag==1)
	 {
	    // Call this function to perform the requested operation.
	    Set_date_time();
		// Update this value as part of the current operation.
		flag=0;
	 }
	// Check this condition before continuing.
	if(atm_login())
	{
		// Call this function to perform the requested operation.
		atm_menu();
    }
  }
}
