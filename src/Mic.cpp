#include "Mic.h"

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

static unsigned long prevTime = 0;
static float timeDiff = 0;
static float timeConst = 10;
static float alpha = 0;
static float data = 0;
static float filtered = 0;

void setupMic() {
    // Mic Setup
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

double getDominantFrequency() {
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