#include "Accel.h"

MPU6050 accel;

float accelXg, accelYg, accelZg = 0;
static unsigned long prevTime = 0;
static float timeDiff = 0;
static float timeConst = 100;
static float alpha = 0;
static float data = 0;
static float filtered = 0;

void setupAccel() {
  // Accelerometer Begin
  Wire.begin(); // Start the wire libary (used by the accelerometer)
  accel.initialize();      // Initialize the accelerometer
  accel.CalibrateAccel(6); // Calibrate the accelerometer with 6 loops
}

void getAccelCorrected() {
    int16_t ax, ay, az;
    accel.getAcceleration(&ax, &ay, &az);

    timeDiff = micros() - prevTime;
    prevTime = micros();
    alpha = timeDiff / (timeConst + timeDiff);

    float rawAccelXg = float(ax) / 8192 /2 ;
    float rawAccelYg = float(ay) / 8192 /2;
    float rawAccelZg = float(az) / 8192 /2 ;

    accelXg = accelXg + alpha * (rawAccelXg - accelXg);
    accelYg = accelYg + alpha * (rawAccelYg - accelYg);
    accelZg = accelZg + alpha * (rawAccelZg - accelZg);
}