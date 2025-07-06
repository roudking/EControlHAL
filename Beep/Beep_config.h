#ifndef _BEEP_CONFIG_H
#define _BEEP_CONFIG_H

#include "my_gpio.h"

typedef struct {
    GPIO_TypeDef *BeepGPIO_PORT;
    uint16_t BeepGPIO_Pin;
}BEEP_CONFIG;

extern BEEP_CONFIG beep_config;

#endif
