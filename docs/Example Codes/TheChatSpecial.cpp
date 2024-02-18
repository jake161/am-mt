#include <Arduino.h>

#define MIC_PIN             A2                  // Analog pin connected to the microphone
#define SAMPLE_RATE         44100               // Audio sample rate in Hz
#define NUM_SAMPLES         2048                // Number of samples to process for frequency estimation
#define SAMPLE_DELAY_US     (1000000 / SAMPLE_RATE) // Delay between samples in microseconds
#define DC_OFFSET           1700                // Analog voltage offset to center at 0, NEEDS TUNING
// Number of previous frequency values to average
#define NUM_VALUES_TO_AVERAGE 5

void setup() {
    Serial.begin(9600);
}

void loop() {
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

    // Store current frequency value in the array
    previous_values[index] = frequency;
    index = (index + 1) % NUM_VALUES_TO_AVERAGE;

    // Calculate average frequency value
    float average_frequency = 0;
    for (int i = 0; i < NUM_VALUES_TO_AVERAGE; i++) {
        average_frequency += previous_values[i];
    }
    average_frequency /= NUM_VALUES_TO_AVERAGE;

    // Output the dominant frequency
    Serial.print("Dominant Frequency: ");
    Serial.print(average_frequency);
    Serial.println(" Hz");

    delay(1000); // Adjust as needed for your application
}
