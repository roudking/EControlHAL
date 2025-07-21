#ifndef KEY_CONFIG_H
#define KEY_CONFIG_H

#include "my_gpio.h"

typedef struct
{
    GPIO_TypeDef *gpio_port;  // GPIO port for the key
    uint16_t gpio_pin;        // GPIO pin number for the key
} KEY_CONFIG;

extern KEY_CONFIG key1_config;
// extern KEY_CONFIG key2_config;

#endif // KEY_CONFIG_H