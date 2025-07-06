#include "Key_gpio.h"

int Key_getvalue(KEY_CONFIG config)
{
  return gpio_readpin(config.KEYGPIO_PORT, config.KEYGPIO_PIN);
}