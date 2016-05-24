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
#include "rfm12b.h"

    
#include <string.h>
#include <stdio.h>



 
uint8_t dataOut[32], dataIn[32];

int main(void)  {
     
     uint8_t  ChkSum;
     uint16_t status;
 
    
     if (SysTick_Config(SystemCoreClock / 1000))     { 
        /* Capture error */ 
         while (1);
     }
     TM_GPIO_Init(GPIOD, GPIO_PIN_14|GPIO_PIN_12, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
     
      
      RFM12B_Init();
      status = RFM12B_WriteCMD(0x0000);
      RFM12B_WriteCMD(0xCA81);//read status register
      RFM12B_WriteCMD(0xCA83);//!er,!ebb,ET,ES,EX,!eb,!ew,DC
      
    /*RFM12B_WriteCMD(0x0000);
      RFM12B_WriteCMD(0x8239);
      RFM12B_WriteFSK(0xAA);//PREAMBLE
      RFM12B_WriteFSK(0xAA);//PREAMBLE
      RFM12B_WriteFSK(0xAA);//PREAMBLE
      RFM12B_WriteFSK(0x2D);//SYNC HI BYTE
      RFM12B_WriteFSK(0xD4);//SYNC LOW BYTE
      RFM12B_WriteFSK(0x30);//DATA BYTE 0
      ChkSum+=0x30;
      RFM12B_WriteFSK(0x31);//DATA BYTE 1
      ChkSum+=0x31;
      RFM12B_WriteFSK(0x32);
      ChkSum+=0x32;
      RFM12B_WriteFSK(0x33);
      ChkSum+=0x33;
      RFM12B_WriteFSK(0x34);
      ChkSum+=0x34;
      RFM12B_WriteFSK(0x35);
      ChkSum+=0x35;
      RFM12B_WriteFSK(0x36);
      ChkSum+=0x36;
      RFM12B_WriteFSK(0x37);
      ChkSum+=0x37;
      RFM12B_WriteFSK(0x38);
      ChkSum+=0x38;
      RFM12B_WriteFSK(0x39);
      ChkSum+=0x39;
      RFM12B_WriteFSK(0x3A);
      ChkSum+=0x3A;
      RFM12B_WriteFSK(0x3B);
      ChkSum+=0x3B;
      RFM12B_WriteFSK(0x3C);
      ChkSum+=0x3C;
      RFM12B_WriteFSK(0x3D);
      ChkSum+=0x3D;
      RFM12B_WriteFSK(0x3E);
      ChkSum+=0x3E;
      RFM12B_WriteFSK(0x3F); //DATA BYTE 15
      ChkSum+=0x3F;
      RFM12B_WriteFSK(ChkSum); //send chek sum
      RFM12B_WriteFSK(0xAA);//DUMMY BYTE
      RFM12B_WriteFSK(0xAA);//DUMMY BYTE
      RFM12B_WriteFSK(0xAA);//DUMMY BYTE*/
      
      
      
      
      
      while(1) {
        status = RFM12B_WriteCMD(0x0000);
        if(status&0x8000 ){
          status = RFM12B_WriteCMD(0xB000);
          ChkSum = 0;
          
        }
      }
      
}     
    
      
  //    RFM12B_WriteCMD(0x8201);
    //  while(1);
              
//}



