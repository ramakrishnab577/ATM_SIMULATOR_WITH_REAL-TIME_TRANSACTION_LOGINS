//RTC.c
#include<lpc21xx.h>
#include<stdio.h>
#include "types.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "rtc.h"
#include "kpm.h"
#include "atm_run.h"
#include<stdlib.h>
#include "delay.h"
//void atm_login(void);
void InitRTC(void)
{		 
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
	CCR=0x11;//Start RTC
}
void set_Hour()
{
	u32 hour;
	CmdLCD(0x01);
chg:StrLCD("set Hour");
    hour=set_number();
	if(hour>0 && hour<24)
	{
	   HOUR=hour;
	   CmdLCD(GOTO_LINE2_POS0);
	   StrLCD("Updated");
	   delay_s(1);
	   CmdLCD(0x01);
	}
	else
	{ 
	   CmdLCD(0x01);
	   StrLCD("Invalid Hour");
	   delay_ms(500);
	   CmdLCD(0x01);
	   goto chg;
	}
}
void set_Min()
{
	u32 min;
	CmdLCD(0x01);
chg:StrLCD("set Min");
    min=set_number();
	if(min>0 && min<60)
	{
	   MIN=min;
	   CmdLCD(GOTO_LINE2_POS0);
	   StrLCD("Updated");
	   delay_s(1);
	   CmdLCD(0x01);
	}
	else
	{ 
	   CmdLCD(0x01);
	   StrLCD("Invalid Min");
	   delay_ms(500);
	   CmdLCD(0x01);
	   goto chg;
	}
}
void set_Sec()
{
	u32 sec;
	CmdLCD(0x01);
chg:StrLCD("set sec");
    sec=set_number();
	if(sec>0 && sec<60)
	{
	   SEC=sec;
	   CmdLCD(GOTO_LINE2_POS0);
	   StrLCD("Updated");
	   delay_s(1);
	   CmdLCD(0x01);
	}
	else
	{ 
	   CmdLCD(0x01);
	   StrLCD("Invalid Sec");
	   delay_ms(500);
	   CmdLCD(0x01);
	   goto chg;
	}
}
void set_Day()
{
    u32 date;
	CmdLCD(0x01);
chg:StrLCD("Set Date");
	date=set_number();
	if(date>0&&date<=31)
	{
	     DOM=date;
		 CmdLCD(GOTO_LINE2_POS0);
		 StrLCD("Updated");
		 delay_s(1);
		 CmdLCD(0x01);
    }
	else
	{ 
	   CmdLCD(0x01);
	   StrLCD("Invalid Date");
	   delay_ms(500);
	   CmdLCD(0x01);
	   goto chg;
	}
}
void set_Month()
{
   u32 month;
	CmdLCD(0x01);
chg:StrLCD("Set month");
	month=set_number();
	if(month>0&&month<13)
	{
	     MONTH=month;
		 CmdLCD(GOTO_LINE2_POS0);
		 StrLCD("Updated");
		 delay_s(1);
		 CmdLCD(0x01);
    }
	else
	{ 
	   CmdLCD(0x01);
	   StrLCD("Invalid month");
	   delay_ms(500);
	   CmdLCD(0x01);
	   goto chg;
	}
}			 
void set_Year()
{
   u32 year;
	CmdLCD(0x01);
chg:StrLCD("Set year");
	year=set_number();
	if(year>2025 && year<3000)
	{
	     YEAR=year;
		 CmdLCD(GOTO_LINE2_POS0);
		 StrLCD("Updated");
		 delay_s(1);
		 CmdLCD(0x01);
    }
	else
	{ 
	   CmdLCD(0x01);
	   StrLCD("Invalid Year");
	   delay_ms(500);
	   CmdLCD(0x01);
	   goto chg;
	}
}
void set_Date()
{
     u32 n;
     CmdLCD(0x01);
	 while(1)
	 {
	  		StrLCD("1:DATE 2:MONTH");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("3:YEAR 4:Exit");
			n=KeyScan();
			delay_ms(500);
			switch(n)
			{
			    case 1:set_Day();
					   break;
				case 2:set_Month();
						break;
				case 3:set_Year();
						break;
				case 4:CmdLCD(0x01);
				       return;
			}
	 }
}
void set_Time()
{
     u32 n;
     CmdLCD(0x01);
	 while(1)
	 {
	  		StrLCD("1:HOUR 2:MIN");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("3:SEC 4:Exit");
			n=KeyScan();
			delay_ms(500);
			switch(n)
			{
			    case 1:set_Hour();
					   break;
				case 2:set_Min();
						break;
				case 3:set_Sec();
						break;
				case 4:CmdLCD(0x01);	
				       return;
			}
	 }
}
void RTC_Read(s32 *s,s32 *m,s32 *h,s32 *d,s32 *M,s32 *y)
{
	*s=SEC;
	*m=MIN;
	*h=HOUR;
	*d=DOM;
	*M=MONTH;
	*y=YEAR;
}
void Display_RTC(void)
{
	s32 sec,min,hour;
	s32 day,month,year;
    char line[17];
	CmdLCD(0x01);
	RTC_Read(&sec,&min,&hour,&day,&month,&year);
	CmdLCD(GOTO_LINE1_POS0);
	sprintf(line,"DATE:%02u/%02u/%04u",day,month,year);
	StrLCD(line);
	CmdLCD(GOTO_LINE2_POS0);
	sprintf(line,"TIME:%02u:%02u:%02u",hour,min,sec);
	StrLCD(line);
}
void Set_date_time(void)
{
	u32 val;
   CmdLCD(0x01);
   while(1)
   {
        CmdLCD(GOTO_LINE1_POS0);
   		StrLCD("1:Date 2:Time 3:EXIT");
		val=KeyScan();
		delay_ms(500);
		switch(val)
		{
		   case 1:set_Date();
		   		 break;
		   case 2:set_Time();
		   		break;
		   case 3:CmdLCD(0x01);
		          return;
		}
   }
}
