#ifndef _MENU_H
#define _MENU_H

#include "Menu_encoder.h"
#include "Key.h"
#include "oled.h"
#include "stdio.h"
#include "Huidu.h"
#include "serial.h"

typedef struct
{
   int black_calibration_flag;
   int white_calibration_flag;
   int working_flag;
   int N;
   int problem_index;

   volatile HUIDU huidu;
}SHOW_MESSAGE;

typedef struct
{
	 int key_value;
	 int last_key_value;

	 int cursor;
    int menu_num;

	 MYKEY key;

	volatile SHOW_MESSAGE message;
}OLED_SHOW;


void Menu_init(void);
void Menu_show(volatile OLED_SHOW *oled_show);
void Menu_keyfuc(volatile OLED_SHOW *oled_show);

#endif
