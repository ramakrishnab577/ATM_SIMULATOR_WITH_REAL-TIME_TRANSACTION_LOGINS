#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
#include "transaction.h"
#include "transaction_history.h"
#include "uart.h"
#include "interrupt.h"
#include "rtc.h"
#include "atm_run.h"
#include "types.h"

#define ACC_NO 1111
#define MAX 3
#include<stdio.h>
#include<lpc21xx.h>
//extern volatile int flag;

extern s32 sec,min,hour;
extern s32 day,month,year;
extern char log[200];
//volatile unsigned char flag=0;

u32 PIN=3333;
u32 acc_num,pin,cnt=0,val;

int atm_login()
{
	IODIR0|=1<<2;
	IOCLR0=1<<2;
	while(1)
	{
	   StrLCD("Welcome!....");
	   CmdLCD(GOTO_LINE2_POS0);
	   StrLCD("ATM SIMULATOR!...");
	   delay_s(1);
		while(1)
		{
		    Display_RTC();
			if(flag==1)
	   		{
	       		Set_date_time();
		   		flag=0;
	   		}
			delay_s(2);
			break;
		}
	    CmdLCD(0x01);
acc:   CmdLCD(GOTO_LINE1_POS0);
	    StrLCD("Enter Account No");
		acc_num=set_number();
		CmdLCD(0x01);
		if(ACC_NO!=acc_num)
		{	CmdLCD(GOTO_LINE1_POS0);
			StrLCD("INVALID ACC NO");
			delay_s(3);
			CmdLCD(0x01);
			goto acc;
		}
		else 
		{
		    CmdLCD(0x01);
pwd:	    CmdLCD(GOTO_LINE1_POS0);
	    	StrLCD("Enter Pin");
		    pin=Read_Password();
			CmdLCD(0x01);
			if(pin==PIN)
			{
			  CmdLCD(GOTO_LINE1_POS0);
			  StrLCD("LOGIN SUCCESS");
			  RTC_Read(&sec,&min,&hour,&day,&month,&year);
			  U0_TxStr("\r\n=======================================================================\r\n");
			  sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :LOGIN SUCCESS\r\n",day,month,year,hour,min,sec,acc_num);
		   	  U0_TxStr(log);
			  U0_TxStr("\r\n=======================================================================\r\n");
			  delay_s(2);
			  CmdLCD(0x01);
			   return 1;
			}
			else
			{
			   CmdLCD(GOTO_LINE1_POS0);
			   StrLCD("INVALID PASSWORD");
			   delay_s(2);
			   CmdLCD(0x01);
			   cnt++;
			   if(cnt==MAX)
			   {
			     CmdLCD(GOTO_LINE1_POS0);
			     StrLCD("TRY AFTER 24Hrs!..");
				 IOSET0=1<<2;
				 delay_ms(500);
				 IOCLR0=1<<2;
				 //delay_ms(500);
				 CmdLCD(0x01);	
			   }
			   else
			   {
			   		goto pwd;
			   }	
			}		 
		}
	}		
}
void change_pin()
{
    u32 old_pin,new_pin;
	CmdLCD(0x01);
old:StrLCD("Enter old pin");
    old_pin=Read_Password();
    if(old_pin==PIN)
    {
	   CmdLCD(0x01);
       StrLCD("Enter new pin");
       new_pin=Read_Password();
       PIN=new_pin;
       CmdLCD(0x01);
	   RTC_Read(&sec,&min,&hour,&day,&month,&year);
	   U0_TxStr("\r\n=======================================================================\r\n");
	   sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :PIN CHANGED SUCCESSFULLY\r\n",day,month,year,hour,min,sec,ACC_NO);
	   U0_TxStr(log);
	   U0_TxStr("\r\n=======================================================================\r\n");
       StrLCD("chg successful");
    
    }
    else
    {
       CmdLCD(0x01);
       StrLCD("Invalid Pin");
	   CmdLCD(0x01);
       goto old;
    }

}
void atm_menu()
{
			  while(1)
			  {
			  		if(flag==1)
	 				{
	    				Set_date_time();
						flag=0;
	 				}
			         CmdLCD(GOTO_LINE1_POS0);
					 StrLCD("1.BAL 2.WDL 3.DEP");
					 CmdLCD(GOTO_LINE2_POS0);
					 StrLCD("4.PIN CHG 5.TRF 6.EX");
					 delay_s(1);
			  		 val=KeyScan();
					 CmdLCD(0x01);
					 while(ColScan()==0);
					 switch(val)
					 {
					 	case 1:Balance(ACC_NO);
						       break;
						case 2:Withdraw(ACC_NO);
							   break;
						case 3:Deposit(ACC_NO);
							   break;
						case 4:change_pin();
							   break;
						case 5:Display_History();
							   break;
						case 6:break;	
					 }
					 if(val==6)
					 {
					   	RTC_Read(&sec,&min,&hour,&day,&month,&year);
						U0_TxStr("\r\n=======================================================================\r\n");
			  			sprintf(log,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u :LOGOUT\r\n",day,month,year,hour,min,sec,ACC_NO);
		   	  			U0_TxStr(log);
						CmdLCD(0x01);
						U0_TxStr("\r\n=======================================================================\r\n");
						StrLCD("THANK YOU!.....");
						U0_TxStr("THANK YOU!...........\r\n\r\n");
						delay_s(1);
						CmdLCD(0x01);
					 	break;
					 }
					if(flag==1)
	   				{
	       				Set_date_time();
		   				flag=0;
	   				}
			  }
}
void atm_run()
{
  while(1)
  {
     if(flag==1)
	 {
	    Set_date_time();
		flag=0;
	 }
	if(atm_login())
	{
		atm_menu();
    }
  }
}
