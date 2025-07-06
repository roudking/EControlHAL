#include "Key.h"

void Key_create(KEY *key, KEY_CONFIG config)
{
  key->config = config;
}

void Key_read(KEY *key)
{
  key->pin_value = Key_getvalue(key->config);
}