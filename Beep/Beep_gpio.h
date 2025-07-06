#ifndef _BEEP_GPIO_H
#define _BEEP_GPIO_H

#include "my_gpio.h"

#define Beep_GPIO_PORT GPIOC
#define Beep_GPIO_Pin GPIO_PIN_12

void beep_on(void);
void beep_off(void);

#endif 
