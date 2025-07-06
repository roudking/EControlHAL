#ifndef _KEY_H
#define _KEY_H

#include "Key_gpio.h"
 
typedef struct
{
   int pin_value;
   KEY_CONFIG config; // Key configuration structure
}KEY;

void Key_create(KEY *key, KEY_CONFIG config);
void Key_read(KEY *key);

#endif
