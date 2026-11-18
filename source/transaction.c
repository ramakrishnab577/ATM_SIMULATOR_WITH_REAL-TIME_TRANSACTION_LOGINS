// Include LCD function declarations for displaying messages and numbers.
#include "lcd.h"

// Include LCD command definitions and cursor position macros.
#include "lcd_defines.h"

// Include keypad functions for reading transaction amounts.
#include "kpm.h"

// Include user-defined data types such as u32 and s32.
#include "types.h"

// Include transaction function declarations for ATM operations.
#include "transaction.h"

// Include transaction history functions for recording transactions.
#include "transaction_history.h"

// Include software delay function declarations.
#include "delay.h"

// Include RTC functions for reading and displaying date and time.
#include "rtc.h"

// Include UART functions for printing transaction details.
#include "uart.h"

// Include LPC21xx microcontroller register definitions.
#include <lpc21xx.h>

// Include standard input/output functions for sprintf().
#include <stdio.h>


// Declare global variables to store the account balance and transaction amount.
u32 Bal,amnt;;

// Declare global variables to store the current RTC time.
s32 sec,min,hour;

// Declare global variables to store the current RTC date.
s32 day,month,year;

// Declare a character buffer for formatting UART transaction messages.
char log[200];


// Display the available account balance on the LCD and UART terminal.
void Balance(u32 acc_no)
{
    // Clear the LCD before displaying account information.
    CmdLCD(0x01);

    // Display the current RTC date and time on the LCD.
    Display_RTC();

    // Wait for one second so the user can view the date and time.
    delay_ms(1000);

    // Clear the LCD before displaying the available balance.
    CmdLCD(0x01);

    // Move the LCD cursor to the beginning of the first line.
    CmdLCD(GOTO_LINE1_POS0);

    // Display the available balance heading on the LCD.
    StrLCD("Available Bal..");

    // Move the LCD cursor to the beginning of the second line.
    CmdLCD(GOTO_LINE2_POS0);

    // Display the current account balance as an unsigned integer.
    U32LCD(Bal);

    // Wait for two seconds so the user can view the balance.
    delay_s(2);

    // Clear the LCD after displaying the balance.
    CmdLCD(0x01);

    // Read the current date and time from the RTC registers.
    RTC_Read(&sec,&min,&hour,&day,&month,&year);

    // Print a separator line before the balance enquiry details.
    U0_TxStr("\r\n=======================================================================\r\n");

    // Format the account number into the UART message buffer.
    sprintf(log,"Account Number:%u\r\n",acc_no);

    // Print the account number on the UART serial terminal.
    U0_TxStr(log);

    // Format the current date in DD-MM-YYYY format.
    sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);

    // Print the transaction date on the UART terminal.
    U0_TxStr(log);

    // Format the current time in HH:MM:SS format.
    sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);

    // Print the transaction time on the UART terminal.
    U0_TxStr(log);

    // Print the transaction type as Balance Enquiry.
    U0_TxStr("Transaction      :Balance Enquiry\r\n");

    // Format the current account balance into the UART message buffer.
    sprintf(log,"Balance       :%u",Bal);

    // Print the available account balance on the UART terminal.
    U0_TxStr(log);

    // Print a separator line after the balance enquiry details.
    U0_TxStr("\r\n=======================================================================\r\n");
}
// Withdraw money from the account after checking the available balance.
void Withdraw(u32 acc_no)
{
    // Clear the LCD before starting the withdrawal operation.
    CmdLCD(0x01);

    // Display the current RTC date and time on the LCD.
    Display_RTC();

    // Wait for one second so the user can view the date and time.
    delay_ms(1000);

    // Clear the LCD before displaying available currency denominations.
    CmdLCD(0x01);

    // Display the available currency denominations for withdrawal.
    StrLCD("Avbl 100 200 500 Rs");

    // Wait for one second before requesting the withdrawal amount.
    delay_s(1);

    // Clear the LCD before accepting the withdrawal amount.
    CmdLCD(0x01);

    // Move the LCD cursor to the beginning of the first line.
    CmdLCD(GOTO_LINE1_POS0);

    // Prompt the user to enter the withdrawal amount.
    StrLCD("Enter Amnt");

    // Read and validate the withdrawal amount entered through the keypad.
    amnt=transaction_amnt();

    // Wait until the pressed keypad key is released.
    while(ColScan()==0);

    // Check whether the requested withdrawal amount is within the available balance.
    if(amnt<=Bal)
    {
        //u8 log[200];

        // Deduct the withdrawal amount from the available account balance.
        Bal-=amnt;

        // Clear the LCD before displaying the withdrawal status.
        CmdLCD(0x01);

        // Move the LCD cursor to the beginning of the first line.
        CmdLCD(GOTO_LINE1_POS0);

        // Display a message confirming successful withdrawal.
        StrLCD("Withdraw success");

        // Wait for two seconds so the user can view the success message.
        delay_s(2);

        // Store the withdrawal details in the transaction history.
        Add_History(acc_no,"WITHDRAW",amnt);

        // Clear the LCD after completing the withdrawal.
        CmdLCD(0x01);

        // Read the RTC values into the supplied variables.
        RTC_Read(&sec,&month,&year,&day,&hour,&min);

        // Print a separator line before the withdrawal receipt.
        U0_TxStr("\r\n=======================================================================\r\n");

        // Format the account number into the UART message buffer.
        sprintf(log,"Account Number:%u\r\n",acc_no);

        // Print the account number on the UART terminal.
        U0_TxStr(log);

        // Format the transaction date in DD-MM-YYYY format.
        sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);

        // Print the transaction date on the UART terminal.
        U0_TxStr(log);

        // Format the transaction time in HH:MM:SS format.
        sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);

        // Print the transaction time on the UART terminal.
        U0_TxStr(log);

        // Print the transaction type as Cash Withdrawal.
        U0_TxStr("Transaction      :Cash Withdrawal\r\n");

        // Format the successfully withdrawn amount.
        sprintf(log,"Withdraw Amount:%u\r\n",amnt);

        // Print the withdrawal amount on the UART terminal.
        U0_TxStr(log);

        // Format the remaining account balance after withdrawal.
        sprintf(log,"Total Balance  :%u",Bal);

        // Print the remaining balance on the UART terminal.
        U0_TxStr(log);

        // Print a separator line after the withdrawal receipt.
        U0_TxStr("\r\n=======================================================================\r\n");
    }

    // Handle the withdrawal request when the account balance is insufficient.
    else
    {
        // Clear the LCD before displaying the error message.
        CmdLCD(0x01);

        // Move the LCD cursor to the beginning of the first line.
        CmdLCD(GOTO_LINE1_POS0);

        // Display an insufficient balance warning on the LCD.
        StrLCD("Insufficient Bal..");

        // Set GPIO P0.2 HIGH to activate the connected warning output.
        IOSET0=1<<2;

        // Keep the warning output active for one second.
        delay_ms(1000);

        // Set GPIO P0.2 LOW to deactivate the warning output.
        IOCLR0=1<<2;

        //delay_ms(500);
        //delay_s(2);

        // Clear the LCD after displaying the insufficient balance warning.
        CmdLCD(0x01);
    }
}


