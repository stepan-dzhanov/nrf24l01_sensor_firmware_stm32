	#include "Main.h" 
	#include "AT24C0X.h"
	//\\#include "I2Cdriver.h"
//-----------------------------------------------------------------------------
	//DBG
		//\\#define _AT24C0X_I2C_DBG_
	//Device
		//\\#define AT24C01
		//\\#define AT24C02
		//\\#define AT24C04
		//\\#define AT24C08
		//\\#define AT24C16
		#define AT24C512
	//-----------------------------------------------------------------------------------------------------------------
	//CS
		#define AT24C0X_A0_A2							0x00/*0 if A0,A1,A2 connected hardware to GND*/
		#define AT24C0X_CS								(0xA0|((AT24C0X_A0_A2&0x07)<<1))
	//Device selector
		#ifdef AT24C01
			#define AT24C0X_PAGE_SIZE       8
			#define AT24C0X_PAGE_Q					16
			#define AT24C0X_MAX_DATA_ADDR		127
		#endif
		#ifdef AT24C02
			#define AT24C0X_PAGE_SIZE       8
			#define AT24C0X_PAGE_Q					32
			#define AT24C0X_MAX_ADDR				255
		#endif
		#ifdef AT24C04
			#define AT24C0X_PAGE_SIZE       16
			#define AT24C0X_PAGE_Q					32
			#define AT24C0X_MAX_ADDR				511
		#endif
		#ifdef AT24C08
			#define AT24C0X_PAGE_SIZE       16
			#define AT24C0X_PAGE_Q					64
			#define AT24C0X_MAX_ADDR				1023
		#endif
		#ifdef AT24C16
			#define AT24C0X_PAGE_SIZE       16
			#define AT24C0X_PAGE_Q					128
			#define AT24C0X_MAX_ADDR				2047
		#endif
		#ifdef AT24C512
			#define AT24C0X_PAGE_SIZE       128
			#define AT24C0X_PAGE_Q					512
			#define AT24C0X_MAX_ADDR				65535
		#endif
		#define AT24C0X_DelayClocks(c)		DelayUs(((c)*1000000UL)/I2C_SPEED)
