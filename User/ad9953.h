#ifndef _AD5593_
#define _AD5593_




#define RCC_GPIO_CS				RCC_AHB1Periph_GPIOC
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS_DDS1			GPIO_Pin_1
#define GPIO_PIN_CS_DDS2			GPIO_Pin_13
#define GPIO_PIN_RESDDS 			GPIO_Pin_15
#define GPIO_CS_PORT				GPIOC

#define AD9953_DDS1_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_DDS1);
#define AD9953_DDS1_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_DDS1);

#define AD9953_DDS2_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_DDS2);
#define AD9953_DDS2_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_DDS2);


#define AD9953_RESET_RES    			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_RESDDS);
#define AD9953_SET_RES       			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_RESDDS);




#define RCC_GPIO_SYNC				RCC_AHB1Periph_GPIOA
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_SYNC_SYNC1			GPIO_Pin_2
#define GPIO_PIN_SYNC_SYNC2			GPIO_Pin_0

#define GPIO_SYNC_PORT				GPIOA

#define AD9953_SYNC1_Enable 			GPIO_SetBits(GPIO_SYNC_PORT,GPIO_PIN_SYNC_SYNC1);
#define AD9953_SYNC1_Disable 			GPIO_ResetBits(GPIO_SYNC_PORT,GPIO_PIN_SYNC_SYNC1);

#define AD9953_SYNC2_Enable 			GPIO_SetBits(GPIO_SYNC_PORT,GPIO_PIN_SYNC_SYNC2);
#define AD9953_SYNC2_Disable 			GPIO_ResetBits(GPIO_SYNC_PORT,GPIO_PIN_SYNC_SYNC2);




void InitAD9953(void);
void SetParamAD9953(u32 freq, u8 ch);







#endif
