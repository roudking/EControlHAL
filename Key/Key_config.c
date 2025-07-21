#include "Key_config.h"

#define KEY1_GPIO_PORT GPIOA
#define KEY1_PIN GPIO_PIN_0

// #define KEY2_GPIO_PORT GPIOA
// #define KEY2_PIN GPIO_PIN_1

KEY_CONFIG key1_config = {
    .gpio_port = KEY1_GPIO_PORT,
    .gpio_pin = KEY1_PIN
};

// KEY_CONFIG key2_config = {
//     .gpio_port = KEY2_GPIO_PORT,
//     .gpio_pin = KEY2_PIN
// };
