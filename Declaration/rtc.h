// RTC.h

// Declare the function to initialize and enable the LPC21xx Real-Time Clock.
void InitRTC(void);

// Declare the function to read the current seconds, minutes, hours, day, month, and year from RTC registers using pointers.
void RTC_Read(s32 *s,s32 *m,s32 *h,s32 *d,s32 *M,s32 *y);

// Declare the function to display the current RTC date and time on the LCD.
void Display_RTC(void);

// Declare the function to display the RTC settings menu for updating the date and time.
void Set_date_time(void);
