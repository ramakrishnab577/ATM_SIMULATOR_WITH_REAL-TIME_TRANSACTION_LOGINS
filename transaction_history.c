#include<lpc21xx.h>
#include<stdio.h>
#include<string.h>
#include "transaction_history.h"
#include "lcd.h"
#include "rtc.h"
#include "types.h"
#include "uart.h"

#define MAX_HISTORY 10
typedef struct
{
	u32	acc_no;
	char type[20];
	u32 amnt;
	u32 day;
	u32 month;
	u32 year;
	u32 hour;
	u32 min;
	u32 sec;
}History;
History h[MAX_HISTORY];
u32 h_cnt=0;
void Add_History(u32 acc_no,char *type,u32 amnt)
{
	u32 i;
	if(h_cnt==MAX_HISTORY)
	{
	 	for(i=0;i<MAX_HISTORY-1;i++)
		{
			h[i]=h[i+1];
		}
		h_cnt=MAX_HISTORY-1;
	}
	i=h_cnt;
	h[i].acc_no=acc_no;
	strncpy(h[i].type,type,sizeof(h[i].type)-1);
	h[i].type[sizeof(h[i].type)-1]='\0';
	h[i].amnt=amnt;
	h[i].day=DOM;
	h[i].month=MONTH;
	h[i].year=YEAR;
	h[i].hour=HOUR;
	h[i].min=MIN;
	h[i].sec=SEC;
	h_cnt++;
}
void Display_History(void)
{
	u32 i;
	char buffer[150];
	U0_TxStr("\r\n=======================================================================\r\n");
	U0_TxStr("Transaction History\r\n");
	if(h_cnt==0)
	{
		sprintf(buffer,"NO TRANSACTION AVAILABLE\r\n");
		U0_TxStr(buffer);
		return;
	}
	for(i=0;i<h_cnt;i++)
	{
			sprintf(buffer,"[%02u-%02u-%04u/%02u:%02u:%02u] ACC:%u  Transaction:%s  Amount:Rs.%u\r\n",
			h[i].day,h[i].month,h[i].year,h[i].hour,h[i].min,h[i].sec,h[i].acc_no,h[i].type,h[i].amnt);
			U0_TxStr(buffer);
	}
	U0_TxStr("\r\n=======================================================================\r\n");
}
