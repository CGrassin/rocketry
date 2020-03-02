/**
 * Designed for Sagan MK1 PCB using 
 * Arduino Pro Mini with 328P at 8MHz/3.3V.
 * 
 * Charles GRASSIN, 2019
 * MIT License
 */

// Libs
#include "PID.h"
#include "MPU6050.h"
#include "BMP280.h"
#include <Servo.h>
#include <SPI.h>
#include <SD.h>


// PINS (for the Sagan MK1 PCB)
#define PIN_PYRO_1 (2)
#define PIN_PYRO_2 (3)
#define PIN_SERVO_X (7)
#define PIN_SERVO_Y (8)
#define PIN_SERVO_E (9)
#define PIN_BUZZER (A0)
#define PIN_LED (A3)
#define PIN_SD_CS (10)

// 
#define PITCH_ERROR (700)
#define PITCH_OK    (500)

// CONFIG
//#define SD_CARD_ENABLE
#define SERIAL_DEBUG_ENABLE
#define SD_CARD_FILENAME "data.csv" // Warning: 8.3 format mandatory

#define MPU6050_X_ANGLE_ERROR (-74)
#define MPU6050_Y_ANGLE_ERROR (11) // unused
#define MPU6050_Z_ANGLE_ERROR (-4)

// Global variables
Servo servo_x, servo_y;
PIDController pidx = PIDController(0,0,0), pidy = PIDController(0,0,0);
File sd_file;
uint32_t pressure;
int16_t gyroX, gyroY, gyroZ;
double angular_speed, angle_x = 0, angle_y = 0;
long timeCurrent, timePrevious;

void setup(){
  #ifdef SERIAL_DEBUG_ENABLE
    Serial.begin(115200);
  #endif
  
  // Servos
	servo_x.attach(PIN_SERVO_X);
  servo_y.attach(PIN_SERVO_Y);

  // Pyro channels
  pinMode(PIN_PYRO_1, OUTPUT);
  digitalWrite(PIN_PYRO_1, LOW);
  pinMode(PIN_PYRO_2, OUTPUT);
  digitalWrite(PIN_PYRO_2, LOW);

  // Outputs
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // MPU6050 Gyro
  if(MPU_init() == -1)
    criticalError();
  
  // BMP280 Baro
  if(BMP_init() == -1)
    criticalError();
  
  // SD card (open card and file)
  #ifdef SD_CARD_ENABLE
    if (!SD.begin(PIN_SD_CS))
      criticalError();
    sd_file = SD.open(SD_CARD_FILENAME, FILE_WRITE);
    if (!sd_file)
      criticalError();
  #endif

  // Signal ready to fligh
  #ifdef SERIAL_DEBUG_ENABLE
    Serial.println("READY!");
  #endif
  tone(PIN_BUZZER, PITCH_OK, 1000);

  timeCurrent = millis();
}

void loop(){
  // Timing
  timePrevious = timeCurrent;
  timeCurrent = millis();

  // Read sensors
  pressure = BMP_getP();
  MPU_getRawGyro(&gyroX,&gyroY,&gyroZ);

  // Compute angle
  angular_speed = (float)(gyroX - MPU6050_X_ANGLE_ERROR)/32.8;
  angle_x += angular_speed * (timeCurrent - timePrevious) / 1000.0;
  angular_speed = (float)(gyroZ - MPU6050_Z_ANGLE_ERROR)/32.8;
  angle_y += angular_speed * (timeCurrent - timePrevious) / 1000.0;

  // Servos
  servo_x.write(angle_x + 90);
  servo_y.write(angle_y + 90);
  
  #ifdef SERIAL_DEBUG_ENABLE
    Serial.print(angle_x);
    Serial.print("\t");
    Serial.println(angle_y);
  #endif
  
  #ifdef SD_CARD_ENABLE
    logSD(angle_x, angle_y);
  #endif
  delay(20);
}

void criticalError(){
  #ifdef SERIAL_DEBUG_ENABLE
    Serial.println("ERROR!");
  #endif
  
  while(1){
    tone(PIN_BUZZER, PITCH_ERROR, 200);
    delay(400);
  }
}

/*
 * Format: tab separated values. Columns:
 * - Date
 */
void logSD(float val1, float val2){
  // FIXME fill me in
  sd_file.print(millis());
  sd_file.print("\t");
  sd_file.print(val1);
  sd_file.print("\t");
  sd_file.print(val2);
  sd_file.print("\n");
  sd_file.flush();
}
