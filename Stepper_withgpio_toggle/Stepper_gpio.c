#include "Stepper_gpio.h"

void Stepper_gpio_set_direction(STEPPER_CONFIG stepper, int direction) {
    // Set the GPIO pins for the stepper motor direction
    if (direction == 1) {
        // Set GPIO pins for forward direction
        gpio_setpin(stepper.dir_port, stepper.dir_pin);
    } else if (direction == -1) {
        // Set GPIO pins for backward direction
        gpio_resetpin(stepper.dir_port, stepper.dir_pin);
    }
}

void Stepper_gpio_togglepin(STEPPER_CONFIG stepper) {
    // Toggle the GPIO pin for stepping
    gpio_togglepin(stepper.step_port, stepper.step_pin);
}