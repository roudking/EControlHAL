#ifndef _MENU_H
#define _MENU_H

#include "Menu_encoder.h"
#include "stdio.h"
#include "OLED.h"

typedef struct
{
	 int key;
	 int last_key;
     int menu_num;
	 int cursor;
	 int speed;
	 int last_speed;
}OLED_SHOW;


void Menu_init(void);
int Menu_getnum(void);
int Menu_getdeltanum(void);
void Menu_encoderclear(void);
void Menu_show(volatile OLED_SHOW *oled_show);

#endif
