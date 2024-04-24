#ifndef TENSION_H
#define TENSION_H

#include <Arduino.h>

// Calculates belt tension from frequency and linear density
float tension(float freq, float mu, float len);

#endif
