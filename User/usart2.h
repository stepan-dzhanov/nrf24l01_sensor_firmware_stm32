#ifndef _USART2_H
#define _USART2_H

#include <stdio.h>
#include "stm32f4xx.h"

/**
 * @brief Definition for COM port1, connected to USART3
 */  
#define Open_USART2                        USART2
#define Open_USART2_CLK                    RCC_APB1Periph_USART2

#define Open_USART2_TX_PIN                 GPIO_Pin_2
#define Open_USART2_TX_GPIO_PORT           GPIOA
#define Open_USART2_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define Open_USART2_TX_SOURCE              GPIO_PinSource2
#define Open_USART2_TX_AF                  GPIO_AF_USART2


#define Open_USART2_RX_PIN                 GPIO_Pin_3
#define Open_USART2_RX_GPIO_PORT           GPIOA
#define Open_USART2_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define Open_USART2_RX_SOURCE              GPIO_PinSource3
#define Open_USART2_RX_AF                  GPIO_AF_USART2

#define Open_USART2_IRQn                   USART2_IRQn	 

void USART2_Configuration(int baud_rate);
void USART2_NVIC_Config(void);
void USART2_SendChar( uint8_t ch );
void sprintf_u2( char *string);
void SentUart2( char *data, char len);

#endif /*_USART_H*/
