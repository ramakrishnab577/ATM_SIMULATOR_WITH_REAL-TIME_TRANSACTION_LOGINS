//delay.c
void delay_us(unsigned int dly_us)
{
   dly_us*=12;
   while(dly_us--);
}
void delay_ms(unsigned int dly_Ms)
{
	  dly_Ms*=12000;
      while(dly_Ms--);
}
void delay_s(unsigned int dly_s)
{
	  dly_s*=12000000;
      while(dly_s--);
}
			  															                    