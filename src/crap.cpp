#include "arduinoFFT.h"

#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048
#define VOLT_OFFSET 250
#define MIC_PIN A0

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

unsigned long prevTime = 0;
float timeDiff = 0;
float timeConst = 10;
float alpha = 0;
float data = 0;
float filtered = 0;

void setup() {
    Serial.begin(115200);
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
    pinMode(7, INPUT);
}

void loop() {
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
    Serial.println(peak);
    delay(10);
}