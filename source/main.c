// main.c

// Include LCD function declarations for initialization and display operations.
#include "lcd.h"

// Include keypad function declarations for initialization and key scanning.
#include "kpm.h"

// Include UART function declarations for serial communication.
#include "uart.h"

// Include RTC function declarations for date and time operations.
#include "rtc.h"

// Include ATM Simulator function declarations for login and transactions.
#include "atm_run.h"

// Include delay function declarations for generating software delays.
#include "delay.h"

// Include external interrupt function declarations for EINT1 configuration.
#include "interrupt.h"


// Main function that initializes peripherals and starts the ATM Simulator.
int main()
{
    // Initialize the 4x4 matrix keypad GPIO pins for user input.
    InitKPM();

    // Initialize the LCD for displaying ATM messages and transaction details.
    InitLCD();

    // Initialize the Real-Time Clock for date and time operations.
    InitRTC();

    // Configure External Interrupt 1 for date and time setting operations.
    Init_EINT1();

    // Initialize UART0 for serial communication with the terminal.
    UART0_Init();

    // Display the ATM Simulator title on the UART serial terminal.
    U0_TxStr("=============================ATM SIMULATOR==================================\r\n\r\n");

    // Display the ATM initialization status message on the serial terminal.
    U0_TxStr("ATM Initialising!....................\r\n");

    // Generate an approximate one-second delay during initialization.
    delay_s(1);

    // Display the initialization completion message on the serial terminal.
    U0_TxStr("Initialising Completed!....\r\n\r\n");

    // Print a separator line on the serial terminal.
    U0_TxStr("\r\n=======================================================================\r\n");

    // Clear the LCD display before starting the ATM application.
    CmdLCD(0x01);

    // Start the ATM Simulator to handle login, menu selection, and transactions.
    atm_run();
}
