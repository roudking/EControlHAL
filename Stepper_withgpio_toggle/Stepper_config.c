#include "Stepper_config.h"

STEPPER_CONFIG stepper1_config = {
    .tim_port = &htim1, // Initialize with NULL or assign a valid TIM_HandleTypeDef pointer

    .step_port = GPIOA, // Step GPIO port
    .step_pin = Stepper1_Pin, // Step GPIO pin

    .dir_port = GPIOB, // Direction GPIO port
    .dir_pin = Dir1_Pin, // Direction GPIO pin

};

STEPPER_CONFIG stepper2_config = {
    .tim_port = &htim1, // Initialize with NULL or assign a valid TIM_HandleTypeDef pointer

    .step_port = GPIOA, // Step GPIO port
    .step_pin = Stepper2_Pin, // Step GPIO pin

    .dir_port = GPIOB, // Direction GPIO port
    .dir_pin = Dir2_Pin, // Direction GPIO pin

};