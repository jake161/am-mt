#include "arduinoFFT.h"
#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048
#define VOLT_OFFSET 250
#define MIC_PIN A2

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

unsigned long prevTime = 0;
float timeDiff = 0;
float timeConst = 100;
float alpha = 0;
float data = 0;
float filtered = 0;

// Acceleration Sensor Setup
MPU6050 accel;
float accelXg, accelYg, accelZg;


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

double freq(){
        for(int i=0; i<SAMPLES; i++) {
        microSeconds = micros();

        timeDiff = micros() - prevTime;
        prevTime = micros();
        alpha = timeDiff / (timeConst + timeDiff);
        data = analogRead(MIC_PIN) - VOLT_OFFSET;
        filtered = filtered + alpha * (data - filtered);

        vReal[i] = filtered;
        vImag[i] = 0;

        while(micros() < (microSeconds + samplingPeriod)) {
            //do nothing
        }
    }

    FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.complexToMagnitude(vReal, vImag, SAMPLES);

    double peak = FFT.majorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    return peak;
}

void setup() {
    Serial.begin(9600);
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
    // Accelerometer Begin
    Wire.begin();            // Start the wire libary (used by the accelerometer)
    accel.initialize();      // Initialize the accelerometer
    accel.CalibrateAccel(6); // Calibrate the accelerometer with 6 loops
}

void loop() {

    // //raw
    // Serial.println(analogRead(MIC_PIN)-VOLT_OFFSET);

    // //filtered
    // timeDiff = micros() - prevTime;
    // prevTime = micros();
    // alpha = timeDiff / (timeConst + timeDiff);
    // data = analogRead(MIC_PIN) - VOLT_OFFSET;
    // filtered = filtered + alpha * (data - filtered);
    // Serial.println(filtered);

    // //frequency
    // Serial.println(freq());
    // delay(10);

    //acceleration
    getAccelCorrected();
    Serial.print(accelXg);
    Serial.print(" ");
    Serial.print(accelYg);
    Serial.print(" ");
    Serial.println(accelZg);
    delay(10);

}