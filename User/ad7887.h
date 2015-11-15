#ifndef _AD7887
#define _AD7887

#define IM 0
#define RE 1

#define RCC_GPIO_CS				RCC_AHB1Periph_GPIOC
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_CS_IM				GPIO_Pin_4
#define GPIO_PIN_CS_RE				GPIO_Pin_5
#define GPIO_CS_PORT				GPIOC

#define AD7887_IM_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_IM);
#define AD7887_IM_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_IM);
#define AD7887_RE_Enable 			GPIO_ResetBits(GPIO_CS_PORT,GPIO_PIN_CS_RE);
#define AD7887_RE_Disable 			GPIO_SetBits(GPIO_CS_PORT,GPIO_PIN_CS_RE);

#define AD7887_STATUS_WORD                      0x21

void AD7887Init();
u16 AD7887GetData(u8 ch) ;
  

  






#endif
