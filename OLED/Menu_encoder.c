#include "Menu_encoder.h"

void menu_encoderinit(void)
{
  encoder_init(&Menu_TIMER_PORT);
}

int16_t menu_getnum(void)
{
    return encoder_justgetcounter(&Menu_TIMER_PORT);
}

int16_t menu_getdeltanum(void)
{
   return encoder_getcounter(&Menu_TIMER_PORT);
}

void menu_encoderclear(void)
{
 encoder_clear(&Menu_TIMER_PORT);
}