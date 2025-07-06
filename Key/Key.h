#ifndef _KEY_H
#define _KEY_H

#include "Key_gpio.h"
 
typedef struct
{
   int pin_value;
}My_KEY;
 
void Key_getvalue(My_KEY *key);
 
#endif 
