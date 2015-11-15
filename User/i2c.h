#ifndef _I2C_
#define _I2C_

#include "stm32f4xx.h"

/* Private define ------------------------------------------------------------*/
#define I2C_PAGESIZE	4


/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define I2C_x_FLAG_TIMEOUT         				10000


#define I2Cx_SPEED               					30000
#define I2Cx_SLAVE_ADDRESS7      					0x33

//#ifdef 
	#define I2C_x                        	I2C1
	#define I2C_x_CLK                    	RCC_APB1Periph_I2C1
	
	#define I2C_x_SDA_PIN                 	GPIO_Pin_9
	#define I2C_x_SDA_GPIO_PORT           	GPIOB
	#define I2C_x_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define I2C_x_SDA_SOURCE              	GPIO_PinSource9
	#define I2C_x_SDA_AF                  	GPIO_AF_I2C1
	
	#define I2C_x_SCL_PIN                 	GPIO_Pin_8
	#define I2C_x_SCL_GPIO_PORT           	GPIOB
	#define I2C_x_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define I2C_x_SCL_SOURCE              	GPIO_PinSource8
	#define I2C_x_SCL_AF                  	GPIO_AF_I2C1
//#endif

/* Private function prototypes -----------------------------------------------*/
void I2C_Configuration(void);
uint8_t I2C_Write(uint8_t DEVICE_WRITE_ADDRESS, uint8_t length, uint8_t *Data);
uint8_t I2C_Read(uint8_t DEVICE_WRITE_ADDRESS, uint8_t RegAddr, uint8_t *Data);
uint8_t I2C_Read_Buf(uint8_t DEVICE_WRITE_ADDRESS, uint8_t RegAddr, uint8_t len, uint8_t *Data);

#endif