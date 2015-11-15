#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for COM port1, connected to USART3
 */  
#define Open_USART                        USART1
#define Open_USART_CLK                    RCC_APB2Periph_USART1

#define Open_USART_TX_PIN                 GPIO_Pin_6
#define Open_USART_TX_GPIO_PORT           GPIOB
#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define Open_USART_TX_SOURCE              GPIO_PinSource6
#define Open_USART_TX_AF                  GPIO_AF_USART1


#define Open_USART_RX_PIN                 GPIO_Pin_7
#define Open_USART_RX_GPIO_PORT           GPIOB
#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define Open_USART_RX_SOURCE              GPIO_PinSource7
#define Open_USART_RX_AF                  GPIO_AF_USART1

#define Open_USART_IRQn                   USART1_IRQn	 

void USART_Configuration(int baud_rate);
void USART_NVIC_Config(void);
void USART_SendChar( uint8_t ch );
void sprintf_u0( char *string);
void SentUart( char *data, char len);

#endif /*_USART_H*/
