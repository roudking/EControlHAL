#include "Key_gpio.h"

int Key_read(void)
{
  return gpio_readpin(Key_GPIO_PORT,Key_GPIO_Pin);
}