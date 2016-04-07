/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "timer.h" 
#include "tm_stm32f4_nrf24l01.h"

    
#include <string.h>
#include <stdio.h>


    
/* My address */
uint8_t MyAddress[] = {
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7
};
/* Receiver address */
uint8_t TxAddress[] = {
    0x7E,
    0x7E,
    0x7E,
    0x7E,
    0x7E
};
 
uint8_t dataOut[32], dataIn[32];

int main(void)  {
    TM_NRF24L01_Transmit_Status_t transmissionStatus;
    char str[40];
    
     if (SysTick_Config(SystemCoreClock / 1000))     { 
        /* Capture error */ 
         while (1);
     }
     TM_GPIO_Init(GPIOD, GPIO_PIN_14|GPIO_PIN_12, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
  
    /* Initialize NRF24L01+ on channel 15 and 32bytes of payload */
    /* By default 2Mbps data rate and 0dBm output power */
    /* NRF24L01 goes to RX mode by default */
    TM_NRF24L01_Init(19, 32);
    
    /* Set 2MBps data rate and -18dBm output power */
    TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_2M, TM_NRF24L01_OutputPower_0dBm);
    
    /* Set my address, 5 bytes */
    TM_NRF24L01_SetMyAddress(MyAddress);
    /* Set TX address, 5 bytes */
    TM_NRF24L01_SetTxAddress(TxAddress);
    
    /* Reset counter */
   
   
    
    
    
    
    
    
    
    
    
    
    
    while (1) {
        /* Every 2 seconds */
        while(GetTimer()<1000);
        ResetTimer();
            /* Fill data with something */
            sprintf((char *)dataOut, "iam");
            dataOut[3] = 2;
            dataOut[4] = 2;
              dataOut[5] = 'B';
            /* Display on USART */
         
            /* Transmit data, goes automatically to TX mode */
            TM_GPIO_SetPinHigh(GPIOD, GPIO_PIN_12);
            TM_NRF24L01_Transmit(dataOut);
            
            /* Turn on led to indicate sending */
          
            /* Wait for data to be sent */
            do {
               transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
            } while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
            /* Turn off led */
            TM_GPIO_SetPinLow(GPIOD, GPIO_PIN_12);
            
            
            /* Go back to RX mode */
            TM_NRF24L01_PowerUpRx();
            
             while(GetTimer()<100);
            /* Wait received data, wait max 100ms, if time is larger, then data were probably lost */
            if(TM_NRF24L01_DataReady()){
              
            
            
           
                /* Get data from NRF2L01+ */
                TM_NRF24L01_GetData(dataIn);
                 sprintf((char *)dataOut, "tst");
                if(!memcmp(&dataIn[1],&dataOut,3)){
                 sprintf((char *)dataOut, "OK");
                 TM_NRF24L01_Transmit(dataOut);
            
            /* Turn on led to indicate sending */
          
            /* Wait for data to be sent */
            do {
               transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
            } while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
                 
                 
                 
                
                }
                
                /* Check transmit status */
                if (transmissionStatus == TM_NRF24L01_Transmit_Status_Ok) {
                   ;
                } else if (transmissionStatus == TM_NRF24L01_Transmit_Status_Lost) {
                  ;
                } 
                
        
        
            }
    
 
  
   
  
    }
 
   
            
            
            
       
        
        
        
        
        
}



