/**
 * This file is an ultra light/simple BMP280
 * library for Arduino.
 * 
 * Charles GRASSIN, 2019
 * MIT License
 */
#include <Wire.h>

#define BMP_ADDR (0x76)

//REGISTERS
#define BMP_REG_ID (0xD0)
#define BMP_REG_STATUS (0xF3)
#define BMP_REG_CTRL_MEAS (0xF4)
#define BMP_REG_CONFIG (0xF5)
#define BMP_REG_PRESS (0xF7)

int8_t BMP_init(){
  Wire.begin();
  Wire.beginTransmission(BMP_ADDR);
  Wire.write(BMP_REG_CTRL_MEAS);
  Wire.write(/*osrs_t*/(0b000 << 5) + /*osrs_p*/(0b111 << 2) + /*mode*/0b11);
  Wire.endTransmission(true);

  Wire.begin();
  Wire.beginTransmission(BMP_ADDR);
  Wire.write(BMP_REG_CONFIG);
  Wire.write(/*t_sb*/(0b000 << 5) + /*filter*/(0b000 << 2) + /*spi3w_en*/0b0 );
  Wire.endTransmission(true);

  // Read ID register as sanity check
  Wire.beginTransmission(BMP_ADDR);
  Wire.write(BMP_REG_ID);
  Wire.endTransmission(false);
  Wire.requestFrom(BMP_ADDR, 1, true);
  return Wire.read();
}

/*
 * @returns The 20 bits raw pressure.
 */
uint32_t BMP_getP(){
  Wire.beginTransmission(BMP_ADDR);
  Wire.write(BMP_REG_PRESS);
  Wire.endTransmission(false);
  Wire.requestFrom(BMP_ADDR, 3, true);

  return 1048576 - (Wire.read()<<12 | Wire.read()<<4 | Wire.read()>>4);
}
