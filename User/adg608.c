#include "stm32f4xx.h"
#include "adg608.h"





void InitADG608()       {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS608,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_A0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_CS608_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS608,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_A1;
  GPIO_Init(GPIO_CS608_PORT, &GPIO_InitStructure);	

  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS608,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_A2;
  GPIO_Init(GPIO_CS608_PORT, &GPIO_InitStructure);	
  
 ////////////////////////////////////////////////////// 
  RCC_AHBxPeriphClockCmd(RCC_GPIO_EN,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_EN_EN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_EN_PORT, &GPIO_InitStructure);
  
 
  ADG608_A0_Disable;
  ADG608_A1_Disable;
  ADG608_A2_Disable;
  ADG608_EN_Disable;
  
}

void SetADG608(u8 a0,u8 a1,u8 a2)       {
  
  if(a0)  {ADG608_A0_Enable;}
  
  else ADG608_A0_Disable;
  if(a1)  {ADG608_A1_Enable;}
  else {ADG608_A1_Disable;}
  if(a2)  {ADG608_A2_Enable;}
  else {ADG608_A2_Disable;}
  
  ADG608_EN_Enable;
  
}