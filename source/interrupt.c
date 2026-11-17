//interrupt.c
#include "types.h"
#include "interrupt.h"
#include "lcd.h"
#include<lpc21xx.h>
volatile int flag=0;
void eint1_isr(void)__irq
{
    flag=1;
	//Set_date_time();
	EXTINT=0x02;
	VICVectAddr=0x00;
}
void  Init_EINT1(void)
{
	PINSEL0&=((u32)~3<<6);
	PINSEL0|=eint1_pin_fun;
		//VICIntSelect &=~(1<<eint0_vic_chno);
	VICIntEnable=1<<eint1_vic_chno;
	VICVectCntl0=(1<<5)|eint1_vic_chno;
	VICVectAddr0=(u32)eint1_isr;
	EXTMODE =0x02;	 //Edge-triggering
	//EXTPOLAR |=0x00; //Rising edge
	EXTINT=0x02;//clear pending interrupt
}
