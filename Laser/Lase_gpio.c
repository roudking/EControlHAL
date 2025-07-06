#include "Laser_gpio.h"

void _Laser_on(void)
{
    gpio_resetpin(LASER_GPIO_Port,LASER_GPIO_Pin);
}

void _Laser_off(void)
{
  gpio_setpin(LASER_GPIO_Port,LASER_GPIO_Pin);
}
