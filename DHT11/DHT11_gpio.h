#ifndef _DHT11_GPIO_H
#define _DHT11_GPIO_H

#include "my_gpio.h"

#define DHT11_GPIO_PORT GPIOC
#define DHT11_GPIO_PIN GPIO_PIN_0

#define dht11_high  gpio_setpin(DHT11_GPIO_PORT, DHT11_GPIO_PIN)
#define dht11_low   gpio_resetpin(DHT11_GPIO_PORT, DHT11_GPIO_PIN)
#define Read_Data   gpio_readpin(DHT11_GPIO_PORT, DHT11_GPIO_PIN)

//对于stm32来说，是输出
void DH11_GPIO_Init_OUT(void);

//对于stm32来说，是输入
void DH11_GPIO_Init_IN(void);


#endif
