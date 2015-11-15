#ifndef _LSM_
#define _LSM_

#include "stm32f4xx.h"

#define ACC_SAD  0x32
#define MAG_SAD  0x3D
#define GYR_SAD  0xD6

#define WHO_AM_I  0x0F
#define CTRL_REG1_G 0x20

#define OUT_X_L_G   0x28


#define CTRL_REG1_A 0x20     //ACC enadle axises, data update frq
#define CTRL_REG4_A 0x23     //ACC full scale
#define CRA_REG_M   0x00     //MAG data output rate
#define CRB_REG_M   0x01     //MAG Gain configuration
#define MR_REG_M    0x02     //Conversion mode


#define OUT_X_L_A   0x28
#define OUT_X_H_A   0x29
#define OUT_Y_L_A   0x2A
#define OUT_Y_H_A   0x2B
#define OUT_Z_L_A   0x2C
#define OUT_Z_H_A   0x2D


#define OUT_X_H_M   0x03
#define OUT_X_L_M   0x04
#define OUT_Z_H_M   0x05
#define OUT_Z_L_M   0x06
#define OUT_Y_H_M   0x07
#define OUT_Y_L_M   0x08



typedef struct {
  u16 x_acc;
  u16 y_acc;
  u16 z_acc;
  u16 x_mag;
  u16 y_mag;
  u16 z_mag;
  u16 x_gyro;
  u16 y_gyro;
  u16 z_gyro;
  
} IMUData_Typedef;

void IMU_Init();
void IMU_Read (IMUData_Typedef *IMU_result);



#endif 