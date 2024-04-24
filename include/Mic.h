#ifndef MIC_H
#define MIC_H

#include <arduinoFFT.h>

#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048
#define VOLT_OFFSET 250
#define MIC_PIN A2

static unsigned int samplingPeriod;
static unsigned long microSeconds;

static double vReal[SAMPLES];
static double vImag[SAMPLES];

void setupMic();
double getDominantFrequency();

#endif