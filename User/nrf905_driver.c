/*
 * File name:
     NRF905_DRIVER.c
 * Copyright:
     HAZEM ELSAYED.
     hazem.elsayed@telia.com
 * Revision History:
     20150822:
       - Rev.1
*/
#include "nrf905_driver.h"
#include "timer.h" 
#include "stm32f4xx.h"
#include "tm_stm32f4_spi.h"
#include "tm_stm32f4_gpio.h"



#define ASSIGN_TX_ADDR_REG      0x22 // ASSIGN TX ADDRESS REGISTER
#define TX_PAYLOAD_REG          0x20 // TX PAYLOAD WIDTH REGISTER
#define RX_PAYLOAD_REG          0x24 // TX PAYLOAD WIDTH REGISTER
#define RX_PAYLOAD_WEDTH_REG    0x03 // RX PAYLOAD WIDTH REGISTER
#define RX_PAYLOAD_WEDTH        0x01 // RX PAYLOAD WIDTH 1-32 BYTE (CAN BE CHANGED)
#define TX_PAYLOAD_WEDTH_REG    0x04 // TX PAYLOAD WIDTH REGISTER
#define TX_PAYLOAD_WEDTH        0x01 // TX PAYLOAD WIDTH 1-32 BYTE (CAN BE CHANGED)
#define CHANNEL_REG             0x00 // CHANNELS RANGE REGISTER 1-170
#define CHANNEL                 0x6C // CHANNEL NO 108  (CAN BE CHANGED)
#define XTAL_REG                0x09 // XTAL SETTING REGISTER
#define _16MHZ                  0xD8 // XTAL 16 MHZ
#define TXRX_ADDR_WIDTH_REG     0x02 // TX/RX ADDRESS WIDTH REGISTER
#define _4BYTE                  0x44 // 4 BYTE ADDRESS WIDTH
#define NRF_PWR_REG             0x01 // NRF905 POWER REGISTER
#define NRF_PWR_10DBM           0x0C // +10 dBm
#define START_SPI               0x00 // ENTER SPI MODE
#define EXIT_SPI                0x01 // EXIT SPI MODE
#define SPI_RECOVER_TIME        0x32 // EXIT SPI MODE
#define POWER_UP_REC_TIME       0x05 //POWER UP RECOVER TIME
#define RX_REG_LOC              0x05 // RX REGISTER LOCATION
#define _4_BYTE                 0x04 // 4 BYTES
#define INIT                    0x00 // INITIAL VALUE
#define STAT_ACTIVE             0x01 // ACTIVE STATUSE
#define STAT_INACTIVE           0x00 // INACTIVE STATUSE
#define FLUSH_RX_PAYLOAD        0x00 //FLUSH RX PAYLOAD
#define END_TX                  0x00 //END_TX
/************************************************************************
* Nrf905 Variables
************************************************************************/
const unsigned short txAddr[_4_BYTE ]={0x14,0xD7,0x6B,0x21};    // TX ADDRESS
const unsigned short rxAddr[_4_BYTE ]={0x14,0xD7,0x6B,0x21};    // RX ADDRESS
int cntTx, cntRx;                         // TX/RX COUNTER CONTROL
unsigned short receive=INIT;             // RECIEVED DATA
/************************************************************************
* Functions
************************************************************************/

void Delay_us(int delay)        {
  int i;
  for(i=0;i<delay*1000;i++);
}



void Nrf905RegCom (unsigned short RegCom, unsigned short RegValue)
{
    NRF905_CSN_LOW;
    TM_SPI_Send(NRF905_SPI,RegCom);
    TM_SPI_Send(NRF905_SPI,RegValue);
    NRF905_CSN_HIGH;
    Delay_us(10);
}
void PowerDownMode(void)
  {
    NRF905_PWRUP_LOW;
   // Delay_us(100);
  }
void PowerUpMode(void)
  {
    NRF905_PWRUP_HIGH;
    Delay_us(100);
  }
void  TransmitMode(void)
  {
    NRF905_TXEN_HIGH;
    NRF905_CE_HIGH;
    Delay_us(10);
  }
void ReceiveMode(void)
  {
    NRF905_TXEN_LOW;
    NRF905_CE_HIGH;
    Delay_us(10);
  }
void TransmitPacket(unsigned short dByte)
  {
     TransmitMode();
     Nrf905RegCom(TX_PAYLOAD_REG,dByte);  // Transmit payload
     NRF905_CE_LOW;           // end trasmit mode
  }
void Nrf905Init(void)
{
    TM_GPIO_Init(NRF905_CSN_PORT,NRF905_CSN_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
    TM_GPIO_Init(NRF905_CE_PORT,NRF905_CE_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
    TM_GPIO_Init(NRF905_PWRUP_PORT,NRF905_PWRUP_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
    TM_GPIO_Init(NRF905_TXEN_PORT,NRF905_TXEN_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
    TM_GPIO_Init(NRF905_DR_PORT,NRF905_DR_PIN, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
    
    NRF905_CSN_HIGH;
    NRF905_TXEN_LOW;
    NRF905_CE_LOW;
    NRF905_PWRUP_LOW;
    
    
    TM_SPI_Init(NRF905_SPI, NRF905_SPI_PINS);
    Delay_us(5000);
    
    PowerDownMode();                                    //enable spi write mode
    Nrf905RegCom(CHANNEL_REG, CHANNEL);                //CHANNELS 1 TO 170
    Nrf905RegCom(XTAL_REG, _16MHZ);                      //XTAL
    Nrf905RegCom(TXRX_ADDR_WIDTH_REG, _4BYTE);           //TX/RX address width
    Nrf905RegCom(TX_PAYLOAD_WEDTH_REG, TX_PAYLOAD_WEDTH);  //Tx payload width
    Nrf905RegCom(RX_PAYLOAD_WEDTH_REG, RX_PAYLOAD_WEDTH);  //Rx payload width
    Nrf905RegCom(NRF_PWR_REG,NRF_PWR_10DBM);         // Output power = +10dBm
    NRF905_CSN_LOW;
    TM_SPI_Send(NRF905_SPI,ASSIGN_TX_ADDR_REG);                  //tx address  4 byte
    for (cntTx=INIT;cntTx<_4_BYTE;cntTx++)
    TM_SPI_Send(NRF905_SPI,txAddr[cntTx]);
    NRF905_CSN_HIGH;
    Delay_us(1);
    for (cntRx=INIT;cntRx<_4_BYTE;cntRx++)
    Nrf905RegCom((cntRx+RX_REG_LOC),rxAddr[cntRx]);  //RX address 4 bytes
    PowerUpMode();              // Exit programing mode & power up nrf905 unit
  }
unsigned short ReceivePacket(void)
 {
   char recieve =0;
   ReceiveMode();
   if(TM_GPIO_GetInputPinValue(NRF905_DR_PORT, NRF905_DR_PIN)){
     NRF905_CE_LOW;
     NRF905_CSN_LOW;
     TM_SPI_Send(NRF905_SPI,RX_PAYLOAD_REG);
     receive=TM_SPI_Send(NRF905_SPI,INIT);
     NRF905_CSN_HIGH;
     return receive ;     // Return recieved data
     
   }
    
 //  NRF905_CE_LOW;
  // NRF905_CSN_LOW;
  // TM_SPI_Send(NRF905_SPI,RX_PAYLOAD_REG);
  // receive=TM_SPI_Send(NRF905_SPI,INIT);
  //  CS_NRF_bit=EXIT_SPI;
  // NRF905_CSN_HIGH;
 //  return receive ;     // Return recieved data
   
}