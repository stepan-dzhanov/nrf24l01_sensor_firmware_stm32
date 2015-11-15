#include "stm32f4xx.h"
#include "ad7887.h"
#include "config.h"


void AD7887Init()       {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_IM;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_RE;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);	
  AD7887_IM_Disable;
  AD7887_RE_Disable;
}

u16 AD7887GetData(u8 ch)        {
  u16 temp,temp1,temp2, result;
  if(ch)        {
    AD7887_RE_Enable;
    
    SPI_I2S_SendData(Open_SPIx,AD7887_STATUS_WORD);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    result =  SPI_I2S_ReceiveData(Open_SPIx);
    temp2 = result;
    temp1 = temp;
    temp = temp<<8;
    result |= temp;
    
    AD7887_RE_Disable;
    return result;
  }
  else {
    AD7887_IM_Enable;
    
    SPI_I2S_SendData(Open_SPIx,AD7887_STATUS_WORD);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    result =  SPI_I2S_ReceiveData(Open_SPIx);
    temp = temp<<8;
    result |= temp;
    
    AD7887_IM_Disable;
    return result;
  }
  //return 0;
  
}

