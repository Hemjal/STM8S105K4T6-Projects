#include "stm8s_delay.h"
#include "stm8s.h"


void delay_us(unsigned int  value)
{
	register unsigned int loops = (int) (dly_const * value) ;
	
	while(loops)
	{
		__asm ("nop");
		loops--;
	};
}


void delay_ms(unsigned int  value)
{
	while(value)
	{
		delay_us(1000);
		value--;
	};
}