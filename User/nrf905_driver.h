
#ifndef _NRF905_DRIVER_H_
#define _NRF905_DRIVER_H_

#define NRF905_SPI				SPI2
#define NRF905_SPI_PINS		        	TM_SPI_PinsPack_2




#define NRF905_CSN_PORT			        GPIOE
#define NRF905_CSN_PIN			        GPIO_PIN_11


#define NRF905_CE_PORT		        	GPIOE
#define NRF905_CE_PIN				GPIO_PIN_12

#define NRF905_PWRUP_PORT		        GPIOE
#define NRF905_PWRUP_PIN			GPIO_PIN_13

#define NRF905_TXEN_PORT		        GPIOE
#define NRF905_TXEN_PIN			        GPIO_PIN_14

#define NRF905_DR_PORT		                GPIOE
#define NRF905_DR_PIN			        GPIO_PIN_15




/* Pins configuration */

#define NRF905_TXEN_LOW			        TM_GPIO_SetPinLow(NRF905_TXEN_PORT,NRF905_TXEN_PIN)
#define NRF905_TXEN_HIGH			TM_GPIO_SetPinHigh(NRF905_TXEN_PORT,NRF905_TXEN_PIN)
#define NRF905_PWRUP_LOW			TM_GPIO_SetPinLow(NRF905_PWRUP_PORT,NRF905_PWRUP_PIN)
#define NRF905_PWRUP_HIGH			TM_GPIO_SetPinHigh(NRF905_PWRUP_PORT,NRF905_PWRUP_PIN)
#define NRF905_CE_LOW				TM_GPIO_SetPinLow(NRF905_CE_PORT,NRF905_CE_PIN)
#define NRF905_CE_HIGH			        TM_GPIO_SetPinHigh(NRF905_CE_PORT,NRF905_CE_PIN)
#define NRF905_CSN_LOW			        TM_GPIO_SetPinLow(NRF905_CSN_PORT,NRF905_CSN_PIN)
#define NRF905_CSN_HIGH			        TM_GPIO_SetPinHigh(NRF905_CSN_PORT,NRF905_CSN_PIN)






void Nrf905Init(void);
void PowerDownMode(void);
void PowerUpMode(void);
void TransmitMode(void);
void ReceiveMode(void);
void TransmitPacket(unsigned short dByte);
unsigned short ReceivePacket(void);
void Nrf905RegCom (unsigned short RegCom, unsigned short RegValue);

#endif