#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "types.h"
#include "transaction.h"
#include "transaction_history.h"
#include "delay.h"
#include "rtc.h"
#include "uart.h"
#include<lpc21xx.h>
#include<stdio.h>

u32 Bal,amnt;;
s32 sec,min,hour;
s32 day,month,year;
char log[200];
void Balance(u32 acc_no)
{
	CmdLCD(0x01);
	Display_RTC();
	delay_ms(1000);
	CmdLCD(0x01);
	CmdLCD(GOTO_LINE1_POS0);
    StrLCD("Available Bal..");
	CmdLCD(GOTO_LINE2_POS0);
    U32LCD(Bal);
	delay_s(2);
	CmdLCD(0x01);
	RTC_Read(&sec,&min,&hour,&day,&month,&year);
	U0_TxStr("\r\n=======================================================================\r\n");
	sprintf(log,"Account Number:%u\r\n",acc_no);
	U0_TxStr(log); 
	sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);
	U0_TxStr(log);
	sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);
	U0_TxStr(log);
	U0_TxStr("Transaction      :Balance Enquiry\r\n");
	sprintf(log,"Balance       :%u",Bal);
	U0_TxStr(log);
	U0_TxStr("\r\n=======================================================================\r\n");
	//sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :BALANCE Rs.%u/-\r\n",day,month,year,hour,min,sec,acc_no,Bal);
	//U0_TxStr(log);
}
void Withdraw(u32 acc_no)
{
	CmdLCD(0x01);
	Display_RTC();
	delay_ms(1000);	
	CmdLCD(0x01);
	StrLCD("Avbl 100 200 500 Rs");
	delay_s(1);
	CmdLCD(0x01);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Amnt");
	amnt=transaction_amnt();
	while(ColScan()==0);
	if(amnt<=Bal)
	{
	    //u8 log[200];
		Bal-=amnt;
		CmdLCD(0x01);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Withdraw success");
		delay_s(2);
		Add_History(acc_no,"WITHDRAW",amnt);
	    CmdLCD(0x01);
		RTC_Read(&sec,&month,&year,&day,&hour,&min);
		U0_TxStr("\r\n=======================================================================\r\n");
		sprintf(log,"Account Number:%u\r\n",acc_no);
		U0_TxStr(log);
		sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);
		U0_TxStr(log);
		sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);
		U0_TxStr(log);
		U0_TxStr("Transaction      :Cash Withdrawal\r\n");
		sprintf(log,"Withdraw Amount:%u\r\n",amnt);
		U0_TxStr(log);
		sprintf(log,"Total Balance  :%u",Bal);
		U0_TxStr(log);
		U0_TxStr("\r\n=======================================================================\r\n");
		//sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] &min,&hour,&day,ACC:%u :WITHDRAW: Rs.%u BALANCE: Rs.%u\r\n",day,month,year,hour,min,sec,acc_no,amnt,Bal);
		//U0_TxStr(log);

	}
	else
	{
		CmdLCD(0x01);
	    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Insufficient Bal..");
		IOSET0=1<<2;
		delay_ms(1000);
		IOCLR0=1<<2;
		//delay_ms(500);
		//delay_s(2);
		CmdLCD(0x01);

		
	}
}


void Deposit(u32 acc_no)
{
	CmdLCD(0x01);
	Display_RTC();
	delay_ms(1000);
	CmdLCD(0x01);
	StrLCD("Avbl 100 200 500 Rs");
	delay_s(1);
	CmdLCD(0x01);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Enter Amnt");
	amnt=transaction_amnt();
	while(ColScan()==0);
	Bal+=amnt;
	CmdLCD(0x01);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("Deposit success");
	delay_s(2);
	Add_History(acc_no,"DEPOSIT",amnt);
	CmdLCD(0x01);
    RTC_Read(&sec,&min,&hour,&day,&month,&year);
	U0_TxStr("\r\n=======================================================================\r\n");
	sprintf(log,"Account Number:%u\r\n",acc_no);
	U0_TxStr(log);
	sprintf(log,"Date          :%02u-%02u-%04u\r\n",day,month,year);
	U0_TxStr(log);
	sprintf(log,"Time          :%02u:%02u:%02u\r\n",hour,min,sec);
	U0_TxStr(log);
	U0_TxStr("Transaction      :Cash Deposit\r\n");
	sprintf(log,"Deposit Amount:%u\r\n",amnt);
	U0_TxStr(log);
	sprintf(log,"Total Balance :%u\r\n",Bal);
	U0_TxStr(log);
	U0_TxStr("\r\n=======================================================================\r\n");

	//sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u DEPOSIT: Rs.%u BALANCE: Rs.%u\r\n",day,month,year,hour,min,sec,acc_no,amnt,Bal);
	//U0_TxStr(log);
}
