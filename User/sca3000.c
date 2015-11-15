#include "stm32f4xx.h"
#include "sca3000.h"
#include "ws_spi.h"
#include "config.h"
void InitSCA3000()       {
  int i;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBxPeriphClockCmd(RCC_GPIO_SCA,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SCA_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_SCA_PORT, &GPIO_InitStructure);
  
  RCC_AHBxPeriphClockCmd(RCC_GPIO_SCA,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SCA_RES;
  GPIO_Init(GPIO_SCA_PORT, &GPIO_InitStructure);
  
  SCA_CS_Enable
  SCA_RES_Enable
  for (i=0; i<=0xFFFF; i++);
  SCA_RES_Disable
  for (i=0; i<=0xFFFF; i++);
  SCA_RES_Enable 
  
  SPI_Configuration_M1();  
   
}

s16 SCA3000_Read(s16 *x,s16 *y, s16 *z)       {
  u32 i;
  s16 result,result1;
  char i_addr = 0x04;
  i_addr = i_addr<<2;
  SCA_CS_Disable
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,i_addr);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result = SPI_I2S_ReceiveData(Open_SPIx);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,0x00);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result = SPI_I2S_ReceiveData(Open_SPIx);

  
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,0x00);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result1 = SPI_I2S_ReceiveData(Open_SPIx);
  SCA_CS_Enable  
 

  
 
  
  
  result1 = result1<<8;
 // result = result>>3;
  result1 |= result;
 
 // result1 &= 0x0FFF ;
 // if(0x1000&result1) {
  //  result1^=0x8000;
   // result1 = (s16)result1*(-1);
 // }
  *x = result1/8;
 
  
  ////***********************************Y axis************************
  for(i=0;i<2000;i++);
  i_addr = 0x06;
  i_addr = i_addr<<2;
  SCA_CS_Disable
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,i_addr);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result = SPI_I2S_ReceiveData(Open_SPIx);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,0x00);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result = SPI_I2S_ReceiveData(Open_SPIx);

  
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,0x00);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result1 = SPI_I2S_ReceiveData(Open_SPIx);
  SCA_CS_Enable  
 

  
 
  
  
  result1 = result1<<8;
 // result = result>>3;
  result1 |= result;
 
 // result1 &= 0x0FFF ;
 // if(0x1000&result1) {
 //   result1^=0x8000;
    //result1 = (s16)result1*(-1);
 // }
  *y = result1/8;
  
//************************ Z Axis*****************************************
  for(i=0;i<2000;i++);
  i_addr = 0x08;
  i_addr = i_addr<<2;
  SCA_CS_Disable
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,i_addr);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result = SPI_I2S_ReceiveData(Open_SPIx);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,0x00);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result = SPI_I2S_ReceiveData(Open_SPIx);

  
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(Open_SPIx,0x00);
  while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
  result1 = SPI_I2S_ReceiveData(Open_SPIx);
  SCA_CS_Enable  
 

  
 
  
  
  result1 = result1<<8;
 // result = result>>3;
  result1 |= result;
 
 // result1 &= 0x0FFF ;
 // if(0x1000&result1) {
 //   result1^=0x8000;
    //result1 = (s16)result1*(-1);
 // }
  *z = result1/8;
  
  
  
 
  return result1;

}