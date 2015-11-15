#ifndef _LEDS_
#define _LEDS_


#define RCC_GPIO_LED				RCC_AHB1Periph_GPIOC
#define RCC_AHBxPeriphClockCmd		        RCC_AHB1PeriphClockCmd
#define GPIO_PIN_LPWM			        GPIO_Pin_5
#define GPIO_PIN_L1			        GPIO_Pin_7
#define GPIO_PIN_L2			        GPIO_Pin_6
#define GPIO_PIN_RPWM			        GPIO_Pin_11
#define GPIO_PIN_R2			        GPIO_Pin_9
#define GPIO_PIN_R1			        GPIO_Pin_8
#define GPIO_LED_PORT				GPIOC

#define LPWM_Enable 			        GPIO_SetBits(GPIO_LED_PORT,GPIO_PIN_LPWM);
#define LPWM_Disable 			        GPIO_ResetBits(GPIO_LED_PORT,GPIO_PIN_LPWM);

#define RPWM_Enable 			        GPIO_SetBits(GPIO_LED_PORT,GPIO_PIN_RPWM);
#define RPWM_Disable 			        GPIO_ResetBits(GPIO_LED_PORT,GPIO_PIN_RPWM);

#define L1_Enable 			        GPIO_SetBits(GPIO_LED_PORT,GPIO_PIN_L1);
#define L1_Disable 			        GPIO_ResetBits(GPIO_LED_PORT,GPIO_PIN_L1);

#define L2_Enable 			        GPIO_SetBits(GPIO_LED_PORT,GPIO_PIN_L2);
#define L2_Disable 			        GPIO_ResetBits(GPIO_LED_PORT,GPIO_PIN_L2);

#define R1_Enable 			        GPIO_SetBits(GPIO_LED_PORT,GPIO_PIN_R1);
#define R1_Disable 			        GPIO_ResetBits(GPIO_LED_PORT,GPIO_PIN_R1);

#define R2_Enable 			        GPIO_SetBits(GPIO_LED_PORT,GPIO_PIN_R2);
#define R2_Disable 			        GPIO_ResetBits(GPIO_LED_PORT,GPIO_PIN_R2);




void InitLeds(void);
void Reverse();
void Cir();
void Forward();


#endif