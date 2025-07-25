#ifndef __ANGLE_H
#define __ANGLE_H

#include "Angle_ic.h"

typedef struct {
  double angle; // Current angle position

  double frequency; // Frequency of the input signal
  double duty; // Duty cycle of the input signal

  ANGLE_CONFIG config; // Configuration for angle measurement
} ANGLE;

void Angle_Create_and_Initbuffer(ANGLE_CONFIG config);
void Angle_getduty(ANGLE *angle); // Function to get the current duty cycle and frequency

#endif // __ANGLE_H