// Deposit money into the account and record the transaction.
void Deposit(u32 acc_no)
{
    // Clear the LCD before starting the deposit operation.
    CmdLCD(0x01);

    // Display the current RTC date and time on the LCD.
    Display_RTC();

    // Wait for one second so the user can view the date and time.
    delay_ms(1000);

    // Clear the LCD before displaying the currency denominations.
    CmdLCD(0x01);

    // Display the available currency denominations for deposit.
    StrLCD("Avbl 100 200 500 Rs");

    // Wait for one second before requesting the deposit amount.
    delay_s(1);

    // Clear the LCD before accepting the deposit amount.
    CmdLCD(0x01);

    // Move the LCD cursor to the beginning of the first line.
    CmdLCD(GOTO_LINE1_POS0);

    // Prompt the user to enter the deposit amount.
    StrLCD("Enter Amnt");

    // Read and validate the deposit amount entered through the keypad.
    amnt=transaction_amnt();

    // Wait until the pressed keypad key is released.
    while(ColScan()==0);

    // Add the deposited amount to the available account balance.
    Bal+=amnt;

    // Clear the LCD before displaying the deposit status.
    CmdLCD(0x01);

    // Move the LCD cursor to the beginning of the first line.
    CmdLCD(GOTO_LINE1_POS0);

    // Display a message confirming successful deposit.
    StrLCD("Deposit success");

    // Wait for two seconds so the user can view the success message.
    delay_s(2);

    // Store the deposit details in the transaction history.
    Add_History(acc_no,"DEPOSIT",amnt);

    // Clear the LCD after completing the deposit.
    CmdLCD(0x01);

    // Read the current date and time from the RTC registers.
    RTC_Read(&sec,&min,&hour,&day,&month,&year);

    // Print a separator line before the deposit receipt.
    U0_TxStr("\r\n=======================================================================\r\n");

    // Format the account number into the UART message buffer.
    sprintf(log,"Account Number:%u\r\n",acc_no);

    // Print the account number on the UART terminal.
    U0_TxStr(log);

    // Format the transaction date in DD-MM-YYYY format.
    sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);

    // Print the transaction date on the UART terminal.
    U0_TxStr(log);

    // Format the transaction time in HH:MM:SS format.
    sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);

    // Print the transaction time on the UART terminal.
    U0_TxStr(log);

    // Print the transaction type as Cash Deposit.
    U0_TxStr("Transaction      :Cash Deposit\r\n");

    // Format the successfully deposited amount.
    sprintf(log,"Deposit Amount:%u\r\n",amnt);

    // Print the deposit amount on the UART terminal.
    U0_TxStr(log);

    // Format the updated account balance after deposit.
    sprintf(log,"Total Balance :%u\r\n",Bal);

    // Print the updated balance on the UART terminal.
    U0_TxStr(log);

    // Print a separator line after the deposit receipt.
    U0_TxStr("\r\n=======================================================================\r\n");
}
