
#include "Beep_config.h"

#define BEEP_GPIO_PORT GPIOA
#define BEEP_GPIO_PIN GPIO_PIN_0   

BEEP_CONFIG beep_config = {
    .BeepGPIO_PORT = BEEP_GPIO_PORT,
    .BeepGPIO_Pin = BEEP_GPIO_PIN
};
