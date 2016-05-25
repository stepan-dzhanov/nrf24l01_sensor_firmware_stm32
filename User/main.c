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
#include "nrf905_driver.h"

    
#include <string.h>
#include <stdio.h>


    

 
 
uint8_t dataOut[32], dataIn[32];

 int main(void)  {
   
    char str[40];
    
     if (SysTick_Config(SystemCoreClock / 1000))     { 
        /* Capture error */ 
         while (1);
     }
    
    Nrf905Init() ;
    
    
    while (1) {
      ReceivePacket(); //TransmitPacket(unsigned short dByte) for TX mode;
     // while(1);
     
        /* If data is ready on NRF24L01+ */
       
       
    }
 
  
   
   
 
   
            
            
            
       
        
        
        
        
        
}



