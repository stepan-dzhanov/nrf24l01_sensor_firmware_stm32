#ifndef _USART3_H
#define _USART3_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for COM port1, connected to USART3
 */  
#define Open_USART3                        USART3
#define Open_USART3_CLK                    RCC_APB1Periph_USART3

#define Open_USART3_TX_PIN                 GPIO_Pin_10
#define Open_USART3_TX_GPIO_PORT           GPIOB
#define Open_USART3_TX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define Open_USART3_TX_SOURCE              GPIO_PinSource10
#define Open_USART3_TX_AF                  GPIO_AF_USART3


#define Open_USART3_RX_PIN                 GPIO_Pin_11
#define Open_USART3_RX_GPIO_PORT           GPIOB
#define Open_USART3_RX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define Open_USART3_RX_SOURCE              GPIO_PinSource11
#define Open_USART3_RX_AF                  GPIO_AF_USART3

#define Open_USART3_IRQn                   USART3_IRQn	 

void USART3_Configuration(int baud_rate);
void USART3_NVIC_Config(void);
void USART3_SendChar( uint8_t ch );
void sprintf_u3( char *string);
void SentUart3( char *data, char len);

#endif /*_USART_H*/
