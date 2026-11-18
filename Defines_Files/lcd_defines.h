//lcd_defines.h
//HD44780 Commands 
// Clear the entire LCD display and move the cursor to the first position.
#define CLEAR_LCD            0x01

// Return the cursor to the first position without clearing the display.
#define RET_CUR_HOME         0x02

// Move the cursor one position to the right after writing a character.
#define SHIFT_CUR_RIGHT      0x06

// Move the cursor one position to the right and shift the display left after writing.
#define SHIFT_CUR_LEFT       0x07

// Turn OFF the LCD display and cursor without deleting stored characters.
#define DSP_OFF              0x08

// Turn ON the LCD display and turn OFF the cursor.
#define DSP_ON_CUR_OFF       0x0C

// Turn ON the LCD display and show the cursor without blinking.
#define DSP_ON_CUR_ON        0x0E

// Turn ON the LCD display and enable the blinking cursor.
#define DSP_ON_CUR_BLINK     0x0F

// Move the cursor one position to the left without changing display data.
#define SHIFT_DISP_LEFT      0x10

// Move the cursor one position to the right without changing display data.
#define SHIFT_DISP_RIGHT     0x14

// Configure the LCD for 8-bit data communication and single-line display.
#define MODE_8BIT_1LINE      0x30

// Configure the LCD for 4-bit data communication and single-line display.
#define MODE_4BIT_1LINE      0x20

// Configure the LCD for 8-bit data communication and two-line display.
#define MODE_8BIT_2LINE      0x38

// Configure the LCD for 4-bit data communication and two-line display.
#define MODE_4BIT_2LINE      0x28

// Move the cursor to the first position of LCD line 1.
#define GOTO_LINE1_POS0      0x80

// Move the cursor to the first position of LCD line 2.
#define GOTO_LINE2_POS0      0xC0

// Move the cursor to the second position of LCD line 2.
#define GOTO_LINE2_POS1      0xC1

// Move the cursor to the first position of LCD line 3 (16x4 LCD).
#define GOTO_LINE3_POS0      0x94

// Move the cursor to the first position of LCD line 4 (16x4 LCD).
#define GOTO_LINE4_POS0      0xD4

// Set the CGRAM address to 0 for creating custom LCD characters.
#define GOTO_CGRAM_START     0x40


// LCD CONNECTION PINS

// Define P0.8 as the starting data pin for LCD D0-D7 (P0.8 to P0.15).
#define LCD_DATA 8 //@p0.8 to p0.15

// Define P0.16 as the LCD Register Select (RS) pin.
#define LCD_RS   16 //@p0.16

// Define P0.18 as the LCD Read/Write (RW) pin.
#define LCD_RW   18 //@p0.18

// Define P0.17 as the LCD Enable (EN) pin.
#define LCD_EN   17 //@p0.17
