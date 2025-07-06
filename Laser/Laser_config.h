#ifndef _LASER_CONFIG_H
#define _LASER_CONFIG_H

#include "my_gpio.h"

typedef struct
{
    GPIO_TypeDef *LaserGPIO_PORT;  // GPIO port for the laser
    uint16_t LaserGPIO_PIN;       // GPIO pin for the laser
} LASER_CONFIG;

extern LASER_CONFIG laser_config;

#endif

