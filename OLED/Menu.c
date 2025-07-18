#include "Menu.h"

void Menu_init(void)
{
   menu_encoderinit();
}

int Menu_getnum(void)
{
  return menu_getnum(); 
}

int Menu_getdeltanum(void)
{
  return menu_getdeltanum();
}

void Menu_encoderclear(void)
{
  menu_encoderclear();
}


void Menu_showmain(volatile OLED_SHOW *oled_show);
void Menu_showT1(volatile OLED_SHOW *oled_show);
void Menu_showT2(volatile OLED_SHOW *oled_show);
void Menu_showT3((volatile OLED_SHOW *oled_show);

void Menu_show(volatile OLED_SHOW *oled_show)
{
   if(oled_show->menu_num == 0)
	 {
	    Menu_showmain(oled_show);
	 }
	 else if(oled_show->menu_num == 1)
	 {
	    Menu_showT1(oled_show);
	 }
	 else if(oled_show->menu_num == 2)
	 {
	    Menu_showT2(oled_show);
	 }
	 else if(oled_show->menu_num == 3)
	 {
	    Menu_showT3(oled_show);
	 }
	 
}


void Menu_showT2(volatile OLED_SHOW *oled_show)
{
    char message[100];
  OLED_PrintString(0, 0 ,"Auto", &myfont, OLED_COLOR_NORMAL); 
	sprintf(message,"Speed : %d RPM",oled_show->speed);
	OLED_PrintString(0, 0 ,message, &myfont, OLED_COLOR_NORMAL); 
}


void Menu_showT1(volatile OLED_SHOW *oled_show)
{
	
	char message[100];

	OLED_PrintString(0, 0 ,"Hand", &myfont, OLED_COLOR_NORMAL); 
	sprintf(message,"Target : %d RPM",oled_show->speed);
	OLED_PrintString(0, 12 ,message, &myfont, OLED_COLOR_NORMAL); 
	sprintf(message,"Current : %d RPM",oled_show->last_speed);
	OLED_PrintString(0, 24 ,message, &myfont, OLED_COLOR_NORMAL); 
	
}

void Menu_showmain(volatile OLED_SHOW *oled_show)
{
	 if(oled_show->cursor <= 100 && oled_show->cursor >= 0)
	 {
		OLED_PrintString(0, 0 ,"* T1", &myfont, OLED_COLOR_NORMAL); 
   	OLED_PrintString(0, 12,"  T2", &myfont, OLED_COLOR_NORMAL);  
	 }
	 else if(oled_show->cursor > 100 && oled_show->cursor < 200)
	 {
	  OLED_PrintString(0, 0 ,"  T1", &myfont, OLED_COLOR_NORMAL); 
   	OLED_PrintString(0, 12,"* T2", &myfont, OLED_COLOR_NORMAL);  
	 }
	 else 
	 {
		OLED_PrintString(0, 0 ,"* T1", &myfont, OLED_COLOR_NORMAL); 
   	OLED_PrintString(0, 12,"  T2", &myfont, OLED_COLOR_NORMAL);  
	   oled_show->cursor = 0;
		 Menu_encoderclear();
	 }
	 
}