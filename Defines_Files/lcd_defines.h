//lcd_defines.h
//HD44780 Commands 
// Give a readable name to a fixed value or setting.
#define CLEAR_LCD            0x01 
// Give a readable name to a fixed value or setting.
#define RET_CUR_HOME         0x02 
// Give a readable name to a fixed value or setting.
#define SHIFT_CUR_RIGHT      0x06 
// Give a readable name to a fixed value or setting.
#define SHIFT_CUR_LEFT       0x07 
// Give a readable name to a fixed value or setting.
#define DSP_OFF              0x08 
// Give a readable name to a fixed value or setting.
#define DSP_ON_CUR_OFF       0x0c 
// Give a readable name to a fixed value or setting.
#define DSP_ON_CUR_ON        0x0E 
// Give a readable name to a fixed value or setting.
#define DSP_ON_CUR_BLINK     0x0F 
// Give a readable name to a fixed value or setting.
#define SHIFT_DISP_LEFT      0x10 
// Give a readable name to a fixed value or setting.
#define SHIFT_DISP_RIGHT     0x14 
// Give a readable name to a fixed value or setting.
#define MODE_8BIT_1LINE      0x30 
// Give a readable name to a fixed value or setting.
#define MODE_4BIT_1LINE      0x20 
// Give a readable name to a fixed value or setting.
#define MODE_8BIT_2LINE      0x38 
// Give a readable name to a fixed value or setting.
#define MODE_4BIT_2LINE      0x28 
// Give a readable name to a fixed value or setting.
#define GOTO_LINE1_POS0      0x80 
// Give a readable name to a fixed value or setting.
#define GOTO_LINE2_POS0      0xC0
// Give a readable name to a fixed value or setting.
#define GOTO_LINE2_POS1      0xC1
// Give a readable name to a fixed value or setting.
#define GOTO_LINE3_POS0      0x94 
// Give a readable name to a fixed value or setting.
#define GOTO_LINE4_POS0      0xD4 
// Give a readable name to a fixed value or setting.
#define GOTO_CGRAM_START     0x40

//lcd connection pins
// Give a readable name to a fixed value or setting.
#define LCD_DATA 8//@p0.8 to p0.15
// Give a readable name to a fixed value or setting.
#define LCD_RS   16//@p0.16
// Give a readable name to a fixed value or setting.
#define LCD_RW   18//@p0.17
// Give a readable name to a fixed value or setting.
#define LCD_EN   17//@p0.18
