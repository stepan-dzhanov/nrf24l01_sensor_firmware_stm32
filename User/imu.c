
#include "imu.h"
#include "tm_stm32f4_i2c.h"


void IMU_Read (IMUData_Typedef *IMU_result){
  uint8_t result[7];
  uint8_t temp=0;
  uint8_t temp1=0;
  uint16_t xacc, yacc,zacc =0;
  temp =0;
 TM_I2C_ReadMulti(I2C1,ACC_SAD, 0x80|OUT_X_L_A, result, 6);
 xacc = result[1];
 xacc = xacc<<8;
 xacc |= result[0];
 yacc = result[3];
 yacc = yacc<<8;
 yacc |= result[2];
 zacc = result[5];
 zacc = zacc<<8;
 zacc |= result[4];
 
 //return;
  IMU_result->x_acc = result[1];
  IMU_result->x_acc = IMU_result->x_acc<<8;
  IMU_result->x_acc |= result[0];
  IMU_result->y_acc = result[3];
  IMU_result->y_acc = IMU_result->y_acc<<8;
  IMU_result->y_acc |= result[2];
  IMU_result->z_acc = result[5];
  IMU_result->z_acc = IMU_result->z_acc<<8;
  IMU_result->z_acc |= result[4];

  TM_I2C_ReadMulti(I2C1,MAG_SAD, OUT_X_H_M, result, 6);
  
  IMU_result->x_mag = result[0];
  IMU_result->x_mag = IMU_result->x_mag<<8;
  IMU_result->x_mag |= result[1];
  IMU_result->y_mag = result[2];
  IMU_result->y_mag = IMU_result->y_mag<<8;
  IMU_result->y_mag |= result[3];
  IMU_result->z_mag = result[4];
  IMU_result->z_mag = IMU_result->z_mag<<8;
  IMU_result->z_mag |= result[5];
  
  TM_I2C_ReadMulti(I2C1,GYR_SAD, 0x80|OUT_X_L_G, result, 6);
  IMU_result->x_gyro = result[1];
  IMU_result->x_gyro = IMU_result->x_gyro<<8;
  IMU_result->x_gyro |= result[0];
  IMU_result->y_gyro = result[3];
  IMU_result->y_gyro = IMU_result->y_gyro<<8;
  IMU_result->y_gyro |= result[2];
  IMU_result->z_gyro = result[5];
  IMU_result->z_gyro = IMU_result->z_gyro<<8;
  IMU_result->z_gyro |= result[4];
  temp = 0;
  
  
  
  return;
 
  
}

void IMU_Init(){
  
  uint8_t Data[2] = {CTRL_REG1_A,0x57};
  uint8_t temp=0;
  TM_I2C_Init(I2C1, TM_I2C_PinsPack_2, 200000);
  
  TM_I2C_Write(I2C1, ACC_SAD, CTRL_REG1_A, 0x67); //axis enable 200 Hz 
  
  TM_I2C_Write(I2C1, MAG_SAD, CRA_REG_M , 0x1C);//220 HZ for magnetometer
  TM_I2C_Write(I2C1, MAG_SAD, CRB_REG_M , 0x00);//±1.3 Gauses full scale
  TM_I2C_Write(I2C1, MAG_SAD, MR_REG_M , 0x00);//Continuous-conversion mode
  
  TM_I2C_Write(I2C1, GYR_SAD, CTRL_REG1_G , 0x4F); //axis enable, normal mode, 190 HZ 
 // temp = TM_I2C_Read(I2C1,GYR_SAD, WHO_AM_I); Check type og gyro 
  return;
}