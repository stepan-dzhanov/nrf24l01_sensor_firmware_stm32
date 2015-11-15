
#include "bluetooth.h"
#include "stm32f4xx.h"

#include "usart.h"

char control_str [] = "AT+UART=38400,0,0";


void InitBluetooth()       {
  int i;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_BL,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_BL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_BL_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RS;
  GPIO_Init(GPIO_BL_PORT, &GPIO_InitStructure);
  
  KEY_Disable
  RS_Enable   
  for (i=0;i<100000;i++);
  KEY_Enable
  RS_Disable
  for (i=0;i<100000;i++);
  RS_Enable   
    
  USART_Configuration(38400);
  USART_NVIC_Config();
  
 
  for (i=0;i<100000;i++);
  sprintf_u0( control_str);
  for (i=0;i<100000;i++);
  KEY_Disable
  for (i=0;i<100000;i++);
  RS_Disable
  for (i=0;i<100000;i++);
  RS_Enable
  USART_Configuration(38400);
  USART_NVIC_Config();
  
  
  
  

  
}
