//main.c
// Include the header needed for this module.
#include "lcd.h"
// Include the header needed for this module.
#include "kpm.h"
// Include the header needed for this module.
#include "uart.h"
// Include the header needed for this module.
#include "rtc.h"
// Include the header needed for this module.
#include "atm_run.h"
// Include the header needed for this module.
#include "delay.h"
// Include the header needed for this module.
#include "interrupt.h"
// Define the function that performs this operation.
int main()
{
	// Call this function to perform the requested operation.
	InitKPM();
	// Call this function to perform the requested operation.
	InitLCD();
	// Call this function to perform the requested operation.
	InitRTC();
	// Call this function to perform the requested operation.
	Init_EINT1();
	// Call this function to perform the requested operation.
	UART0_Init();
	// Send this text to the serial terminal through UART0.
	U0_TxStr("=============================ATM SIMULATOR==================================\r\n\r\n");
	// Send this text to the serial terminal through UART0.
	U0_TxStr("ATM Initialising!....................\r\n");
	// Wait for the requested number of seconds.
	delay_s(1);
	// Send this text to the serial terminal through UART0.
	U0_TxStr("Initialising Completed!....\r\n\r\n");
	// Send this text to the serial terminal through UART0.
	U0_TxStr("\r\n=======================================================================\r\n");
	// Clear the LCD before showing new information.
	CmdLCD(0x01);
	// Call this function to perform the requested operation.
	atm_run();
}
