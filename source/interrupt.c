//interrupt.c
// Include the header needed for this module.
#include "types.h"
// Include the header needed for this module.
#include "interrupt.h"
// Include the header needed for this module.
#include<lpc21xx.h>
// Declare shared data used by more than one function.
volatile int flag=0;
void eint1_isr(void)__irq
{
    // Update this value as part of the current operation.
    flag=1;
	//Set_date_time();
	// Configure or acknowledge the external interrupt.
	EXTINT=0x02;
	// Configure or acknowledge the external interrupt.
	VICVectAddr=0x00;
}
// Define the function that performs this operation.
void  Init_EINT1(void)
{
	// Select the hardware function assigned to the microcontroller pins.
	PINSEL0&=((u32)~3<<6);
	// Select the hardware function assigned to the microcontroller pins.
	PINSEL0|=eint1_pin_fun;
		//VICIntSelect &=~(1<<eint0_vic_chno);
	// Configure or acknowledge the external interrupt.
	VICIntEnable=1<<eint1_vic_chno;
	// Configure or acknowledge the external interrupt.
	VICVectCntl0=(1<<5)|eint1_vic_chno;
	// Configure or acknowledge the external interrupt.
	VICVectAddr0=(u32)eint1_isr;
	// Configure or acknowledge the external interrupt.
	EXTMODE =0x02;	 //Edge-triggering
	//EXTPOLAR |=0x00; //Rising edge
	// Configure or acknowledge the external interrupt.
	EXTINT=0x02;//clear pending interrupt
}
