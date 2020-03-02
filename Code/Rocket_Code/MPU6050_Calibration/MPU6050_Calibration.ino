#include "MPU6050.h"

#define MEASUREMENTS_NB 100
#define MEASUREMENTS_DELAY 100

int16_t gyroX, gyroY, gyroZ;
int32_t totalX=0, totalY=0, totalZ=0;

void setup() {
  Serial.begin(115200);
  MPU_init();

  Serial.println("Measuring...");
  for(int i=0; i<MEASUREMENTS_NB;i++){
    delay(MEASUREMENTS_DELAY);
    MPU_getRawGyro(&gyroX,&gyroY,&gyroZ);
    totalX += gyroX;
    totalY += gyroY;
    totalZ += gyroZ;
  }

  Serial.println("Result:");

  Serial.print("X_error=");
  Serial.println((float)totalX/MEASUREMENTS_NB);
  
  Serial.print("Y_error=");
  Serial.println((float)totalY/MEASUREMENTS_NB);
  
  Serial.print("Z_error=");
  Serial.println((float)totalZ/MEASUREMENTS_NB);
}

void loop() {}
