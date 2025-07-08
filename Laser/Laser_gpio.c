#include "Laser_gpio.h"

void _Laser_on(LASER_CONFIG config)
{
    gpio_resetpin(config.LaserGPIO_PORT, config.LaserGPIO_PIN);
}

void _Laser_off(LASER_CONFIG config)
{
    gpio_setpin(config.LaserGPIO_PORT, config.LaserGPIO_PIN);
}
