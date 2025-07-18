#ifndef _MENU_H
#define _MENU_H

#include "Menu_encoder.h"
#include "stdio.h"
#include "OLED.h"

typedef struct
{
   int speed;
   int last_speed;
   int speed_flag;
}SHOW_MESSAGE;

typedef struct
{
	 int key;
	 int last_key;

	 int cursor;
     int menu_num;

	 SHOW_MESSAGE message;
}OLED_SHOW;


void Menu_init(void);
void Menu_show(volatile OLED_SHOW *oled_show);
void Menu_showfuc(volatile OLED_SHOW *oled_show);
void Menu_keyfuc(volatile OLED_SHOW *oled_show);

#endif
