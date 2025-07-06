#ifndef _HUIDUSENSOR_GPIO_H
#define _HUIDUSENSOR_GPIO_H

#include "my_gpio.h"

#define Huidu_GPIO_PORT1  GPIOD
#define Huidu_GPIO_PIN1 GPIO_PIN_0

#define Huidu_GPIO_PORT2  GPIOD
#define Huidu_GPIO_PIN2 GPIO_PIN_1

#define Huidu_GPIO_PORT3  GPIOD
#define Huidu_GPIO_PIN3 GPIO_PIN_2

#define Huidu_GPIO_PORT4  GPIOD
#define Huidu_GPIO_PIN4 GPIO_PIN_3

#define Huidu_GPIO_PORT5  GPIOD
#define Huidu_GPIO_PIN5 GPIO_PIN_4

#define Huidu_GPIO_PORT6  GPIOD
#define Huidu_GPIO_PIN6 GPIO_PIN_5

#define Huidu_GPIO_PORT7  GPIOD
#define Huidu_GPIO_PIN7 GPIO_PIN_6

#define Huidu_GPIO_PORT8  GPIOD
#define Huidu_GPIO_PIN8 GPIO_PIN_7

void Huidu_ReadPin(int *array);


#endif
