// Include the header needed for this module.
#include<lpc21xx.h>
// Include the header needed for this module.
#include "types.h"
// Include the header needed for this module.
#include "uart.h"
// Include the header needed for this module.
#include "uart_defines.h"
// Define the function that performs this operation.
void UART0_Init(void)
{
	// Select the hardware function assigned to the microcontroller pins.
	PINSEL0 &=~((3<<2)|(3<<0));
//	PINSEL0 |=(1<<TXD0_PIN_FUNC|1<<RXD0_PIN_FUNC);
// Select the hardware function assigned to the microcontroller pins.
PINSEL0|=0x05;
	// Configure or write data to a UART0 hardware register.
	U0LCR=((1<<DLAB_BIT)|(_8BIT<<WORD_LEN_SEL_BITS));
	// Configure or write data to a UART0 hardware register.
	U0DLL=DIVISOR;
	// Configure or write data to a UART0 hardware register.
	U0DLM=DIVISOR>>8;
	// Configure or write data to a UART0 hardware register.
	U0LCR &=~(1<<DLAB_BIT);
}
// Define the function that performs this operation.
void UART0_Tx(u8 sDat)
{
	// Configure or write data to a UART0 hardware register.
	U0THR=sDat;
	// Repeat these steps while the condition is true.
	while(((U0LSR>>TEMT_BIT)&1)==0);
}
/*void UART0_Rx(void)
{
	while(((U0LSR>>DR_BIT)&1)==0);
	return U0RBR;
}*/
// Define the function that performs this operation.
void U0_TxStr(char *s)
{

	// Repeat these steps while the condition is true.
	while(*s)
	{
		// Send one character through UART0.
		UART0_Tx(*s++);
	}
}
// Define the function that performs this operation.
void U0_TxU32(u32 n)
{
	// Declare variables used to store data for this operation.
	s32 i=0;u8 a[10];
	// Check this condition before continuing.
	if(n==0)
	{
		// Send one character through UART0.
		UART0_Tx('0');
	}
	// Handle the case when the previous condition is false.
	else
	{
		// Repeat these steps while the condition is true.
		while(n>0)
		{
			// Update this value as part of the current operation.
			a[i++]=(n%10)+48;
			// Update this value as part of the current operation.
			n/=10;
		}
	}
	// Repeat these steps using the loop counter.
	for(--i;i>=0;i--)
	{
		// Send one character through UART0.
		UART0_Tx(a[i]);
	}
}
// Define the function that performs this operation.
void U0_Tx32(s32 n)
{
	// Check this condition before continuing.
	if(n<0)
	{
		// Send one character through UART0.
		UART0_Tx('-');
		// Update this value as part of the current operation.
		n=-n;
	}
	// Send one character through UART0.
	UART0_Tx(n);
}
// Define the function that performs this operation.
void U0_F32(f32 fn,u8 nDP)
{
	// Declare variables used to store data for this operation.
	u32 n,i;
	// Check this condition before continuing.
	if(fn<0.0)
	{
		// Send one character through UART0.
		UART0_Tx('-');
		// Update this value as part of the current operation.
		fn=-fn;
	}
	// Update this value as part of the current operation.
	n=fn;
	// Send one character through UART0.
	UART0_Tx(n);
	// Send one character through UART0.
	UART0_Tx('.');
	// Repeat these steps using the loop counter.
	for(i=0;i<nDP;i++)
	{
		// Update this value as part of the current operation.
		fn=(fn-n)*10;
		// Update this value as part of the current operation.
		n=fn;
		// Send one character through UART0.
		UART0_Tx(n+48);
	}
}
/*s8* U0_RxStr(void)
{
	static s8 rBuff[100];
	s8 t,i=0;
	while(1)
	{
		t=UART0_Rx();
		rBuff[i]=t;
		if((t=='\n')||(t=='\r'))
		{
			rBuff[i]='\0';
			break;
		}
		i++;
	}
	U0_TxStr("\n\r");
	return rBuff;
}*/
