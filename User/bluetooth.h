#ifndef _BLUE_
#define _BLUE_

#define RCC_GPIO_BL				RCC_AHB1Periph_GPIOE
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_BL			        GPIO_Pin_1
#define GPIO_PIN_RS			        GPIO_Pin_0

#define GPIO_BL_PORT				GPIOE

#define KEY_Enable 			        GPIO_SetBits(GPIO_BL_PORT,GPIO_PIN_BL);
#define KEY_Disable 			        GPIO_ResetBits(GPIO_BL_PORT,GPIO_PIN_BL);

#define RS_Enable 			        GPIO_SetBits(GPIO_BL_PORT,GPIO_PIN_RS);
#define RS_Disable 			        GPIO_ResetBits(GPIO_BL_PORT,GPIO_PIN_RS);

void InitBluetooth();


#endif