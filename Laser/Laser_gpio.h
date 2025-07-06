#ifndef _LASER_GPIO_H
#define _LASER_GPIO_H

#include "my_gpio.h"

#define LASER_GPIO_Port GPIOE
#define LASER_GPIO_Pin GPIO_PIN_4

void _Laser_on(void);
void _Laser_off(void);


#endif