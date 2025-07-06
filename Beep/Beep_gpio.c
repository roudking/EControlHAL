#include "Beep_gpio.h"

void beep_on(void)
{
	gpio_setpin(Beep_GPIO_PORT, Beep_GPIO_Pin);
}

void beep_off(void)
{
  gpio_resetpin(Beep_GPIO_PORT, Beep_GPIO_Pin);
}