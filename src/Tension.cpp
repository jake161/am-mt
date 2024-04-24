#include "Tension.h"

// Calculates belt tension from frequency and linear density
float tension(float freq, float mu, float len)
{
  float tension = mu * pow(2.0 * len * freq, 2);

  return tension;
}