#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h> // Replace with your sensor library


// Mic Setup
#define MIC_PIN             A2                  // Analog pin connected to the microphone
#define SAMPLE_RATE         44100               // Audio sample rate in Hz
#define NUM_SAMPLES         2048                // Number of samples to process for frequency estimation
#define SAMPLE_DELAY_US     (1000000 / SAMPLE_RATE) // Delay between samples in microseconds
#define DC_OFFSET           1635                // Analog voltage offset to center at 0, NEEDS TUNING
#define NUM_VALUES_TO_AVERAGE 5                 // Number of previous frequency values to average

// Initialize sensor objects
MPU6050 accel;
float accelXg, accelYg, accelZg;

float alpha = 1; // This is the smoothing factor, adjust it to your needs
float lastOutput = 0.0; // This will hold the last output value

float tension(float, float, float);
float processAudio();
void getAccelCorrected();
float lowPassFilter(float);


void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Accelerometer Begin
  Wire.begin(); // Start the wire libary (used by the accelerometer)
  accel.initialize();      // Initialize the accelerometer
  accel.CalibrateAccel(6); // Calibrate the accelerometer with 6 loops
}

void loop() {

  // Get current time
  unsigned long time = millis();

  // Print time vs frequency
  getAccelCorrected();
  Serial.println(accelXg); // Replace with your method to get frequency
  delay(100);
}

// Calculates belt tension from frequency and linear density
float tension(float freq, float mu, float len)
{
  float tension = mu * pow(2.0 * len * freq, 2);

  return tension;
}

float processAudio() {
    unsigned long last_crossing_time = 0;
    unsigned long crossings = 0;

    // Array to store previous frequency values for averaging
    float previous_values[NUM_VALUES_TO_AVERAGE] = {0};
    int index = 0;

    // Collect audio samples
    for (int i = 0; i < NUM_SAMPLES; i++) {
        int sample = analogRead(MIC_PIN) - DC_OFFSET; // Read analog input and center around 0

        // Check for zero-crossings
        if (i > 0 && sample * (analogRead(MIC_PIN) - DC_OFFSET) < 0) {
            if (last_crossing_time != 0) {
                unsigned long current_time = micros();
                unsigned long period = current_time - last_crossing_time;
                crossings++;

                last_crossing_time = current_time;
            } else {
                last_crossing_time = micros();
            }
        }

        delayMicroseconds(SAMPLE_DELAY_US); // Adjusted delay between samples
    }

    // Calculate frequency based on zero-crossings
    float frequency;
    if (crossings > 0) {
        // Convert crossings to Hz
        frequency = (float)crossings * 1000000 / (NUM_SAMPLES * SAMPLE_DELAY_US);
    } else {
        frequency = 0; // Default to 0 if no crossings
    }

    // Store current frequency values
    previous_values[index] = frequency;
    index = (index + 1) % NUM_VALUES_TO_AVERAGE;

    // Calculate average frequency value
    float average_frequency = 0;
    for (int i = 0; i < NUM_VALUES_TO_AVERAGE; i++) {
        average_frequency += previous_values[i];
    }
    average_frequency /= NUM_VALUES_TO_AVERAGE;

    // Output the dominant frequency
    return average_frequency;
}

void getAccelCorrected() { // Provide this portion of the code to the students.
  int16_t ax, ay, az; // Initialize acceleration variables in the different axes. "int16_t" means 16-bit integer.
  accel.getAcceleration(&ax, &ay, &az); // Get axis acceleration values.
  accelXg = float(ax) / 8192 /2 ; // Conversion to g's.
  accelYg = float(ay) / 8192 /2; // Conversion to g's.
  accelZg = float(az) / 8192 /2 ; // Conversion to g's.
}

float lowPassFilter(float input) {
  float output = alpha * input + (1.0 - alpha) * lastOutput;
  lastOutput = output;
  return output;
}