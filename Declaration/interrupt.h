// interrupt.h

// Declare the External Interrupt 1 service routine using the ARM IRQ interrupt attribute.
void eint1_isr(void)__irq;

// Declare the function to configure and enable External Interrupt 1 (EINT1).
void Init_EINT1(void);

// Define the PINSEL0 bit mask (bits 7:6) used to configure P0.3 for the EINT1 function.
#define eint1_pin_fun 0x000000c0

// Define VIC channel number 15, which is assigned to External Interrupt 1.
#define eint1_vic_chno 15

// Declare a shared flag that can be modified by the interrupt service routine.
// The volatile keyword ensures the compiler reads its value when accessed.
extern volatile int flag;
