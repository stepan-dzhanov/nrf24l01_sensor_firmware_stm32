#ifndef _AD5231_
#define _AD5231_




#define RCC_GPIO_CS				RCC_AHB1Periph_GPIOC
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS_AM  			GPIO_Pin_6
#define GPIO_PIN_CS_BR  			GPIO_Pin_7
#define GPIO_CS_PORT				GPIOC

#define AD5231_AM_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_AM);
#define AD5231_AM_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_AM);

#define AD5231_BR_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_BR);
#define AD5231_BR_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_BR);


#define RCC_GPIO_CS1				RCC_AHB1Periph_GPIOA
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS_BR1  			GPIO_Pin_4
#define GPIO_PIN_CS_FA  			GPIO_Pin_2
#define GPIO_CS1_PORT				GPIOA

#define AD5231_FA_Enable 			GPIO_ResetBits(GPIO_CS1_PORT,GPIO_PIN_CS_FA);
#define AD5231_FA_Disable 			GPIO_SetBits(GPIO_CS1_PORT,GPIO_PIN_CS_FA);

#define AD5231_BR1_Enable 			GPIO_ResetBits(GPIO_CS1_PORT,GPIO_PIN_CS_BR1);
#define AD5231_BR1_Disable 			GPIO_SetBits(GPIO_CS1_PORT,GPIO_PIN_CS_BR1);








void InitAD5231(void);
void SetParamAD5231(u16 param, u8 ch);

#endif
