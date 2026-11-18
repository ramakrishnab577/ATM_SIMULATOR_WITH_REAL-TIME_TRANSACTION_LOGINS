// kpm.h

// Include user-defined data types such as u32 (unsigned 32-bit integer).
#include "types.h"

// Declare a function to scan the keypad columns and detect a key press.
u32 ColScan(void);

// Declare a function to identify which keypad row contains the pressed key.
u32 RowCheck(void);

// Declare a function to identify which keypad column contains the pressed key.
u32 ColCheck(void);

// Declare a function to scan the keypad and return the value of the pressed key.
u32 KeyScan(void);

// Declare a function to initialize the GPIO pins connected to the 4x4 keypad.
void InitKPM(void);

// Declare a function to read the ATM PIN while displaying '*' instead of digits.
u32 Read_Password(void);

// Declare a function to read and validate the withdrawal or deposit amount.
u32 transaction_amnt(void);

// Declare a function to read a numeric value for configuring RTC date and time.
u32 set_number(void);
