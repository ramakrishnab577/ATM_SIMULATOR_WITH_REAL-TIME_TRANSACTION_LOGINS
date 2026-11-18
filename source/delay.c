//delay.c
// Define the function that performs this operation.
void delay_us(unsigned int dly_us)
{
   // Update this value as part of the current operation.
   dly_us*=12;
   // Repeat these steps while the condition is true.
   while(dly_us--);
}
// Define the function that performs this operation.
void delay_ms(unsigned int dly_Ms)
{
	  // Update this value as part of the current operation.
	  dly_Ms*=12000;
      // Repeat these steps while the condition is true.
      while(dly_Ms--);
}
// Define the function that performs this operation.
void delay_s(unsigned int dly_s)
{
	  // Update this value as part of the current operation.
	  dly_s*=12000000;
      // Repeat these steps while the condition is true.
      while(dly_s--);
}
			  															                    