	//#include "Main.h" 
	#include "I2Cdriver.h"
//-----------------------------------------------------------------------------
	//\\#define _MYI2C_I2C_DBG_
	//I2C constants
		#define I2C_NAME									I2C2
		#define MYI2C_I2C_GPIO_CLOCK()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
		#define MYI2C_I2C_PINPORT					GPIOF		
		#define MYI2C_SCL_PINNUM					1
		#define MYI2C_SDA_PINNUM					0
		#define MYI2C_I2C_CLOCK()					RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
		#define I2C_SPEED               	200000UL
	//CS
		#define MYI2C_DelayClocks(c)			DelayUs(((c)*1000000UL)/I2C_SPEED)
	//-----------------------------------------------------------------------------------------------------------------		
		typedef enum{
			WAIT_TIMEOUT,WAIT_NO_TIMEOUT
		}Type_WaitForEventStatus;
		typedef enum{
			GPIOSTORE_STORE,GPIOSTORE_RESTORE
		}Type_GpioCfgStoreOp;	
//-----------------------------------------------------------------------------
	void MYI2C_GpioConfig(void);
	void MYI2C_I2cConfig(void);
	void MYI2C_I2cReset(void);
	Type_MyI2cOpStatus MYI2C_TestI2c(void);
	Type_MyI2cOpStatus MYI2C_ByteWrite(uint8_t slaveAddr,uint8_t byte, uint16_t writeAddr);
	Type_MyI2cOpStatus MYI2C_Test(void);
//-----------------------------------------------------------------------------
static Type_WaitForEventStatus I2cWaitForEventWithTimeout(uint32_t event,uint16_t i2cClocks){
	uint32_t n = (i2cClocks*CORE_CLK)/(I2C_SPEED*3);
	while(I2C_CheckEvent(I2C_NAME,event)==ERROR)
		if(!n--)return WAIT_TIMEOUT;
	return WAIT_NO_TIMEOUT;
}
void GPIO_StoreConfig(GPIO_TypeDef* GPIOx,Type_GpioCfgStoreOp store){
	static GPIO_TypeDef gpioTemp;
	if(store==GPIOSTORE_STORE){
		gpioTemp.MODER = GPIOx->MODER;
		gpioTemp.OTYPER = GPIOx->OTYPER; 
		gpioTemp.AFR[0] = GPIOx->AFR[0];
		gpioTemp.AFR[1] = GPIOx->AFR[1];
	}
		else{
			GPIOx->MODER = gpioTemp.MODER;
			GPIOx->OTYPER = gpioTemp.OTYPER; 
			GPIOx->AFR[0] = gpioTemp.AFR[0];
			GPIOx->AFR[1] = gpioTemp.AFR[1];
		}
}
void MYI2C_GpioConfig(void){
  GPIO_InitTypeDef  GPIO_InitStructure; 
	MYI2C_I2C_GPIO_CLOCK();
  /* Configure I2C1 pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Pin = (1<<MYI2C_SDA_PINNUM) | (1<<MYI2C_SCL_PINNUM);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(MYI2C_I2C_PINPORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(MYI2C_I2C_PINPORT,MYI2C_SCL_PINNUM,GPIO_AF_I2C2);
	GPIO_PinAFConfig(MYI2C_I2C_PINPORT,MYI2C_SDA_PINNUM,GPIO_AF_I2C2);
}
void MYI2C_I2cConfig(void){
  I2C_InitTypeDef  I2C_InitStructure;
  // 
	MYI2C_I2C_CLOCK();
  I2C_SoftwareResetCmd(I2C_NAME, ENABLE);
  I2C_SoftwareResetCmd(I2C_NAME, DISABLE);
  /* I2C configuration */	
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;//I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0;//slaveAddr;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;   
  /* Apply I2C configuration after enabling it */
  I2C_Init(I2C_NAME, &I2C_InitStructure);
  /* I2C Peripheral Enable */
  I2C_Cmd(I2C_NAME, ENABLE);
}

