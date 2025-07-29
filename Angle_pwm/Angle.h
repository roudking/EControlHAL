#ifndef __ANGLE_H
#define __ANGLE_H

#include "Angle_ic.h"

typedef struct {
  double angle; // Current angle position
  double last_angle; // Last angle position
  double real_angle; // Real angle position

  double frequency; // Frequency of the input signal
  double duty; // Duty cycle of the input signal

  ANGLE_CONFIG *config; // Configuration for angle measurement
} ANGLE;

void Angle_Create(ANGLE *angle, ANGLE_CONFIG *config); // Function to create and initialize the angle structure
void Angle_init(ANGLE *angle); // Function to initialize the angle structure
void Angle_getduty_and_frequency(ANGLE *angle); // Function to get the current duty cycle and frequency
void Angle_getangle(ANGLE *angle); // Function to get the current angle based on duty cycle

#endif // __ANGLE_H
