//main.c
#include "lcd.h"
#include "kpm.h"
#include "uart.h"
#include "rtc.h"
#include "atm_run.h"
#include "delay.h"
#include "interrupt.h"
int main()
{
	InitKPM();
	InitLCD();
	InitRTC();
	Init_EINT1();
	UART0_Init();
	U0_TxStr("=============================ATM SIMULATOR==================================\r\n\r\n");
	U0_TxStr("ATM Initialising!....................\r\n");
	delay_s(1);
	U0_TxStr("Initialising Completed!....\r\n\r\n");
	U0_TxStr("\r\n=======================================================================\r\n");
	CmdLCD(0x01);
	atm_run();
}
