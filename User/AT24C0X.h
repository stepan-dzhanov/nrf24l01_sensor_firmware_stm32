#ifndef _AT24C0X_H_
#define _AT24C0X_H_	
	#include <stdint.h>
	#include "I2CdriverTypes.h"
	//---------------------------------------------------------------------------
	#pragma pack(push,1)
	typedef struct{
		void (*I2cInit)(void);
		Type_MyI2cOpStatus (*PageRead)(uint8_t slaveAddr,uint8_t* pBuffer,uint16_t readAddr,uint16_t numByteToRead);
		Type_MyI2cOpStatus (*PageWrite)(uint8_t slaveAddr,uint8_t* pBuffer,uint16_t writeAddr,uint16_t numByteToWrite);
		Type_MyI2cOpStatus (*WaitEepromStandbyState)(uint8_t slaveAddr);
	}Type_AT24C0X_Init;		
	#pragma pack(pop)
	//---------------------------------------------------------------------------
	void AT24C0X_Init(Type_AT24C0X_Init *s);
	Type_MyI2cOpStatus AT24C0X_BufferWrite(uint8_t* pBuffer, uint16_t writeAddr, u16 NumByteToWrite);
	Type_MyI2cOpStatus AT24C0X_BufferRead(uint8_t* pBuffer, uint16_t readAddr, u16 NumByteToRead);	
	Type_MyI2cOpStatus AT24C0X_Erase(void);
	Type_MyI2cOpStatus AT24C0X_TestI2c(void);
#endif//_AT24C0X_H_