//Private variables------------------------------------------------------------
static Type_AT24C0X_Init sI2CInterface = {0,0,0};
//Debug functions--------------------------------------------------------------
static uint8_t AT24C0X_Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2,
	uint16_t BufferLength){
	uint8_t isEquel = 1;
  while(BufferLength--){
		if(*pBuffer1 != *pBuffer2){
			isEquel = 0;
    }    
    pBuffer1++;
    pBuffer2++;
  }
  return isEquel;  
}
Type_MyI2cOpStatus AT24C0X_TestI2c(void){
  Type_MyI2cOpStatus status;	
	const uint8_t len =38;
	uint8_t Tx1_Buffer[len] = "ghytrscbhjkll;8795695udfuye685exgdljyt";
	uint8_t Rx1_Buffer[len]; 
	//	
	for(int32_t addr=0;addr<AT24C0X_MAX_ADDR;addr+=len){
		//First write in the memory followed by a read of the written data
		//Write on I2C EEPROM from EEPROM_WriteAddress1
			status = AT24C0X_BufferWrite(Tx1_Buffer,addr,len); 
		//Read from I2C EEPROM from EEPROM_ReadAddress1
			status = AT24C0X_BufferRead(Rx1_Buffer,addr,len); 
		//Check if the data written to the memory is read correctly
			if(AT24C0X_Buffercmp(Tx1_Buffer, Rx1_Buffer,len)==0){
				status = MYI2C_STATUS_ERROR;
				break;
			}
				else status = MYI2C_SUCCSESS_READ_WRITE;
	}
	return status;
}
void AT24C0X_Init(Type_AT24C0X_Init *s){
	if(*(uint32_t*)(s->I2cInit)==0 || 
		*(uint32_t*)(s->PageRead)==0 || 
		*(uint32_t*)(s->PageWrite)==0 || 
		*(uint32_t*)(s->WaitEepromStandbyState)==0){
		while(1);
	}
	sI2CInterface = *s;
	sI2CInterface.I2cInit();
	int32_t n = 100000; 
	/*while(n-->0){
		AT24C0X_TestI2c();
		DelayMs(10);
	}*/
}
//---------------------------------------------------------------------------------------------------------
//Write functions******************************************************************************************
//---------------------------------------------------------------------------------------------------------
Type_MyI2cOpStatus AT24C0X_BufferWrite(uint8_t* pBuffer, uint16_t writeAddr, uint16_t numByteToWrite){
	/*******************************************************************************
	* Function Name  : AT24C0X_BufferWrite
	* Description    : Writes buffer of data to the I2C EEPROM.
	* Input          : - pBuffer : pointer to the buffer  containing the data to be 
	*                    written to the EEPROM.
	*                  - writeAddr : EEPROM's internal address to write to.
	*                  - numByteToWrite : number of bytes to write to the EEPROM.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	Type_MyI2cOpStatus status = MYI2C_SUCCSESS_READ_WRITE;
	uint8_t addr = writeAddr % AT24C0X_PAGE_SIZE;
	uint8_t count = AT24C0X_PAGE_SIZE - addr;
	uint8_t numOfPage =  numByteToWrite / AT24C0X_PAGE_SIZE;
	uint8_t numOfSingle = numByteToWrite % AT24C0X_PAGE_SIZE;
	//  
	if(addr == 0){// If writeAddr is AT24C0X_PAGE_SIZE aligned 
		if(numOfPage == 0){// If numByteToWrite < AT24C0X_PAGE_SIZE 
			status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer, writeAddr, numOfSingle);
			sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
		}
		else{//If numByteToWrite > AT24C0X_PAGE_SIZE 
			while(numOfPage--){
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer, writeAddr, AT24C0X_PAGE_SIZE); 
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
				writeAddr +=  AT24C0X_PAGE_SIZE;
				pBuffer += AT24C0X_PAGE_SIZE;
			}
			if(numOfSingle!=0){
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer, writeAddr, numOfSingle);
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
			}
		}
	}
	else{//If writeAddr is not AT24C0X_PAGE_SIZE aligned  
		if(numOfPage== 0){//If numByteToWrite < AT24C0X_PAGE_SIZE  
			if(count<numByteToWrite && count>0){
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer,writeAddr,count);
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
				numByteToWrite -= count;
				pBuffer += count;
				writeAddr += count;
			}
			if(numByteToWrite>0){
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer,writeAddr,numByteToWrite);
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
			}
		}
		else{//If numByteToWrite > AT24C0X_PAGE_SIZE 
			numByteToWrite -= count;
			numOfPage =  numByteToWrite / AT24C0X_PAGE_SIZE;
			numOfSingle = numByteToWrite % AT24C0X_PAGE_SIZE;	
			if(count != 0){  
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer, writeAddr, count);
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
				writeAddr += count;
				pBuffer += count;
			} 
			while(numOfPage--){
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer, writeAddr, AT24C0X_PAGE_SIZE);
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
				writeAddr +=  AT24C0X_PAGE_SIZE;
				pBuffer += AT24C0X_PAGE_SIZE;  
			}
			if(numOfSingle != 0){
				status |= sI2CInterface.PageWrite(AT24C0X_CS,pBuffer, writeAddr, numOfSingle); 
				sI2CInterface.WaitEepromStandbyState(AT24C0X_CS);
			}
		}
	}
	return status;  
}
//---------------------------------------------------------------------------------------------------------
//Read functions*******************************************************************************************
//---------------------------------------------------------------------------------------------------------
Type_MyI2cOpStatus AT24C0X_BufferRead(uint8_t* pBuffer,uint16_t readAddr,uint16_t numByteToRead){
	Type_MyI2cOpStatus status = MYI2C_SUCCSESS_READ_WRITE;
	uint8_t addr = readAddr%AT24C0X_PAGE_SIZE;
	uint8_t count = AT24C0X_PAGE_SIZE-addr;
	//uint8_t numOfPage =  numByteToRead/AT24C0X_PAGE_SIZE;
	//uint8_t numOfSingle = numByteToRead%AT24C0X_PAGE_SIZE;
	//
	if(count<numByteToRead && count>0){			
		status |= sI2CInterface.PageRead(AT24C0X_CS,pBuffer,readAddr,count);
		numByteToRead -= count;
		pBuffer += count;
		readAddr += count;
	}
	if(numByteToRead>0){
		status |= sI2CInterface.PageRead(AT24C0X_CS,pBuffer,readAddr,numByteToRead);
	}
	return status;
}
/*uint8_t AT24C0X_InitAndRead(uint8_t buf[],uint16_t virtAddr,uint16_t quontity){
	uint8_t readStat;
	AT24C0X_Init();
	readStat = AT24C0X_BufferRead(buf,virtAddr,quontity);
	//\\DbgOut_UnsNumToAsciiHex("\n\rAT24C0X_readStat = ",readStat,4);
	return readStat;
}*/
Type_MyI2cOpStatus AT24C0X_Erase(void){
  Type_MyI2cOpStatus status;	
	uint8_t Tx1_Buffer[AT24C0X_PAGE_SIZE] = "1234567890",len = sizeof(Tx1_Buffer),
		Rx1_Buffer[len]; 
	uint32_t addr = 0;
	//
	for(addr=0;addr<AT24C0X_MAX_ADDR;addr+=len){
		//First write in the memory followed by a read of the written data
		//Write on I2C EEPROM from EEPROM_WriteAddress1
			status = AT24C0X_BufferWrite(Tx1_Buffer,addr,len); 
		//Read from I2C EEPROM from EEPROM_ReadAddress1
			status = AT24C0X_BufferRead(Rx1_Buffer,addr,len); 
		//Check if the data written to the memory is read correctly
			if(AT24C0X_Buffercmp(Tx1_Buffer, Rx1_Buffer,len)==0){
				status = MYI2C_STATUS_ERROR;
				break;
			}
				else status = MYI2C_SUCCSESS_READ_WRITE;
	}
	return status;
}
