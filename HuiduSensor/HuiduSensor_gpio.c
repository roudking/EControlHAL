#include "HuiduSensor_gpio.h"

void Huidu_ReadPin(int *array)
{
	array[0] = !gpio_readpin(Huidu_GPIO_PORT1, Huidu_GPIO_PIN1);
	array[1] = !gpio_readpin(Huidu_GPIO_PORT2, Huidu_GPIO_PIN2);
	array[2] = !gpio_readpin(Huidu_GPIO_PORT3, Huidu_GPIO_PIN3);
	array[3] = !gpio_readpin(Huidu_GPIO_PORT4, Huidu_GPIO_PIN4);
	array[4] = !gpio_readpin(Huidu_GPIO_PORT5, Huidu_GPIO_PIN5);
	array[5] = !gpio_readpin(Huidu_GPIO_PORT6, Huidu_GPIO_PIN6);
	array[6] = !gpio_readpin(Huidu_GPIO_PORT7, Huidu_GPIO_PIN7);
	array[7] = !gpio_readpin(Huidu_GPIO_PORT8, Huidu_GPIO_PIN8);	
}
