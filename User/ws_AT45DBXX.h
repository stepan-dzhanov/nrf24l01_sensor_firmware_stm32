/*********************************************************************************************************
*
* File                : ws_AT45DBXX.h
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#ifndef _AT45DBXX_H
#define _AT45DBXX_H

#define RCC_GPIO_CS				RCC_AHB1Periph_GPIOC
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS				GPIO_Pin_4
#define GPIO_CS_PORT				GPIOC

#define AT45DBXX_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS);
#define AT45DBXX_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS);


void AT45DBXX_Init(void);
static void AT45DBXX_BUSY(void);
void AT45DBXX_Read_ID(u8 *Data);

void write_buffer(u16 BufferOffset,u8 Data);
u8 read_buffer(u16 BufferOffset);

#include "ws_spi.h"

#endif /*_AT45DBXX_H*/

