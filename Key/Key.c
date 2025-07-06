#include "Key.h"

void Key_getvalue(My_KEY *key)
{
  key->pin_value = Key_read();
}