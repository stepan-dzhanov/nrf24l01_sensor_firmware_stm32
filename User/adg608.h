#ifndef _ADG608_
#define _ADG608_




#define RCC_GPIO_CS608				RCC_AHB1Periph_GPIOA
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS_A0  			GPIO_Pin_11
#define GPIO_PIN_CS_A1  			GPIO_Pin_12
#define GPIO_PIN_CS_A2  			GPIO_Pin_8
#define GPIO_CS608_PORT				GPIOA

#define ADG608_A0_Enable 			GPIO_SetBits(GPIO_CS608_PORT,GPIO_PIN_CS_A0);
#define ADG608_A0_Disable 			GPIO_ResetBits(GPIO_CS608_PORT,GPIO_PIN_CS_A0);

#define ADG608_A1_Enable 			GPIO_SetBits(GPIO_CS608_PORT,GPIO_PIN_CS_A1);
#define ADG608_A1_Disable 			GPIO_ResetBits(GPIO_CS608_PORT,GPIO_PIN_CS_A1);

#define ADG608_A2_Enable 			GPIO_SetBits(GPIO_CS608_PORT,GPIO_PIN_CS_A2);
#define ADG608_A2_Disable 			GPIO_ResetBits(GPIO_CS608_PORT,GPIO_PIN_CS_A2);


#define RCC_GPIO_EN				RCC_AHB1Periph_GPIOG
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_EN_EN  			GPIO_Pin_8
#define GPIO_EN_PORT				GPIOG

#define ADG608_EN_Enable 			GPIO_SetBits(GPIO_EN_PORT,GPIO_PIN_EN_EN);
#define ADG608_EN_Disable 			GPIO_ResetBits(GPIO_EN_PORT,GPIO_PIN_EN_EN);







void InitADG608(void);
void SetADG608(u8 a0,u8 a1,u8 a2);

#endif
