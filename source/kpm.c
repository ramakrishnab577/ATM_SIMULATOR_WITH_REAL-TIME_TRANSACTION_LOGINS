//kpm.c
// Include the header needed for this module.
#include <LPC21xx.h>
// Include the header needed for this module.
#include "defines.h"
// Include the header needed for this module.
#include "types.h"
// Include the header needed for this module.
#include "kpm_defines.h"
// Include the header needed for this module.
#include "lcd.h"
// Include the header needed for this module.
#include "lcd_defines.h"
// Include the header needed for this module.
#include "delay.h"
// Give a readable name to a fixed value or setting.
#define MAX 100000
// Declare shared data used by more than one function.
extern u32 kpmLUT[][4];
// Declare variables used to store data for this operation.
u32 row,col,keyV;
// Check the keypad columns for a key press or release.
u32 ColScan(void)
{
	// Declare variables used to store data for this operation.
	u32 status;
	// Update this value as part of the current operation.
	status=READNIBBLE(IOPIN1,COL0);
	// Finish this function and return to its caller.
	return ((status<15) ? 0 : 1);
}
// Define the function that performs this operation.
u32 RowCheck(void)
{
	// Declare variables used to store data for this operation.
	u32 r;
	// Repeat these steps using the loop counter.
	for(r=0;r<=3;r++)
	{
		// Call this function to perform the requested operation.
		WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
		// Check this condition before continuing.
		if(ColScan()==0)
		{
			// Exit the current loop or switch case.
			break;		  
		}
	}														
	// Call this function to perform the requested operation.
	WRITENIBBLE(IOPIN1,ROW0,0);
	// Finish this function and return to its caller.
	return r;
}
// Define the function that performs this operation.
u32 ColCheck(void)
{
	// Declare variables used to store data for this operation.
	u32 c;
	// Repeat these steps using the loop counter.
	for(c=0;c<=3;c++)
	{
		// Check this condition before continuing.
		if(READBIT(IOPIN1,COL0+c)==0)
			// Exit the current loop or switch case.
			break;
	}
	// Finish this function and return to its caller.
	return c;
}
// Read the key pressed on the keypad.
u32 KeyScan(void)

