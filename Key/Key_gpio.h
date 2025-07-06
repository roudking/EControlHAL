#ifndef _KEY_GPIO_H
#define _KEY_GPIO_H

#include "my_gpio.h"

#define Key_GPIO_PORT GPIOE
#define Key_GPIO_Pin  GPIO_PIN_3

int Key_read(void);

#endif
