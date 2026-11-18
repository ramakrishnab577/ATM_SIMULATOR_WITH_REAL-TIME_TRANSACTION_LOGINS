// lcd.h

// Include user-defined data types such as u16, u32, s32, and f32.
#include "types.h"

// Declare a function to write 8-bit data or commands to the LCD interface.
void WriteLCD(u16 byte);

// Declare a function to send commands such as clear display or cursor positioning to the LCD.
void CmdLCD(u16 cmd);

// Declare a function to initialize the LCD GPIO pins and configure the LCD display.
void InitLCD(void);

// Declare a function to display a single ASCII character on the LCD.
void CharLCD(u16 asciiVal);

// Declare a function to display a null-terminated string on the LCD.
void StrLCD(char *);

// Declare a function to display an unsigned 32-bit integer on the LCD.
void U32LCD(u32);

// Declare a function to display a signed 32-bit integer on the LCD.
void S32LCD(s32);

// Declare a function to display a floating-point number with the specified decimal places.
void F32LCD(f32,u16 nDP);
