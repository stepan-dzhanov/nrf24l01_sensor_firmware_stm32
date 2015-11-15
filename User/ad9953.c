#include "stm32f4xx.h"
#include "ad9953.h"
#include "config.h"
#include "ws_spi.h"

void Delay_tc(u32 nCount)
{
  while(nCount--)
  {

  }
}



void InitAD9953()       {
  u8 temp;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_DDS1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_DDS2;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);	
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RESDDS;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);	
  
  ////////
  RCC_AHBxPeriphClockCmd(RCC_GPIO_SYNC,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SYNC_SYNC1 | GPIO_PIN_SYNC_SYNC2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_SYNC_PORT, &GPIO_InitStructure);
  
  
  
  AD9953_SYNC1_Disable;
  AD9953_SYNC2_Disable;
  AD9953_DDS1_Disable;
  AD9953_DDS2_Disable;
  AD9953_SET_RES 
  Delay_tc(100000);
  AD9953_RESET_RES 
    
   AD9953_DDS1_Enable;
    
    SPI_I2S_SendData(Open_SPIx,0x01);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x02);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x04);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
  
    AD9953_DDS1_Disable;
    Delay_tc(100000);
    /*AD9953_DDS1_Enable;
    
    
    SPI_I2S_SendData(Open_SPIx,0x04);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>24));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>16));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>8));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq&0x000000FF));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
 
    AD9953_DDS1_Disable;
    Delay_tc(100000);*/
    AD9953_DDS1_Enable;
    
  
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x02);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
     
    AD9953_DDS1_Disable;

    //AD9953_SYNC2_Enable;
    Delay_tc(100000);
   // AD9953_SYNC2_Disable;
    
//***************************DDS2 Init*****************************************
    AD9953_DDS2_Enable;
    
    SPI_I2S_SendData(Open_SPIx,0x01);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x04);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
  
    AD9953_DDS2_Disable;
    Delay_tc(100000);
    AD9953_DDS2_Enable;
    
    
    SPI_I2S_SendData(Open_SPIx,0x05);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x10);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    
     AD9953_DDS2_Disable;
    Delay_tc(100000);
    /*AD9953_DDS2_Enable;
    
    
    
    
    
    
    
     SPI_I2S_SendData(Open_SPIx,0x04);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>24));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>16));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>8));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq&0x000000FF));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
 
    AD9953_DDS2_Disable;
    Delay_tc(100000);*/
    AD9953_DDS2_Enable;
    
  
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x02);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,0x00);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
     
    AD9953_DDS2_Disable;
    
    AD9953_SYNC2_Enable;
    Delay_tc(100);
    AD9953_SYNC2_Disable;
    
//************************************read****************
    
   
    
  
}

void SetParamAD9953(u32 freq, u8 ch)   {
    u16 temp;
    AD9953_DDS2_Enable;
    SPI_I2S_SendData(Open_SPIx,0x04);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>24));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>16));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>8));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq&0x000000FF));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    AD9953_DDS2_Disable;
    
   
    AD9953_DDS1_Enable;
    SPI_I2S_SendData(Open_SPIx,0x04);
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>24));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>16));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq>>8));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    SPI_I2S_SendData(Open_SPIx,(u8)(freq&0x000000FF));
    while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
    temp =  SPI_I2S_ReceiveData(Open_SPIx);
    AD9953_DDS1_Disable;
    
    
     AD9953_SYNC2_Enable;
    Delay_tc(100);
    AD9953_SYNC2_Disable;
    
    
    
    
}