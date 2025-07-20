#include "Raspberry_uart.h"

static void Raspberry_uartcallback(void);

uint8_t raspberry_uctemp;
#define BUFFER_SIZE 255
unsigned char raspberry_cmd_buffer[BUFFER_SIZE]; //命令缓冲区
char raspberry_cmd[1000];


//树莓派函数注册
void Raspberry_uartinit(void)
{
  // Set up UART callbacks
   usart_callbackregister(&Raspberry_UART, Raspberry_uartcallback);
   usart_rx_it_start(&Raspberry_UART,&raspberry_uctemp);
}

static void Raspberry_uartcallback(void)
{
	 
			static int i = 0;
	  if (raspberry_uctemp != '\n' && i < BUFFER_SIZE - 1) {
            raspberry_cmd_buffer[i++] = raspberry_uctemp;
        }
		 
	 else 
		{
					raspberry_cmd_buffer[i] = '\0'; // 完成字符串
					i = 0; // 重置索引
			
		   cJSON *json = cJSON_Parse((char *)raspberry_cmd_buffer);
		
		  if (json) {
						cJSON *json_command = cJSON_GetObjectItem(json, "cmd");
		
			   if (json_command && json_command->type == cJSON_String) 
	  			{
            strcpy(raspberry_cmd, json_command->valuestring); // 更新全局变量cmd
  				if(strcmp(raspberry_cmd,"ping") == 0)
				 {
					// 发送响应
					Raspberry_printf("{\"cmd\":\"ping\",\"result\":\"pong\"}\n");
				}
				else if(strcmp(raspberry_cmd,"spin") == 0)
				{
					cJSON *speed_json = cJSON_GetObjectItem(json, "speed");
							
			        // 从 speed 中提取数字字符串
			    	int speed = speed_json->valueint;
					Raspberry_speeddataIN(speed);
					Raspberry_printf("{\"cmd\":\"spin\",\"result\":\"ok\"}\n");
				}
				else if(strcmp(raspberry_cmd,"angle") == 0)
				{
				  cJSON *angle_json = cJSON_GetObjectItem(json, "angle");
				  // 从 angle 中提取数字字符串
				  float angle = angle_json->valuedouble;
				  Raspberry_angledataIN(angle);
				  Raspberry_printf("{\"cmd\":\"angle\",\"result\":\"ok\"}\n");
				 }

				memset(raspberry_cmd_buffer,'\0',sizeof(raspberry_cmd_buffer));
				memset(raspberry_cmd,'\0',sizeof(raspberry_cmd));
  		
		     }
        }
	      cJSON_Delete(json);	
      }
	   usart_rx_it_start(&Raspberry_UART,&raspberry_uctemp);	
}


