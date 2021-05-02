/**
******************************************************************************
Project: UART2 and Blink On Board LED
Board: STM8s105k4T6, Black board, ALi Express.
Author: Md Abu Hemjal
Date: 31st April 2021
******************************************************************************
*/

#include "string.h"
#include "stm8s.h"
#include "stm8s_uart2.h"


#define LED_DELAY_MS 100

void CLK_Configuration(void);
void GPIO_Configuration(void);
void UART2_config(void);
int printf(const char *str);  // Print user data and return number of data sent


void main(void)
{
  
  CLK_Configuration();   // Configures clocks 
  GPIO_Configuration();  // Configures GPIOs
  UART2_config();        // UART2 configuration 
  
  while(1)
  {
    UART2_ClearFlag(UART2_FLAG_RXNE);
    printf("My name is Khan\r\n");
    if(UART2_GetFlagStatus(UART2_FLAG_RXNE) == SET)
    {
      uint8_t ch = UART2_ReceiveData8(); 
      UART2_SendData8(ch);
      while(UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);            
    }  
    
    GPIO_WriteHigh(GPIOE, GPIO_PIN_5);  // Blinking onboard LED
    delay_ms(LED_DELAY_MS);
    GPIO_WriteLow(GPIOE, GPIO_PIN_5);
    delay_ms(LED_DELAY_MS);	
    delay_ms(3000);
    
  }
  
}


void CLK_Configuration(void)
{  
  /* Fmaster = 16MHz */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART2, ENABLE);
  
}

void GPIO_Configuration(void)
{
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);  //uart2 TX pin
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);       // uart2 RX pin
  GPIO_DeInit(GPIOE);
  GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
}

void UART2_config(void)
{
  UART2_DeInit();   
  UART2_Init(9600,UART2_WORDLENGTH_8D,UART2_STOPBITS_1,UART2_PARITY_NO, 
             UART2_SYNCMODE_CLOCK_DISABLE,UART2_MODE_TXRX_ENABLE); 
  UART2_Cmd(ENABLE);
}

int printf(const char *str) {
  char i;
  UART2_ClearFlag(UART2_FLAG_TC);
  for(i = 0; i < strlen(str); i++) {		
    UART2_SendData8(str[i]);                
    while(UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);   
  }
  return(i); // Bytes sent
}
