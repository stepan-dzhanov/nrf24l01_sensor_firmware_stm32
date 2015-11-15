#ifndef _SCA3000_
#define _SCA3000_

#define RCC_GPIO_SCA				RCC_AHB1Periph_GPIOB
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_SCA_CS			        GPIO_Pin_11
#define GPIO_PIN_SCA_RES		        GPIO_Pin_12
#define GPIO_SCA_PORT				GPIOB

#define SCA_CS_Enable 			        GPIO_SetBits(GPIO_SCA_PORT,GPIO_PIN_SCA_CS);
#define SCA_CS_Disable 			        GPIO_ResetBits(GPIO_SCA_PORT,GPIO_PIN_SCA_CS);

#define SCA_RES_Enable 			        GPIO_SetBits(GPIO_SCA_PORT,GPIO_PIN_SCA_RES);
#define SCA_RES_Disable 			GPIO_ResetBits(GPIO_SCA_PORT,GPIO_PIN_SCA_RES);


void InitSCA3000();
s16 SCA3000_Read(s16 *x,s16 *y, s16 *z);

#endif
