#ifndef _AD7192_
#define _AD7192_



#define RCC_GPIO_CS_CARDIO				RCC_AHB1Periph_GPIOC
#define RCC_AHBxPeriphClockCmd		                RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS_CARDIO			        GPIO_Pin_14
#define GPIO_CS_PORT				        GPIOC

#define AD7192_Enable 			                GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_CARDIO);
#define AD7192_Disable 			                GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_CARDIO);


void InitAD7192(void);
void SetParamAD7192(u32 data, u8 comm);
u32 ReadDataAD7192( u8 comm);

#endif