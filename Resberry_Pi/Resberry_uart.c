#include "Resberry_uart.h"

static void Resberry_uartcallback(void);

uint8_t resberry_uctemp;
#define BUFFER_SIZE 255
unsigned char resberry_cmd_buffer[BUFFER_SIZE]; //命令缓冲区
char resberry_cmd[1000];


//树莓派函数注册
void Resberry_uartinit(void)
{
  // Set up UART callbacks
   usart_callbackregister(&Resberry_UART, Resberry_uartcallback);
   usart_rx_it_start(&Resberry_UART,&resberry_uctemp);
}

static void Resberry_uartcallback(void)
{
	 
			static int i = 0;
	  if (resberry_uctemp != '\n' && i < BUFFER_SIZE - 1) {
            resberry_cmd_buffer[i++] = resberry_uctemp;
        }
		 
	 else 
		{
					resberry_cmd_buffer[i] = '\0'; // 完成字符串
					i = 0; // 重置索引
			
		   cJSON *json = cJSON_Parse((char *)resberry_cmd_buffer);
		
		  if (json) {
						cJSON *json_command = cJSON_GetObjectItem(json, "cmd");
		
			   if (json_command && json_command->type == cJSON_String) 
	  			{
            strcpy(resberry_cmd, json_command->valuestring); // 更新全局变量cmd
  				if(strcmp(resberry_cmd,"ping") == 0)
				 {
					// 发送响应
					Resberry_printf("{\"cmd\":\"ping\",\"result\":\"pong\"}\n");
				}
				else if(strcmp(resberry_cmd,"spin") == 0)
				{
					cJSON *speed_json = cJSON_GetObjectItem(json, "speed");
							
			        // 从 speed 中提取数字字符串
			    	int speed = speed_json->valueint;
					Resberry_speeddataIN(speed);
					Resberry_printf("{\"cmd\":\"spin\",\"result\":\"ok\"}\n");
				}
				else if(strcmp(resberry_cmd,"angle") == 0)
				{
				  cJSON *angle_json = cJSON_GetObjectItem(json, "angle");
				  // 从 angle 中提取数字字符串
				  float angle = angle_json->valuedouble;
				  Resberry_angledataIN(angle);
				  Resberry_printf("{\"cmd\":\"angle\",\"result\":\"ok\"}\n");
				 }

				memset(resberry_cmd_buffer,'\0',sizeof(resberry_cmd_buffer));
				memset(resberry_cmd,'\0',sizeof(resberry_cmd));
  		
		     }
        }
	      cJSON_Delete(json);	
      }
	   usart_rx_it_start(&Resberry_UART,&resberry_uctemp);	
}