void MYI2C_TargetReset(void){	
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint8_t i;
	//
	GPIO_StoreConfig(MYI2C_I2C_PINPORT,GPIOSTORE_STORE);
		// Configure I2C1 pins: SCL and SDA
		GPIO_InitStructure.GPIO_Pin = (1<<MYI2C_SDA_PINNUM) | (1<<MYI2C_SCL_PINNUM);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(MYI2C_I2C_PINPORT, &GPIO_InitStructure);
		//
		MYI2C_I2C_PINPORT->ODR = 1<<MYI2C_SDA_PINNUM;
		MYI2C_I2C_PINPORT->ODR = 1<<MYI2C_SCL_PINNUM;
		MYI2C_DelayClocks(1);
		for(i=0;i<10;i++)
		{
			MYI2C_I2C_PINPORT->ODR = 1<<MYI2C_SCL_PINNUM;
			MYI2C_DelayClocks(1);
			MYI2C_I2C_PINPORT->ODR = ~(1<<MYI2C_SCL_PINNUM);
			MYI2C_DelayClocks(1);				
		}
		//
		MYI2C_I2C_PINPORT->ODR = ~(1<<MYI2C_SDA_PINNUM);
		MYI2C_DelayClocks(1);
		MYI2C_I2C_PINPORT->ODR = 1<<MYI2C_SDA_PINNUM;	
	GPIO_StoreConfig(MYI2C_I2C_PINPORT,GPIOSTORE_RESTORE);			
}
Type_WaitForEventStatus WaitWhileBusy(uint16_t i2cClocks){
	uint32_t n = (i2cClocks*CORE_CLK)/(I2C_SPEED*3);
	while(I2C_CheckEvent(I2C_NAME,I2C_FLAG_BUSY)==SUCCESS)
		if(!n--)break;
	if(!n){
		MYI2C_TargetReset();
		//\\if(I2C_CheckEvent(I2C_NAME,I2C_FLAG_BUSY))
		return WAIT_NO_TIMEOUT;
	}
	return WAIT_NO_TIMEOUT;
}
//---------------------------------------------------------------------------------------------------------
void MYI2C_Init(void){
	MYI2C_GpioConfig();
	MYI2C_TargetReset();
	MYI2C_I2cConfig();
	//\\I2C_DigitalFilterConfig(I2C_NAME,10/*This parameter can be a number between 0x00 and 0x0F*/);
	//\\I2C_AnalogFilterCmd(I2C_NAME,ENABLE);
	#ifdef _MYI2C_I2C_DBG_
		Type_MyI2cOpStatus status;
		while(1)
			status = MYI2C_Test();
	#endif//_MYI2C_I2C_DBG_
}
Type_MyI2cOpStatus MYI2C_ByteWrite16BitAddr(uint8_t slaveAddr,uint8_t byte, uint16_t writeAddr){
	//*******************************************************************************
	//* Function Name  : MYI2C_ByteWrite
	//* Description    : Writes one byte to the I2C EEPROM.
	//* Input          : - pBuffer : pointer to the buffer  containing the data to be 
	//*                    written to the EEPROM.
	//*                  - writeAddr : EEPROM's internal address to write to.
	//* Output         : None
	//* Return         : None
	//*******************************************************************************
	IrqPush();
		//While the bus is busy
			if(WaitWhileBusy(1000)==WAIT_TIMEOUT)
				return MYI2C_TIMEOUT;
		//Send STRAT condition 
			I2C_GenerateSTART(I2C_NAME, ENABLE);
		//Test on EV5 and clear it  
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))/* BUSY, MSL and SB flag */
				return MYI2C_TIMEOUT;
		//Enable Acknowledgement
			I2C_AcknowledgeConfig(I2C_NAME, ENABLE);
		//Send EEPROM address for write 
			I2C_Send7bitAddress(I2C_NAME,slaveAddr,I2C_Direction_Transmitter);	
		//Test on EV6 and clear it 
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED,1000))/* BUSY, MSL, ADDR, TXE and TRA flags */
				return MYI2C_TIMEOUT;	
		//Send the EEPROM's internal address to write to
			I2C_SendData(I2C_NAME, (uint8_t)(writeAddr>>8));	
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))
				return MYI2C_TIMEOUT;
			I2C_SendData(I2C_NAME, (uint8_t)writeAddr);
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))	
				return MYI2C_TIMEOUT;
		//Send the byte to be written
			I2C_SendData(I2C_NAME,byte); 	
		//Test on EV8 and clear it
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))
				return MYI2C_TIMEOUT;		
		//Send STOP condition 
		I2C_GenerateSTOP(I2C_NAME, ENABLE);
	IrqPop();
	return MYI2C_SUCCSESS_READ_WRITE;
}
Type_MyI2cOpStatus MYI2C_PageWrite16BitAddr(uint8_t slaveAddr,uint8_t* pBuffer, uint16_t writeAddr, uint16_t numByteToWrite){
/*******************************************************************************
* Function Name  : MYI2C_PageWrite
* Description    : Writes more than one byte to the EEPROM with a single WRITE
*                  cycle. The number of byte can't exceed the EEPROM page size.
* Input          : - pBuffer : pointer to the buffer containing the data to be 
*                    written to the EEPROM.
*                  - writeAddr : EEPROM's internal address to write to.
*                  - numByteToWrite : number of bytes to write to the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
	IrqPush();
		//While the bus is busy
			if(WaitWhileBusy(1000)==WAIT_TIMEOUT)
				return MYI2C_TIMEOUT;
		//Send STRAT condition 
			I2C_GenerateSTART(I2C_NAME, ENABLE);
		//Test on EV5 and clear it  
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))/* BUSY, MSL and SB flag */
				return MYI2C_TIMEOUT;
		//Enable Acknowledgement
			I2C_AcknowledgeConfig(I2C_NAME, ENABLE);
		//Send EEPROM address for write 
			I2C_Send7bitAddress(I2C_NAME,slaveAddr,I2C_Direction_Transmitter);	
		//Test on EV6 and clear it 
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED,1000))/* BUSY, MSL, ADDR, TXE and TRA flags */
				return MYI2C_TIMEOUT;	
		//Send the EEPROM's internal address to write to
			I2C_SendData(I2C_NAME, (uint8_t)(writeAddr>>8));	
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))
				return MYI2C_TIMEOUT;
			I2C_SendData(I2C_NAME, (uint8_t)writeAddr);
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))	
				return MYI2C_TIMEOUT;
		//While there is data to be written
			while(numByteToWrite-->0){
				//Send the current byte 
					I2C_SendData(I2C_NAME, *pBuffer); 
				//Point to the next byte to be written 
					pBuffer++;   
				//Test on EV8 and clear it
					while (!I2C_CheckEvent(I2C_NAME, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
			}
		//Send STOP condition
			I2C_GenerateSTOP(I2C_NAME, ENABLE);
	IrqPop();
	return MYI2C_SUCCSESS_READ_WRITE;
}
Type_MyI2cOpStatus MYI2C_PageRead16BitAddr(uint8_t slaveAddr,uint8_t* pBuffer,uint16_t readAddr,uint16_t numByteToRead){
	/*******************************************************************************
	* Function Name  : MYI2C_BufferRead
	* Description    : Reads a block of data from the EEPROM.
	* Input          : - pBuffer : pointer to the buffer that receives the data read 
	*                    from the EEPROM.
	*                  - ReadAddr : EEPROM's internal address to read from.
	*                  - NumByteToRead : number of bytes to read from the EEPROM.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	IrqPush();
		//Write	address
			//While the bus is busy
				if(WaitWhileBusy(100)==WAIT_TIMEOUT)
					return MYI2C_TIMEOUT;
			//Send START condition
				I2C_GenerateSTART(I2C_NAME, ENABLE);
			//Test on EV5 and clear it
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))
					return MYI2C_TIMEOUT;															
			//Enable Acknowledgement
				I2C_AcknowledgeConfig(I2C_NAME, ENABLE);
			//Send EEPROM address for write 
				I2C_Send7bitAddress(I2C_NAME,slaveAddr,I2C_Direction_Transmitter);
			//Test on EV6 and clear it 
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED,1000))
					return MYI2C_TIMEOUT;
			//Clear EV6 by setting again the PE bit
				I2C_Cmd(I2C_NAME, ENABLE);
			//Send the EEPROM's internal address to write to
				I2C_SendData(I2C_NAME, (uint8_t)(readAddr>>8));	
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))
					return MYI2C_TIMEOUT;
				I2C_SendData(I2C_NAME, (uint8_t)readAddr);
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))	
					return MYI2C_TIMEOUT;
		//Sequential read
			//Send STRAT condition a second time 
			I2C_GenerateSTART(I2C_NAME, ENABLE);  
			//Test on EV5 and clear it
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))
				return MYI2C_TIMEOUT;
			//Send EEPROM address for read 
			I2C_Send7bitAddress(I2C_NAME,slaveAddr, I2C_Direction_Receiver); 
			//Test on EV6 and clear it 
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED,1000))
				return MYI2C_TIMEOUT;
			//While there is data to be read 
			while(numByteToRead){
				if(numByteToRead == 1){
					//Disable Acknowledgement 
					I2C_AcknowledgeConfig(I2C_NAME, DISABLE);			  
					/*//Send STOP Condition 
					I2C_GenerateSTOP(I2C_NAME, ENABLE);*/
				}
				//Test on EV7 and clear it
				if(I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_RECEIVED,1000)){  
					//Read a byte from the EEPROM 
					*pBuffer = I2C_ReceiveData(I2C_NAME);			
					//Point to the next location where the byte read will be saved
					pBuffer++; 			  
					//Decrement the read bytes counter
					numByteToRead--;      
				}
					else return MYI2C_TIMEOUT;
				/*if(numByteToRead == 0){  
					//Send STOP Condition 
					I2C_GenerateSTOP(I2C_NAME, ENABLE);
				}*/
			}		
			I2C_GenerateSTOP(I2C_NAME, ENABLE);
		/*//Enable Acknowledgement to be ready for another reception 
		I2C_AcknowledgeConfig(I2C_NAME, ENABLE);*/
	IrqPop();
	return MYI2C_SUCCSESS_READ_WRITE;
}
Type_MyI2cOpStatus MYI2C_PageWrite8BitAddr(uint8_t slaveAddr,uint8_t* pBuffer, uint8_t writeAddr, uint8_t numByteToWrite){
/*******************************************************************************
* Function Name  : MYI2C_PageWrite
* Description    : Writes more than one byte to the EEPROM with a single WRITE
*                  cycle. The number of byte can't exceed the EEPROM page size.
* Input          : - pBuffer : pointer to the buffer containing the data to be 
*                    written to the EEPROM.
*                  - writeAddr : EEPROM's internal address to write to.
*                  - numByteToWrite : number of bytes to write to the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
	IrqPush();
		//While the bus is busy
			if(WaitWhileBusy(1000)==WAIT_TIMEOUT)
				return MYI2C_TIMEOUT;
		//Send STRAT condition 
			I2C_GenerateSTART(I2C_NAME, ENABLE);
		//Test on EV5 and clear it  
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))/* BUSY, MSL and SB flag */
				return MYI2C_TIMEOUT;
		//Enable Acknowledgement
			I2C_AcknowledgeConfig(I2C_NAME, ENABLE);
		//Send EEPROM address for write 
			I2C_Send7bitAddress(I2C_NAME,slaveAddr,I2C_Direction_Transmitter);	
		//Test on EV6 and clear it 
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED,1000))/* BUSY, MSL, ADDR, TXE and TRA flags */
				return MYI2C_TIMEOUT;	
		//Send the EEPROM's internal address to write to
			I2C_SendData(I2C_NAME, (uint8_t)writeAddr);
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))	
				return MYI2C_TIMEOUT;
		//While there is data to be written
			while(numByteToWrite-->0){
				//Send the current byte 
					I2C_SendData(I2C_NAME, *pBuffer); 
				//Point to the next byte to be written 
					pBuffer++;   
				//Test on EV8 and clear it
					while (!I2C_CheckEvent(I2C_NAME, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
			}
		//Send STOP condition
			I2C_GenerateSTOP(I2C_NAME, ENABLE);
	IrqPop();
	return MYI2C_SUCCSESS_READ_WRITE;
}
Type_MyI2cOpStatus MYI2C_PageRead8BitAddr(uint8_t slaveAddr,uint8_t* pBuffer,uint8_t readAddr,uint8_t numByteToRead){
	/*******************************************************************************
	* Function Name  : MYI2C_BufferRead
	* Description    : Reads a block of data from the EEPROM.
	* Input          : - pBuffer : pointer to the buffer that receives the data read 
	*                    from the EEPROM.
	*                  - ReadAddr : EEPROM's internal address to read from.
	*                  - NumByteToRead : number of bytes to read from the EEPROM.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	IrqPush();
		//Write	address
			//While the bus is busy
				if(WaitWhileBusy(100)==WAIT_TIMEOUT)
					return MYI2C_TIMEOUT;
			//Send START condition
				I2C_GenerateSTART(I2C_NAME, ENABLE);
			//Test on EV5 and clear it
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))
					return MYI2C_TIMEOUT;															
			//Enable Acknowledgement
				I2C_AcknowledgeConfig(I2C_NAME, ENABLE);
			//Send EEPROM address for write 
				I2C_Send7bitAddress(I2C_NAME,slaveAddr,I2C_Direction_Transmitter);
			//Test on EV6 and clear it 
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED,1000))
					return MYI2C_TIMEOUT;
			//Clear EV6 by setting again the PE bit
				I2C_Cmd(I2C_NAME, ENABLE);
			//Send the EEPROM's internal address to write to
				I2C_SendData(I2C_NAME, (uint8_t)readAddr);
				if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_TRANSMITTED,1000))	
					return MYI2C_TIMEOUT;
		//Sequential read
			//Send STRAT condition a second time 
			I2C_GenerateSTART(I2C_NAME, ENABLE);  
			//Test on EV5 and clear it
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_MODE_SELECT,1000))
				return MYI2C_TIMEOUT;
			//Send EEPROM address for read 
			I2C_Send7bitAddress(I2C_NAME,slaveAddr, I2C_Direction_Receiver); 
			//Test on EV6 and clear it 
			if(!I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED,1000))
				return MYI2C_TIMEOUT;
			//While there is data to be read 
			while(numByteToRead){
				if(numByteToRead == 1){
					//Disable Acknowledgement 
					I2C_AcknowledgeConfig(I2C_NAME, DISABLE);			  
					/*//Send STOP Condition 
					I2C_GenerateSTOP(I2C_NAME, ENABLE);*/
				}
				//Test on EV7 and clear it
				if(I2cWaitForEventWithTimeout(I2C_EVENT_MASTER_BYTE_RECEIVED,1000)){  
					//Read a byte from the EEPROM 
					*pBuffer = I2C_ReceiveData(I2C_NAME);			
					//Point to the next location where the byte read will be saved
					pBuffer++; 			  
					//Decrement the read bytes counter
					numByteToRead--;      
				}
					else return MYI2C_TIMEOUT;
				/*if(numByteToRead == 0){  
					//Send STOP Condition 
					I2C_GenerateSTOP(I2C_NAME, ENABLE);
				}*/
			}		
			I2C_GenerateSTOP(I2C_NAME, ENABLE);
		/*//Enable Acknowledgement to be ready for another reception 
		I2C_AcknowledgeConfig(I2C_NAME, ENABLE);*/
	IrqPop();
	return MYI2C_SUCCSESS_READ_WRITE;
}
Type_MyI2cOpStatus MYI2C_WaitEepromStandbyState(uint8_t slaveAddr){
/*******************************************************************************
* Function Name  : AT24C0X_WaitEepromStandbyState
* Description    : Wait for EEPROM Standby state
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
	Type_MyI2cOpStatus  st = MYI2C_SUCCSESS_READ_WRITE;
	volatile uint16_t SR1_Tmp = 0;
	uint32_t n = (10000LL/**/*CORE_CLK)/(I2C_SPEED*3);
	//
	do{
		/* Send START condition */
		I2C_GenerateSTART(I2C_NAME, ENABLE);
		/* Read I2C1 SR1 register */
		SR1_Tmp = I2C_ReadRegister(I2C_NAME, I2C_Register_SR1);
		/* Send EEPROM address for write */
		I2C_Send7bitAddress(I2C_NAME,slaveAddr,I2C_Direction_Transmitter);
		if(n--==0){
			st = MYI2C_TIMEOUT;
			break;
		}
	}
		while(!(I2C_ReadRegister(I2C_NAME, I2C_Register_SR1) & 0x0002));
  
	/* Clear AF flag */
	I2C_ClearFlag(I2C_NAME, I2C_FLAG_AF);
	
	/* STOP condition */    
	I2C_GenerateSTOP(I2C_NAME, ENABLE); 
	return st;	
}
//---------------------------------------------------------------------------------------------------------
Type_MyI2cOpStatus  MYI2C_Test(void){
	Type_MyI2cOpStatus  st;
	uint8_t m[8];
	for(int i=0;i<sizeof(m)/sizeof(m[0]);i++)
		m[i] = i;
	#define AT24C0X_A0_A2			0x00/*0 if A0,A1,A2 connected hardware to GND*/
	#define AT24C0X_CS				(0xA0|((AT24C0X_A0_A2&0x07)<<1))
	st = MYI2C_PageWrite8BitAddr(AT24C0X_CS,m,0,8);
	for(int i=0;i<sizeof(m)/sizeof(m[0]);i++)
		m[i] = 0;
	st = MYI2C_PageRead8BitAddr(AT24C0X_CS,m,0,8);
	return st;
}
