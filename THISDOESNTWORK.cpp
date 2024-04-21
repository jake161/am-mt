#include <Arduino.h>
#include "MPU6050.h" // Search "MPU6050" in library manager and select the one by Electronic Cats.
#include "Wire.h"
MPU6050 accel;

float accelXg, accelYg, accelZg; // Define the acceleration variables for each axis in g's.

void getAccelCorrected();

// Define other needed variables here:

void setup() {

  // Initialize Accelerometer
  Wire.begin(); // Start the wire libary (used by the accelerometer)
  Serial.begin(115200); // Start serial at 115200 baud
  accel.initialize(); // Initialize the accelerometer (with range +/- 2g)
  accel.CalibrateAccel(6); // Calibrate the accelerometer with 6 loops

  // Print data headers if desired here:
}

void loop() {
  getAccelCorrected(); // Function that will update the variables accelXg, accelYg, and accelZg. See function at the end of the code for details.
  Serial.println(accelXg); // Print the acceleration in the x-axis in g's.
  delay(100); // Delay for 100 ms.

}

// DO NOT TOUCH THE CODE BELOW
void getAccelCorrected() { // Provide this portion of the code to the students.
  int16_t ax, ay, az; // Initialize acceleration variables in the different axes. "int16_t" means 16-bit integer.
  accel.getAcceleration(&ax, &ay, &az); // Get axis acceleration values.
  accelXg = float(ax) / 8192 /2 ; // Conversion to g's.
  accelYg = float(ay) / 8192 /2; // Conversion to g's.
  accelZg = float(az) / 8192 /2 ; // Conversion to g's.
}