#ifndef _MENU_ENCODER_H
#define _MENU_ENCODER_H

#include "encoder.h"

#define Menu_TIMER_PORT htim3

void menu_encoderinit(void);
int16_t menu_getnum(void);
int16_t menu_getdeltanum(void);
void menu_encoderclear(void);

#endif 
