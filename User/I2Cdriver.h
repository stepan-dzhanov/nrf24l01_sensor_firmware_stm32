#ifndef _MYI2C_DRIVER_H_
#define _MYI2C_DRIVER_H_	
	#include <stdint.h>
	#include "I2CdriverTypes.h"
	//---------------------------------------------------------------------------
	void MYI2C_Init(void);
	Type_MyI2cOpStatus MYI2C_PageRead16BitAddr(uint8_t slaveAddr,uint8_t* pBuffer,uint16_t readAddr,uint16_t numByteToRead);
	Type_MyI2cOpStatus MYI2C_PageWrite16BitAddr(uint8_t slaveAddr,uint8_t* pBuffer,uint16_t writeAddr,uint16_t numByteToWrite);
	Type_MyI2cOpStatus MYI2C_PageRead8BitAddr(uint8_t slaveAddr,uint8_t* pBuffer,uint8_t readAddr,uint8_t numByteToRead);
	Type_MyI2cOpStatus MYI2C_PageWrite8BitAddr(uint8_t slaveAddr,uint8_t* pBuffer,uint8_t writeAddr,uint8_t numByteToWrite);
	Type_MyI2cOpStatus MYI2C_WaitEepromStandbyState(uint8_t slaveAddr);
#endif//_I2C_DRIVER_H_
