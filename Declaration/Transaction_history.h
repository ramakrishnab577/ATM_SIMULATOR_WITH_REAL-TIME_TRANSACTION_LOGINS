// transaction_history.h

// Include user-defined data types such as u32 (unsigned 32-bit integer).
#include "types.h"

// Declare the function to store a transaction's account number, type, and amount in history.
void Add_History(u32 acc_no,char *type,u32 amnt);

// Declare the function to display stored transaction history on the UART serial terminal.
void Display_History(void);