{
	 // Repeat these steps while the condition is true.
	 while(ColScan());
   // Update this value as part of the current operation.
   row=RowCheck();
   // Update this value as part of the current operation.
   col=ColCheck();
   //delay_ms(200);
   // Update this value as part of the current operation.
   keyV=kpmLUT[row][col];
   // while(ColScan());
   // Finish this function and return to its caller.
   return keyV; 	
}
// Define the function that performs this operation.
void InitKPM(void)
{
	//all rows grounded(output)
	// Configure the selected GPIO pins as inputs or outputs.
	IODIR1|=15<<ROW0;
	//all cols high (input)
	//IODIR1 &=~(15<<COL0); //default
}
u32 kpmLUT[4][4]= 
{
	{1,2,3,'A'},
	{4,5,6,'B'},
	{7,8,9,'C'},
	{'*',0,'#','D'}
}; 
// Read the PIN from the keypad while hiding the entered digits.
u32 Read_Password()
{
	// Declare variables used to store data for this operation.
	u32 num=0,val,digit=0,i=0;
	// Repeat these steps while the condition is true.
	while(1)
	{
	    // Read the key pressed on the keypad.
	    val=KeyScan();
		// Repeat these steps while the condition is true.
		while(ColScan()==0);
		// Check this condition before continuing.
		if(val>=0 && val<=9)
		{
			// Move the LCD cursor to the required display position.
			CmdLCD(GOTO_LINE2_POS0+(i++));
			// Display one character on the LCD.
			CharLCD('*');
			// Check this condition before continuing.
			if(digit<MAX)
			{
			  // Update this value as part of the current operation.
			  num=num*10+val;
			  digit++;
			}
		}
		// Check this condition before continuing.
		else if(val==35)
		{
		  // Check this condition before continuing.
		  if(digit>0)
		   // Finish this function and return to its caller.
		   return num;
		   //CmdLCD(0x01);
		}
		// Check this condition before continuing.
		else if(val==42)
		{
			// Check this condition before continuing.
			if(digit>0)
			{
			    digit--;
				i--;
		    	// Update this value as part of the current operation.
		    	num=num/10;
			    // Move the LCD cursor to the required display position.
			    CmdLCD(GOTO_LINE2_POS0+i);
			    // Show this message on the LCD.
			    StrLCD(" ");
				// Move the LCD cursor to the required display position.
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		}
	}
}
/*u32 get_number()
{
		u32 num=0,i=0,val,digit=0;
		for(i=0;i<4;i++)
		{	
		   val=KeyScan();
		   if(val>=0 && val<=9)
		   {
		      CmdLCD(GOTO_LINE2_POS0+i);
		       U32LCD(val);
		       num=num*10+val;
			   digit++;
		   }
		   else if(val==35)
		   {
		     return num;
		   }
		   else if(val==42)
		   {
		    if(digit>0)
			{
			    digit--;
				i--;
		    	num=num/10;
			    CmdLCD(GOTO_LINE2_POS0+i);
			    StrLCD(" ");
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		   }
		}
}*/
// Read and validate the transaction amount.
u32 transaction_amnt()
{
	// Declare variables used to store data for this operation.
	u32 num=0,val,digit=0,i=0;
	// Repeat these steps while the condition is true.
	while(1)
	{
	  	// Read the key pressed on the keypad.
	  	val=KeyScan();
		// Repeat these steps while the condition is true.
		while(ColScan()==0);
		// Check this condition before continuing.
		if(val>=0 && val<=9)
		{
			// Move the LCD cursor to the required display position.
			CmdLCD(GOTO_LINE2_POS0+(i++));
			// Display this number on the LCD.
			U32LCD(val);
			// Check this condition before continuing.
			if(digit<MAX)
			{
			  // Update this value as part of the current operation.
			  num=num*10+val;
			  digit++;
			}
		}
		// Check this condition before continuing.
		else if(val==35)
		{
		  // Check this condition before continuing.
		  if(digit>0)
		   {
		      // Check this condition before continuing.
		      if(num==0)
			  {
                // Move the LCD cursor to the required display position.
                CmdLCD(GOTO_LINE2_POS0);
				// Show this message on the LCD.
				StrLCD("                 ");
				// Move the LCD cursor to the required display position.
				CmdLCD(GOTO_LINE2_POS0);
				// Show this message on the LCD.
				StrLCD("Invalid!......");
				// Wait for the requested number of seconds.
				delay_s(1);
			      // Return to the named input step to try again.
			      goto e;
			  }
			  // Check this condition before continuing.
			  if(num%100!=0)
			  {
			    // Move the LCD cursor to the required display position.
			    CmdLCD(GOTO_LINE2_POS0);
				// Show this message on the LCD.
				StrLCD("                 ");
				// Move the LCD cursor to the required display position.
				CmdLCD(GOTO_LINE2_POS0);
				// Show this message on the LCD.
				StrLCD("Invalid!......");
				// Wait for the requested number of seconds.
				delay_s(1);   
				   // Return to the named input step to try again.
				   goto e;
			  }
		      // Finish this function and return to its caller.
		      return num;
		   }
		}
		// Check this condition before continuing.
		else if(val==42)
		{
		  	// Check this condition before continuing.
		  	if(digit>0)
			{
			    digit--;
				i--;
		    	// Update this value as part of the current operation.
		    	num=num/10;
			    // Move the LCD cursor to the required display position.
			    CmdLCD(GOTO_LINE2_POS0+i);
			    // Show this message on the LCD.
			    StrLCD(" ");
				// Move the LCD cursor to the required display position.
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		}
		// Handle the case when the previous condition is false.
		else
		{
		   // Entry point used when the user needs to retry.
		   e:num=0;
		     // Update this value as part of the current operation.
		     digit=0;
			 // Move the LCD cursor to the required display position.
			 CmdLCD(GOTO_LINE2_POS0);
			 // Show this message on the LCD.
			 StrLCD("                  ");
		}
	}
}
// Read a number entered using the keypad.
u32 set_number()
{
	// Declare variables used to store data for this operation.
	u32 num=0,val,digit=0,i=0;
	// Repeat these steps while the condition is true.
	while(1)
	{
	    // Read the key pressed on the keypad.
	    val=KeyScan();
		// Repeat these steps while the condition is true.
		while(ColScan()==0);
		// Check this condition before continuing.
		if(val>=0 && val<=9)
		{
			// Move the LCD cursor to the required display position.
			CmdLCD(GOTO_LINE2_POS0+(i++));
			// Display this number on the LCD.
			U32LCD(val);
			// Check this condition before continuing.
			if(digit<MAX)
			{
			  // Update this value as part of the current operation.
			  num=num*10+val;
			  digit++;
			}
		}
		// Check this condition before continuing.
		else if(val==35)
		{
		  // Check this condition before continuing.
		  if(digit>0)
		   // Finish this function and return to its caller.
		   return num;
		   //CmdLCD(0x01);
		}
		// Check this condition before continuing.
		else if(val==42)
		{
			// Check this condition before continuing.
			if(digit>0)
			{
			    digit--;
				i--;
		    	// Update this value as part of the current operation.
		    	num=num/10;
			    // Move the LCD cursor to the required display position.
			    CmdLCD(GOTO_LINE2_POS0+i);
			    // Show this message on the LCD.
			    StrLCD(" ");
				// Move the LCD cursor to the required display position.
				CmdLCD(GOTO_LINE2_POS0+i);
			}
		}
	}
}
