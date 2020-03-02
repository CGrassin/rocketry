/**
 * This file is an ultra light/simple MPU6050
 * library for Arduino.
 * 
 * Charles GRASSIN, 2019
 * MIT License
 */
 
#include <Wire.h>

#define MPU_ADDR (0x68)

// Average error compensation
#define GYRO_ERROR_X 0
#define GYRO_ERROR_Y 0
#define GYRO_ERROR_Z 0

/*
Calibration code:
#include "MPU6050.h"
int16_t gyroX=0, gyroY=0, gyroZ=0;
void setup(){
  MPU_init();
  Serial.begin(9600);
  for(int i=0;i<100;i++){
    MPU_getRawGyro(&gyroX,&gyroY,&gyroZ);
    Serial.println(....);
  }
}
void loop(){}
 */

//REGISTERS
#define MPU_REG_PWR_MGMT_1 (0x6B)
#define MPU_REG_GYRO_CONFIG (0x1B)
#define MPU_REG_WHO_AM_I (0x75)
#define MPU_REG_ACCEL_XOUT_H (0x3B)
#define MPU_REG_GYRO_XOUT_H (0x43)

int8_t MPU_init(){
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(MPU_REG_PWR_MGMT_1);
  Wire.write(0);     // wakes up the MPU-6050
  Wire.endTransmission(true);
  
  // Gyro config
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(MPU_REG_GYRO_CONFIG);
  Wire.write(0x10); // 1000dps full scale
  Wire.endTransmission(true);

  // Read WHO AM I? register as sanity check
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(MPU_REG_WHO_AM_I);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 1, true);
  return Wire.read();
}

void MPU_getRawAcc(int16_t* accX, int16_t* accY, int16_t* accZ){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(MPU_REG_ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  
  *accX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  *accY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  *accZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}

void MPU_getRawGyro(int16_t* gyroX, int16_t* gyroY, int16_t* gyroZ){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(MPU_REG_GYRO_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  
  *gyroX=Wire.read()<<8|Wire.read() - GYRO_ERROR_X;  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  *gyroY=Wire.read()<<8|Wire.read() - GYRO_ERROR_Y;  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  *gyroZ=Wire.read()<<8|Wire.read() - GYRO_ERROR_Z;  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}
