#include "stm32f4xx.h"
#include"leds.h"


void InitLeds()       {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_LED,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LPWM;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_LED,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RPWM;
  GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);
 
  RCC_AHBxPeriphClockCmd(RCC_GPIO_LED,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_L1;
  GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure); 
  RCC_AHBxPeriphClockCmd(RCC_GPIO_LED,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_L2;
  GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure); 
  RCC_AHBxPeriphClockCmd(RCC_GPIO_LED,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_R1;
  GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure); 
  RCC_AHBxPeriphClockCmd(RCC_GPIO_LED,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_R2;
  GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure); 

  
  L1_Disable 
  R1_Disable
  L2_Enable
  R2_Enable
  RPWM_Enable
  LPWM_Enable 
}
    
void Forward()  {
  RPWM_Disable
  LPWM_Disable 
  
  
  L1_Disable 
  R1_Disable
  L2_Enable
  R2_Enable
  RPWM_Enable
  LPWM_Enable 
  
}

void Reverse()  {
  RPWM_Disable
  LPWM_Disable 
  
  
  L2_Disable 
  R2_Disable
  L1_Enable
  R1_Enable
  RPWM_Enable
  LPWM_Enable 
  
}


void Cir()  {
  RPWM_Disable
  LPWM_Disable 
  
  
  L2_Disable 
  R1_Disable
  L1_Enable
  R2_Enable
  RPWM_Enable
  LPWM_Enable 
  
}
    