#ifndef STEPPER_GPIO_H
#define STEPPER_GPIO_H

#include "Stepper_config.h"

void Stepper_gpio_set_direction(STEPPER_CONFIG stepper, int direction);
void Stepper_gpio_togglepin(STEPPER_CONFIG stepper);

#endif // STEPPER_GPIO_H