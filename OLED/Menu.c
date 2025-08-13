#include "Menu.h"

#define step 3

void Menu_init(void)
{
   menu_encoderinit();
}

void Menu_showmain(volatile OLED_SHOW *oled_show);
void Menu_showT1(volatile OLED_SHOW *oled_show);
void Menu_showT2(volatile OLED_SHOW *oled_show);
void Menu_showT3(volatile OLED_SHOW *oled_show);
// void Menu_showT4(volatile OLED_SHOW *oled_show);

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

void Menu_showmain(volatile OLED_SHOW *oled_show)
{
	 if(oled_show->cursor >= 0 && oled_show->cursor <= step)
	 {
	    OLED_ShowString(1, 1 ,"* Calibration", 2); 
   	    OLED_ShowString(3, 1 ,"  Basic part", 2);  
        OLED_ShowString(5, 1 ,"  Improve part", 2);
	 }
	 else if(oled_show->cursor > step && oled_show->cursor < 2 * step)
	 {
	    OLED_ShowString(1, 1 ,"  Calibration", 2); 
   	    OLED_ShowString(3, 1 ,"* Basic part", 2);  
        OLED_ShowString(5, 1 ,"  Improve part", 2);
	 }
     else if(oled_show->cursor >= 2 * step && oled_show->cursor < 3 * step)
     {
        OLED_ShowString(1, 1 ,"  Calibration", 2); 
   	    OLED_ShowString(3, 1 ,"  Basic part", 2);  
        OLED_ShowString(5, 1 ,"* Improve part", 2);
     }
	 else 
	 {
	    OLED_ShowString(1, 1 ,"* Calibration", 2); 
   	    OLED_ShowString(3, 1 ,"  Basic part", 2);  
        OLED_ShowString(5, 1 ,"  Improve part", 2);
	    oled_show->cursor = 0;
	   menu_encoderclear();
	 }
}

void Menu_showT1(volatile OLED_SHOW *oled_show)
{
   if(oled_show->cursor >= 0 && oled_show->cursor <= step)
   {
       OLED_ShowString(1, 1 ,"* White", 2); 
       OLED_ShowString(3, 1 ,"  Black", 2);
   }
   else if(oled_show->cursor > step && oled_show->cursor < 2 * step)
   {
       OLED_ShowString(1, 1 ,"  White", 2); 
       OLED_ShowString(3, 1 ,"* Black", 2);
   }
   else if(oled_show->cursor >= 2 * step && oled_show->cursor < 3 * step)
   {
       OLED_ShowString(1, 1 ,"  White", 2); 
       OLED_ShowString(3, 1 ,"  Black", 2);
   }
   else 
   {
       OLED_ShowString(1, 1 ,"* White", 2); 
       OLED_ShowString(3, 1 ,"  Black", 2);
       oled_show->cursor = 0;
       menu_encoderclear();
   }
   
   if(oled_show->message.white_calibration_flag == 1)
   {
       OLED_ShowString(5, 1 ,"White done", 2);
   }
   else
   {
       OLED_ShowString(5, 1 ,"White waiting", 2);
   }

   if(oled_show->message.black_calibration_flag == 1)
   {
       OLED_ShowString(7, 1 ,"Black done", 2);
   }
   else
   {
       OLED_ShowString(7, 1 ,"Black waiting", 2);
   }

}


void Menu_showT2(volatile OLED_SHOW *oled_show)
{
   if(oled_show->cursor >= 0 && oled_show->cursor < step) oled_show->message.N = 1;
    else if(oled_show->cursor >= step && oled_show->cursor < 2 * step) oled_show->message.N = 2;
    else if(oled_show->cursor >= 2 * step && oled_show->cursor < 3 * step) oled_show->message.N = 3;
    else if(oled_show->cursor >= 3 * step && oled_show->cursor < 4 * step) oled_show->message.N = 4;
    else if(oled_show->cursor >= 4 * step && oled_show->cursor < 5 * step) oled_show->message.N = 5;
    else
    {
        oled_show->message.N = 1;
        oled_show->cursor = 0;
        menu_encoderclear();
    }

    OLED_ShowString(1, 1 ," Basic part", 2);
    char message[40];
    sprintf(message," N = %d",oled_show->message.N);
    OLED_ShowString(3, 1 ,message, 2);
}


void Menu_showT3(volatile OLED_SHOW *oled_show)
{
  if(oled_show->cursor >= 0 && oled_show->cursor < step) oled_show->message.N = 1;
    else if(oled_show->cursor >= step && oled_show->cursor < 2 * step) oled_show->message.N = 2;
    else if(oled_show->cursor >= 2 * step && oled_show->cursor < 3 * step) oled_show->message.N = 3;
    else 
    {
        oled_show->message.N = 1;
        oled_show->cursor = 0;
        menu_encoderclear();
    }

    OLED_ShowString(1, 1 ," Improve part", 2);
    char message[40];
    sprintf(message," M = %d",oled_show->message.N);
    OLED_ShowString(3, 1 ,message, 2);
}




