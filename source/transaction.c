// Include the header needed for this module.
#include "lcd.h"
// Include the header needed for this module.
#include "lcd_defines.h"
// Include the header needed for this module.
#include "kpm.h"
// Include the header needed for this module.
#include "types.h"
// Include the header needed for this module.
#include "transaction.h"
// Include the header needed for this module.
#include "transaction_history.h"
// Include the header needed for this module.
#include "delay.h"
// Include the header needed for this module.
#include "rtc.h"
// Include the header needed for this module.
#include "uart.h"
// Include the header needed for this module.
#include<lpc21xx.h>
// Include the header needed for this module.
#include<stdio.h>

// Declare variables used to store data for this operation.
u32 Bal,amnt;;
// Declare variables used to store data for this operation.
s32 sec,min,hour;
// Declare variables used to store data for this operation.
s32 day,month,year;
// Declare variables used to store data for this operation.
char log[200];
// Define the function that performs this operation.
void Balance(u32 acc_no)
{
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Show the current date and time on the LCD.
	Display_RTC();
	// Wait for the requested number of milliseconds.
	delay_ms(1000);
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE1_POS0);
    // Show this message on the LCD.
    StrLCD("Available Bal..");
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE2_POS0);
    // Display this number on the LCD.
    U32LCD(Bal);
	// Wait for the requested number of seconds.
	delay_s(2);
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Read the current date and time from the real-time clock.
	RTC_Read(&sec,&min,&hour,&day,&month,&year);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("\r\n=======================================================================\r\n");
	// Format the transaction or date details as text.
	sprintf(log,"Account Number:%u\r\n",acc_no);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log); 
	// Format the transaction or date details as text.
	sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Format the transaction or date details as text.
	sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("Transaction      :Balance Enquiry\r\n");
	// Format the transaction or date details as text.
	sprintf(log,"Balance       :%u",Bal);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("\r\n=======================================================================\r\n");
	//sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :BALANCE Rs.%u/-\r\n",day,month,year,hour,min,sec,acc_no,Bal);
	//U0_TxStr(log);
}
// Define the function that performs this operation.
void Withdraw(u32 acc_no)
{
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Show the current date and time on the LCD.
	Display_RTC();
	// Wait for the requested number of milliseconds.
	delay_ms(1000);	
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Show this message on the LCD.
	StrLCD("Avbl 100 200 500 Rs");
	// Wait for the requested number of seconds.
	delay_s(1);
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE1_POS0);
	// Show this message on the LCD.
	StrLCD("Enter Amnt");
	// Read and validate the transaction amount.
	amnt=transaction_amnt();
	// Repeat these steps while the condition is true.
	while(ColScan()==0);
	// Check this condition before continuing.
	if(amnt<=Bal)
	{
	    //u8 log[200];
		// Update this value as part of the current operation.
		Bal-=amnt;
		// Clear the LCD before showing new information.
		CmdLCD(0x01);
		// Move the LCD cursor to the required display position.
		CmdLCD(GOTO_LINE1_POS0);
		// Show this message on the LCD.
		StrLCD("Withdraw success");
		// Wait for the requested number of seconds.
		delay_s(2);
		// Call this function to perform the requested operation.
		Add_History(acc_no,"WITHDRAW",amnt);
	    // Clear the LCD before showing new information.
	    CmdLCD(0x01);
		// Read the current date and time from the real-time clock.
		RTC_Read(&sec,&month,&year,&day,&hour,&min);
		// Send this text to the serial terminal through UART0.
		U0_TxStr("\r\n=======================================================================\r\n");
		// Format the transaction or date details as text.
		sprintf(log,"Account Number:%u\r\n",acc_no);
		// Send this text to the serial terminal through UART0.
		U0_TxStr(log);
		// Format the transaction or date details as text.
		sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);
		// Send this text to the serial terminal through UART0.
		U0_TxStr(log);
		// Format the transaction or date details as text.
		sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);
		// Send this text to the serial terminal through UART0.
		U0_TxStr(log);
		// Send this text to the serial terminal through UART0.
		U0_TxStr("Transaction      :Cash Withdrawal\r\n");
		// Format the transaction or date details as text.
		sprintf(log,"Withdraw Amount:%u\r\n",amnt);
		// Send this text to the serial terminal through UART0.
		U0_TxStr(log);
		// Format the transaction or date details as text.
		sprintf(log,"Total Balance  :%u",Bal);
		// Send this text to the serial terminal through UART0.
		U0_TxStr(log);
		// Send this text to the serial terminal through UART0.
		U0_TxStr("\r\n=======================================================================\r\n");
		//sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] &min,&hour,&day,ACC:%u :WITHDRAW: Rs.%u BALANCE: Rs.%u\r\n",day,month,year,hour,min,sec,acc_no,amnt,Bal);
		//U0_TxStr(log);

	}
	// Handle the case when the previous condition is false.
	else
	{
		// Clear the LCD before showing new information.
		CmdLCD(0x01);
	    // Move the LCD cursor to the required display position.
	    CmdLCD(GOTO_LINE1_POS0);
		// Show this message on the LCD.
		StrLCD("Insufficient Bal..");
		// Set the selected microcontroller output pin HIGH.
		IOSET0=1<<2;
		// Wait for the requested number of milliseconds.
		delay_ms(1000);
		// Set the selected microcontroller output pin LOW.
		IOCLR0=1<<2;
		//delay_ms(500);
		//delay_s(2);
		// Clear the LCD before showing new information.
		CmdLCD(0x01);

		
	}
}


// Define the function that performs this operation.
void Deposit(u32 acc_no)
{
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Show the current date and time on the LCD.
	Display_RTC();
	// Wait for the requested number of milliseconds.
	delay_ms(1000);
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Show this message on the LCD.
	StrLCD("Avbl 100 200 500 Rs");
	// Wait for the requested number of seconds.
	delay_s(1);
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE1_POS0);
	// Show this message on the LCD.
	StrLCD("Enter Amnt");
	// Read and validate the transaction amount.
	amnt=transaction_amnt();
	// Repeat these steps while the condition is true.
	while(ColScan()==0);
	// Update this value as part of the current operation.
	Bal+=amnt;
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Move the LCD cursor to the required display position.
	CmdLCD(GOTO_LINE1_POS0);
	// Show this message on the LCD.
	StrLCD("Deposit success");
	// Wait for the requested number of seconds.
	delay_s(2);
	// Call this function to perform the requested operation.
	Add_History(acc_no,"DEPOSIT",amnt);
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
    // Read the current date and time from the real-time clock.
    RTC_Read(&sec,&min,&hour,&day,&month,&year);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("\r\n=======================================================================\r\n");
	// Format the transaction or date details as text.
	sprintf(log,"Account Number:%u\r\n",acc_no);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Format the transaction or date details as text.
	sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Format the transaction or date details as text.
	sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("Transaction      :Cash Deposit\r\n");
	// Format the transaction or date details as text.
	sprintf(log,"Deposit Amount:%u\r\n",amnt);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Format the transaction or date details as text.
	sprintf(log,"Total Balance :%u\r\n",Bal);
	// Send this text to the serial terminal through UART0.
	U0_TxStr(log);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("\r\n=======================================================================\r\n");

	//sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u DEPOSIT: Rs.%u BALANCE: Rs.%u\r\n",day,month,year,hour,min,sec,acc_no,amnt,Bal);
	//U0_TxStr(log);
}
