/**
******************************************************************************
Project: Blink On Board LED
Board: STM8s105k4T6, Black board, ALi Express.
Author: Md Abu Hemjal
Date: 31st March 2021
******************************************************************************
*/

#include "stm8s.h"


#define LED_DELAY_MS 100

void CLK_Configuration(void);
void GPIO_Configuration(void);
void Toggle(void);


void main(void)
{
  /* Configures clocks */
  CLK_Configuration();
  
  /* Configures GPIOs */
  GPIO_Configuration();
  
  while(1)
	{
	GPIO_WriteHigh(GPIOE, GPIO_PIN_5);
	delay_ms(LED_DELAY_MS);
	GPIO_WriteLow(GPIOE, GPIO_PIN_5);
	delay_ms(LED_DELAY_MS);	
	}
  
}


void CLK_Configuration(void)
{
  
  /* Fmaster = 16MHz */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
}

void GPIO_Configuration(void)
{
  GPIO_DeInit(GPIOE);
  GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
}
