#ifndef STEPPER_CONFIG_H
#define STEPPER_CONFIG_H

#include "my_gpio.h"
#include "tim_it.h"

typedef struct {
    TIM_HandleTypeDef* tim_port; // Pointer to the timer handle

    GPIO_TypeDef* dir_port; // Direction GPIO port
    uint16_t dir_pin; // Direction GPIO pin

    GPIO_TypeDef* step_port; // Step GPIO port
    uint16_t step_pin; // Step GPIO pin
        
} STEPPER_CONFIG;

extern STEPPER_CONFIG stepper1_config;
extern STEPPER_CONFIG stepper2_config;

#endif // STEPPER_CONFIG_H