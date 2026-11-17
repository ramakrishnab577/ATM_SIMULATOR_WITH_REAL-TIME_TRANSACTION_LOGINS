//kpm.c
#include <LPC21xx.h>
#include "defines.h"
#include "types.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#define MAX 100000
extern u32 kpmLUT[][4];
u32 row,col,keyV;
u32 ColScan(void)
{
	u32 status;
	status=READNIBBLE(IOPIN1,COL0);
	return ((status<15) ? 0 : 1);
}
u32 RowCheck(void)
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
		if(ColScan()==0)
		{
			break;		  
		}
	}														
	WRITENIBBLE(IOPIN1,ROW0,0);
	return r;
}
u32 ColCheck(void)
{
	u32 c;
	for(c=0;c<=3;c++)
	{
		if(READBIT(IOPIN1,COL0+c)==0)
			break;
	}
	return c;
}
u32 KeyScan(void)

{
	 while(ColScan());
   row=RowCheck();
   col=ColCheck();
   //delay_ms(200);
   keyV=kpmLUT[row][col];
   // while(ColScan());
   return keyV; 	
}
void InitKPM(void)
{
	//all rows grounded(output)
	IODIR1|=15<<ROW0;
	//all cols high (input)
	//IODIR1 &=~(15<<COL0); //default
}
u32 kpmLUT[4][4]= 
{
	{1,2,3,'A'},
	{4,5,6,'B'},
	{7,8,9,'C'},
	{'*',0,'#','D'}
}; 
u32 Read_Password()
{
	u32 num=0,val,digit=0,i=0;
	while(1)
	{
	    val=KeyScan();
		while(ColScan()==0);
		if(val>=0 && val<=9)
		{
			CmdLCD(GOTO_LINE2_POS0+(i++));
			CharLCD('*');
			if(digit<MAX)
			{
			  num=num*10+val;
			  digit++;
			}
		}
		else if(val==35)
		{
		  if(digit>0)
		   return num;
		   //CmdLCD(0x01);
		}
		else if(val==42)
		{
			if(digit>0)
			{
			    digit--;
				i--;
		    	num=num/10;
			    CmdLCD(GOTO_LINE2_POS0+i);
			    StrLCD(" ");
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		}
	}
}
/*u32 get_number()
{
		u32 num=0,i=0,val,digit=0;
		for(i=0;i<4;i++)
		{	
		   val=KeyScan();
		   if(val>=0 && val<=9)
		   {
		      CmdLCD(GOTO_LINE2_POS0+i);
		       U32LCD(val);
		       num=num*10+val;
			   digit++;
		   }
		   else if(val==35)
		   {
		     return num;
		   }
		   else if(val==42)
		   {
		    if(digit>0)
			{
			    digit--;
				i--;
		    	num=num/10;
			    CmdLCD(GOTO_LINE2_POS0+i);
			    StrLCD(" ");
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		   }
		}
}*/
u32 transaction_amnt()
{
	u32 num=0,val,digit=0,i=0;
	while(1)
	{
	  	val=KeyScan();
		while(ColScan()==0);
		if(val>=0 && val<=9)
		{
			CmdLCD(GOTO_LINE2_POS0+(i++));
			U32LCD(val);
			if(digit<MAX)
			{
			  num=num*10+val;
			  digit++;
			}
		}
		else if(val==35)
		{
		  if(digit>0)
		   {
		      if(num==0)
			  {
                CmdLCD(GOTO_LINE2_POS0);
				StrLCD("                 ");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Invalid!......");
				delay_s(1);
			      goto e;
			  }
			  if(num%100!=0)
			  {
			    CmdLCD(GOTO_LINE2_POS0);
				StrLCD("                 ");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Invalid!......");
				delay_s(1);   
				   goto e;
			  }
		      return num;
		   }
		}
		else if(val==42)
		{
		  	if(digit>0)
			{
			    digit--;
				i--;
		    	num=num/10;
			    CmdLCD(GOTO_LINE2_POS0+i);
			    StrLCD(" ");
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		}
		else
		{
		   e:num=0;
		     digit=0;
			 CmdLCD(GOTO_LINE2_POS0);
			 StrLCD("                  ");
		}
	}
}
u32 set_number()
{
	u32 num=0,val,digit=0,i=0;
	while(1)
	{
	    val=KeyScan();
		while(ColScan()==0);
		if(val>=0 && val<=9)
		{
			CmdLCD(GOTO_LINE2_POS0+(i++));
			U32LCD(val);
			if(digit<MAX)
			{
			  num=num*10+val;
			  digit++;
			}
		}
		else if(val==35)
		{
		  if(digit>0)
		   return num;
		   //CmdLCD(0x01);
		}
		else if(val==42)
		{
			if(digit>0)
			{
			    digit--;
				i--;
		    	num=num/10;
			    CmdLCD(GOTO_LINE2_POS0+i);
			    StrLCD(" ");
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		}
	}
}
