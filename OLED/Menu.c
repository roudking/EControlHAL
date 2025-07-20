#include "Menu.h"

void Menu_init(void)
{
   menu_encoderinit();
}

void Menu_showmain(volatile OLED_SHOW *oled_show);
void Menu_showT1(volatile OLED_SHOW *oled_show);
void Menu_showT2(volatile OLED_SHOW *oled_show);
void Menu_showT3(volatile OLED_SHOW *oled_show);
void Menu_showT4(volatile OLED_SHOW *oled_show);

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
	//  else if(oled_show->menu_num == 3)
	//  {
	//     Menu_showT3(oled_show);
	//  }
	//  else if (oled_show->menu_num == 4)
	//  {
	//     Menu_showT4(oled_show);
	//  }
	 
}

void Menu_showmain(volatile OLED_SHOW *oled_show)
{
	 if(oled_show->cursor >= 0 && oled_show->cursor <= 100)
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
	  menu_encoderclear();
	 }
}

void Menu_showT1(volatile OLED_SHOW *oled_show)
{
	char message[100];

	OLED_PrintString(0, 0 ,"Hand", &myfont, OLED_COLOR_NORMAL); 
	sprintf(message,"Target : %d RPM",oled_show->message.speed);
	OLED_PrintString(0, 12 ,message, &myfont, OLED_COLOR_NORMAL); 
	sprintf(message,"Current : %d RPM",oled_show->message.last_speed);
	OLED_PrintString(0, 24 ,message, &myfont, OLED_COLOR_NORMAL); 
	
}


void Menu_showT2(volatile OLED_SHOW *oled_show)
{
    char message[100];
  OLED_PrintString(0, 0 ,"Auto", &myfont, OLED_COLOR_NORMAL); 
	sprintf(message,"Speed : %d RPM",oled_show->message.speed);
	OLED_PrintString(0, 0 ,message, &myfont, OLED_COLOR_NORMAL); 
}





void Menu_showmainfuc(volatile OLED_SHOW *oled_show);
void Menu_showT1fuc(volatile OLED_SHOW *oled_show);
void Menu_showT2fuc(volatile OLED_SHOW *oled_show);
void Menu_showT3fuc(volatile OLED_SHOW *oled_show);
void Menu_showT4fuc(volatile OLED_SHOW *oled_show);

void Menu_showfuc(volatile OLED_SHOW *oled_show)
{
   if(oled_show->menu_num == 0)
	 {
	    Menu_showmainfuc(oled_show);
	 }
	 else if(oled_show->menu_num == 1)
	 {
	    Menu_showT1fuc(oled_show);
	 }
	 else if(oled_show->menu_num == 2)
	 {
	    Menu_showT2fuc(oled_show);
	 }
	//  else if(oled_show->menu_num == 3)
	//  {
	//     Menu_showT3fuc(oled_show);
	//  }
	//  else if (oled_show->menu_num == 4)
	//  {
	//     Menu_showT4fuc(oled_show);
	//  }
}

void Menu_showmainfuc(volatile OLED_SHOW *oled_show)
{
     oled_show->cursor = Menu_getnum();
}

void Menu_showT1fuc(volatile OLED_SHOW *oled_show)
{
	  	static int speed_cnt = 0;
	   if(speed_cnt < 50) speed_cnt ++;
		else
		{
		    speed_cnt = 0;
		oled_show->message.last_speed = oled_show->message.speed + rand() % 3 - 2;
			if(oled_show->message.last_speed < 0) oled_show->message.last_speed = 0;
		}

	    oled_show->message.speed = Menu_getnum()/20.0;
		if(oled_show->message.speed > 120) oled_show->message.speed = 120;
		else if(oled_show->message.speed < -120) oled_show->message.speed = -120;
}

void Menu_showT2fuc(volatile OLED_SHOW *oled_show)
{
	 static int cnt = 0;
		 static int cnt_up = 30;
		
		
		 if(cnt < cnt_up) cnt ++;
		else 
		{
			cnt = 0;
		 if(oled_show->message.speed < 100 && oled_show->message.speed_flag == 0) 
		 {
			 oled_show->message.speed += 10;
			 if(oled_show->message.speed == 100) {
				 cnt_up = 200;
			   oled_show->message.speed_flag = 2;
			 }
		 }
		 else if(oled_show->message.speed == 100 && oled_show->message.speed_flag == 2)
		 {
		  cnt_up = 20;
			oled_show->message.speed_flag = 0;
		 }
		 else if(oled_show->message.speed >= 100 && oled_show->message.speed < 120 && oled_show->message.speed_flag == 0)
		 {
			oled_show->message.speed++;
		 }
		 else if(oled_show->message.speed == 120 && oled_show->message.speed_flag == 0) 
		 {
		   oled_show->message.speed_flag = 1;
			 cnt_up = 50;
		 }
		 
		 else if(oled_show->message.speed > 10 && oled_show->message.speed_flag == 1) oled_show->message.speed -= 10;
		 else 
		 {
			 cnt_up = 30;
			 oled_show->message.speed = 0;
			 oled_show->message.speed_flag = -1;
		 }

		}
}



void Menu_showmainkeyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT1keyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT2keyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT3keyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT4keyfuc(volatile OLED_SHOW *oled_show);


void Menu_keyfuc(volatile OLED_SHOW *oled_show)
{
	 oled_show->last_key = oled_show->key;
	 oled_show->key = Key_read();

 if(oled_show->last_key == 1 && oled_show->key == 0)
 {
   if(oled_show->menu_num == 0)
	 {
	    Menu_showmainkeyfuc(oled_show);
	 }
	 else if(oled_show->menu_num == 1)
	 {
	    Menu_showT1keyfuc(oled_show);
	 }
	 else if(oled_show->menu_num == 2)
	 {
	    Menu_showT2keyfuc(oled_show);
	 }
	//  else if(oled_show->menu_num == 3)
	//  {
	//     Menu_showT3keyfuc(oled_show);
	//  }
	//  else if (oled_show->menu_num == 4)
	//  {
	//     Menu_showT4keyfuc(oled_show);
	//  }
 }

}

void Menu_showmainkeyfuc(volatile OLED_SHOW *oled_show)
{
  	if(oled_show->cursor <= 100 && oled_show->cursor >= 0)  oled_show->menu_num = 1;
    else if(oled_show->cursor > 100 && oled_show->cursor < 200) oled_show->menu_num = 2;
			oled_show->cursor = 0;
			oled_show->message.speed  = 0;
}

void Menu_showT1keyfuc(volatile OLED_SHOW *oled_show)
{
		  oled_show->menu_num = 0;
		  oled_show->cursor = 0;
		  oled_show->message.speed = 0;
}

void Menu_showT2keyfuc(volatile OLED_SHOW *oled_show)
{
		  oled_show->menu_num = 0;
		  oled_show->cursor = 0;
		  oled_show->message.speed = 0;
}