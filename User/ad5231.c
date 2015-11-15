#include "stm32f4xx.h"
#include "ad5231.h"
#include "config.h"
#include "ws_spi.h"




void InitAD5231()       {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_AM;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_BR;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);	
  
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS1,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_FA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_CS1_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS1,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_BR1;
  GPIO_Init(GPIO_CS1_PORT, &GPIO_InitStructure);	
  
 
  AD5231_AM_Disable;
  AD5231_BR_Disable;
  
  AD5231_BR1_Disable;
 
  AD5231_FA_Disable;
 
  
}

void SetParamAD5231(u16 param, u8 ch)   {
    u8 temp;
    //SPI_Configuration_M1();
    if (ch==1) AD5231_AM_Enable 
    else if (ch==0) AD5231_BR_Enable 
    else if (ch==2) AD5231_BR1_Enable 
    
    SPI_I2S_SendData(Open_SPIx,0xB0);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(param>>8));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(param));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    
    if (ch==1) AD5231_AM_Disable 
    else if (ch==0) AD5231_BR_Disable 
    else if (ch==2) AD5231_BR1_Disable
    // SPI_Configuration_M2();
    
}