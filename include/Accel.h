#ifndef ACCEL_H
#define ACCEL_H

#include <Wire.h>
#include <MPU6050.h>

extern MPU6050 accel;
extern float accelXg, accelYg, accelZg;

void getAccelCorrected();
void setupAccel();

#endif
