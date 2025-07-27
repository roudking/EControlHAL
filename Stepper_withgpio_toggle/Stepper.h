#ifndef STEPPER_H
#define STEPPER_H

#include "Stepper_gpio.h"

typedef struct {
    int arrived; // Flag to indicate if the stepper has arrived at the target position
    int toggle; // Flag to indicate if the stepper pin is toggled
} STEPPER_STATUS;


typedef struct {
    int step_count; // Number of steps to move
    int last_step_count; // Last step count for comparison

    int index; // Index of the stepper motor, used for buffer management

    STEPPER_STATUS status; // Status of the stepper motor
    STEPPER_CONFIG config; // Configuration for the stepper motor
} STEPPER;

void Stepper_create(STEPPER *stepper, STEPPER_CONFIG config, int index);
void Stepper_init(STEPPER *stepper);
void Stepper_get_arrived(STEPPER *stepper);
void Stepper_set_steps_relative(STEPPER *stepper, int steps);
void Stepper_set_steps_absolute(STEPPER *stepper, int steps);

#endif // STEPPER_H