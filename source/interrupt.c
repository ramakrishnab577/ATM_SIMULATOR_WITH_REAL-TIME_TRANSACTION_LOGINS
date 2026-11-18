// interrupt.c

// Include user-defined data types such as u32.
#include "types.h"

// Include external interrupt definitions and function declarations.
#include "interrupt.h"

// Include LPC21xx microcontroller register definitions.
#include <lpc21xx.h>

// Declare a volatile flag to indicate when External Interrupt 1 occurs.
volatile int flag = 0;


// Define the External Interrupt 1 Interrupt Service Routine (ISR).
void eint1_isr(void) __irq
{
    // Set the flag to 1 to notify the main program that an interrupt occurred.
    flag = 1;

    //Set_date_time();

    // Clear the pending EINT1 interrupt flag by writing 1 to bit 1 of EXTINT.
    EXTINT = 0x02;

    // Acknowledge the interrupt to the VIC and signal the end of ISR execution.
    VICVectAddr = 0x00;
}


// Initialize and configure External Interrupt 1 (EINT1).
void Init_EINT1(void)
{
    // Clear the function selection bits for P0.3 in the PINSEL0 register.
    PINSEL0 &= ((u32)~3 << 6);

    // Select the EINT1 alternate pin function using the defined macro.
    PINSEL0 |= eint1_pin_fun;

    //VICIntSelect &= ~(1 << eint0_vic_chno);

    // Enable the EINT1 interrupt channel in the Vectored Interrupt Controller.
    VICIntEnable = 1 << eint1_vic_chno;

    // Enable VIC vector slot 0 and assign the EINT1 interrupt channel to it.
    VICVectCntl0 = (1 << 5) | eint1_vic_chno;

    // Assign the EINT1 interrupt service routine address to VIC vector slot 0.
    VICVectAddr0 = (u32)eint1_isr;

    // Configure EINT1 as an edge-triggered external interrupt.
    EXTMODE = 0x02;

    //EXTPOLAR |= 0x00; // Rising edge

    // Clear any pending EINT1 interrupt before normal operation.
    EXTINT = 0x02;
}
