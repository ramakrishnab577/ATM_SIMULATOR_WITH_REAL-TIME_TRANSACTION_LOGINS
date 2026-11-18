// delay.c

// Generate an approximate delay in microseconds using a software loop.
void delay_us(unsigned int dly_us)
{
    // Multiply the requested microseconds by 12 to calculate the loop count.
    dly_us *= 12;

    // Decrement the loop counter until it reaches zero to create a delay.
    while(dly_us--);
}

// Generate an approximate delay in milliseconds using a software loop.
void delay_ms(unsigned int dly_Ms)
{
    // Multiply the requested milliseconds by 12000 to calculate the loop count.
    dly_Ms *= 12000;

    // Decrement the loop counter until it reaches zero to create a delay.
    while(dly_Ms--);
}

// Generate an approximate delay in seconds using a software loop.
void delay_s(unsigned int dly_s)
{
    // Multiply the requested seconds by 12000000 to calculate the loop count.
    dly_s *= 12000000;

    // Decrement the loop counter until it reaches zero to create a delay.
    while(dly_s--);
}
			  															                    
