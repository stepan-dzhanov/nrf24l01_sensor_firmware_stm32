
#include "stm32f4xx.h"
#include "ws_spi.h"
#include "config.h"
#include "ad7192.h"



void Delay_tc_(u32 nCount)
{
  while(nCount--)
  {

  }
}


void InitAD7192()       {
  u8 temp;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_CS_CARDIO,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_CS_CARDIO;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_CS_PORT, &GPIO_InitStructure);
  AD7192_Disable;
  Delay_tc_(100000);
  AD7192_Enable;
  SPI_I2S_SendData(Open_SPIx,0xFF);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  temp =  SPI_I2S_ReceiveData(Open_SPIx);
  SPI_I2S_SendData(Open_SPIx,0xFF);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  temp =  SPI_I2S_ReceiveData(Open_SPIx);
  SPI_I2S_SendData(Open_SPIx,0xFF);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  temp =  SPI_I2S_ReceiveData(Open_SPIx);
  SPI_I2S_SendData(Open_SPIx,0xFF);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  temp =  SPI_I2S_ReceiveData(Open_SPIx);
  SPI_I2S_SendData(Open_SPIx,0xFF);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  temp =  SPI_I2S_ReceiveData(Open_SPIx);
  AD7192_Disable;
  

  
  
  Delay_tc_(100000);
 // AD7192_Enable;
 // SetParamAD7192(0x282828, 0x28);
  SetParamAD7192(0x13200C, 0x08);
  SetParamAD7192(0x282828, 0x28);
  Delay_tc_(100000);
 // AD7192_Disable;
 // Delay_tc_(100000);
 // AD7192_Enable;
   ReadDataAD7192(0x48);
   ReadDataAD7192(0x68);
   ReadDataAD7192(0x90);
 // AD7192_Disable;
  
  
  SetParamAD7192(0x000117, 0x10);
  Delay_tc_(100000);
  Delay_tc_(100000);
  Delay_tc_(100000);
  SetParamAD7192(0x932030, 0x08);
  Delay_tc_(100000);
  Delay_tc_(100000);
  Delay_tc_(100000);
  SetParamAD7192(0xB32030, 0x08);
  Delay_tc_(100000);
  Delay_tc_(100000);
  Delay_tc_(100000);
  AD7192_Disable;
  
  
}


void SetParamAD7192(u32 data, u8 comm)   {
  u16 temp;
  AD7192_Enable; 
  SPI_Send_byte(comm);
 
  SPI_Send_byte((u8)(data>>16));
  SPI_Send_byte((u8)(data>>8));
  SPI_Send_byte((u8)(data));
 
  
  AD7192_Disable;
  
}


u32 ReadDataAD7192( u8 comm)   {
  u32 data = 0;
  u8 ldata;
  u8 status=0;
  AD7192_Enable; 
  if(!comm) comm = 0x58; //Read data register in continue mode
  
  SPI_Send_byte(comm);
  
  if(!(comm==0x58))       {
  ldata =  SPI_Receive_byte();
  data |= ldata;
 
  data = data<<8;
  ldata =  SPI_Receive_byte();
  data |= ldata;
  data = data<<8;
  ldata =  SPI_Receive_byte();
  data |= ldata;
  }
  if(comm ==0x58)       {
    Delay_tc_(100);
     ldata =  SPI_Receive_byte();
    data |= ldata;
     status = ldata;
    data = data<<8;
    ldata =  SPI_Receive_byte();
    data |= ldata;
    data = data<<8;
    ldata =  SPI_Receive_byte();
    data |= ldata;
    data = data<<8;
    ldata =  SPI_Receive_byte();
    data |= ldata;
    Delay_tc_(100000);
    if((status&0x80) == 0){
      status = status;
      ldata =0;
      if(comm == 0x58);
      
      
    }
    
  }
  
  AD7192_Disable;
  return data;
}