void Menu_showmainkeyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT1keyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT2keyfuc(volatile OLED_SHOW *oled_show);
void Menu_showT3keyfuc(volatile OLED_SHOW *oled_show);
// void Menu_showT4keyfuc(volatile OLED_SHOW *oled_show);


void Menu_keyfuc(volatile OLED_SHOW *oled_show)
{
	 oled_show->last_key_value = oled_show->key_value;
	 Key_read(&(oled_show->key));
     oled_show->key_value = oled_show->key.pin_value;

 if(oled_show->last_key_value == 1 && oled_show->key_value == 0)
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
	 else if(oled_show->menu_num == 3)
	 {
	    Menu_showT3keyfuc(oled_show);
	 }
	//  if (oled_show->menu_num == 4)
	//  {
	//     Menu_showT4keyfuc(oled_show);
	//  }
 }

}

void Menu_showmainkeyfuc(volatile OLED_SHOW *oled_show)
{
  	if(oled_show->cursor >= 0 && oled_show->cursor < step) 
    {
        oled_show->menu_num = 1;
        oled_show->message.problem_index = 0; // Set problem index for task 1
    } 
    else if(oled_show->cursor >= step && oled_show->cursor < 2 * step) 
    {
        oled_show->menu_num = 2;
    }
    else if(oled_show->cursor >= 2 * step && oled_show->cursor < 3 * step){
        oled_show->menu_num = 3;        
    } 

    oled_show->cursor = 0; // Reset cursor
    menu_encoderclear(); // Clear the encoder counter
    OLED_CLS();
}

void Menu_showT1keyfuc(volatile OLED_SHOW *oled_show)
{
         static unsigned short calibrated_white_buffer[8] = {0}, calibrated_black_buffer[8] = {0};

	 if(oled_show->cursor >= 0 && oled_show->cursor < step) {
        Get_Anolog_Value(&(oled_show->message.huidu.huidu_sensor),calibrated_white_buffer);
        Debugger_printf("white:%d,%d,%d,%d,%d,%d,%d,%d\n",calibrated_white_buffer[0],calibrated_white_buffer[1],calibrated_white_buffer[2],calibrated_white_buffer[3],calibrated_white_buffer[4],calibrated_white_buffer[5],calibrated_white_buffer[6],calibrated_white_buffer[7]);
        oled_show->message.white_calibration_flag = 1;
          if( oled_show->message.black_calibration_flag == 1)
          {
            No_MCU_Ganv_Sensor_Init(&(oled_show->message.huidu.huidu_sensor),calibrated_white_buffer,calibrated_black_buffer);
          }
     }
     else if(oled_show->cursor >= step && oled_show->cursor < 2 * step) {
        Get_Anolog_Value(&(oled_show->message.huidu.huidu_sensor),calibrated_black_buffer);
        Debugger_printf("black:%d,%d,%d,%d,%d,%d,%d,%d\n",calibrated_black_buffer[0],calibrated_black_buffer[1],calibrated_black_buffer[2],calibrated_black_buffer[3],calibrated_black_buffer[4],calibrated_black_buffer[5],calibrated_black_buffer[6],calibrated_black_buffer[7]);
        oled_show->message.black_calibration_flag = 1;

         if(oled_show->message.white_calibration_flag == 1)
         {
            No_MCU_Ganv_Sensor_Init(&(oled_show->message.huidu.huidu_sensor),calibrated_white_buffer,calibrated_black_buffer);
         }
     }
     else if(oled_show->cursor >= 2 * step && oled_show->cursor < 3 * step)
    {
        oled_show->message.black_calibration_flag = 0;
        oled_show->message.white_calibration_flag = 0;
        oled_show->message.N = 1;
        oled_show->message.problem_index = 0;
        
        oled_show->menu_num = 0; // Reset to main menu
        oled_show->cursor = 0;
        menu_encoderclear();
        
    }
    OLED_CLS();
}

void Menu_showT2keyfuc(volatile OLED_SHOW *oled_show)
{
     oled_show->message.problem_index = 1;
     oled_show->cursor = 0; // Reset cursor
     oled_show->menu_num = 0; // Reset to main menu
     menu_encoderclear(); // Clear the encoder counter
     OLED_CLS();
}

void Menu_showT3keyfuc(volatile OLED_SHOW *oled_show)
{
     oled_show->message.problem_index = 2;
     oled_show->cursor = 0; // Reset cursor
     oled_show->menu_num = 0; // Reset to main menu
     menu_encoderclear(); // Clear the encoder counter
     OLED_CLS();
}