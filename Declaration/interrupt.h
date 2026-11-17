//interrupt.h
void eint1_isr(void)__irq;
void  Init_EINT1(void);
#define eint1_pin_fun 0x000000c0
#define eint1_vic_chno 15
extern volatile int flag;
