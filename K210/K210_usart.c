#include "K210_usart.h"

static void K210_uartcallback(void);

uint8_t k210_uctemp;
#define BUFFER_SIZE 255
unsigned char k210_cmd_buffer[BUFFER_SIZE]; //命令缓冲区
char k210_cmd[1000];

//K210函数注册
void K210_uartinit(void)
{
  // Set up UART callbacks
   usart_callbackregister(&K210_UART, K210_uartcallback);
   usart_rx_it_start(&K210_UART,&k210_uctemp);
}

static void K210_uartcallback(void)
{
	 
			static int i = 0;
	  if (k210_uctemp != '\n' && i < BUFFER_SIZE - 1) {
            k210_cmd_buffer[i++] = k210_uctemp;
        }
		 
	 else 
		{
					k210_cmd_buffer[i] = '\0'; // 完成字符串
					i = 0; // 重置索引
			
		   cJSON *json = cJSON_Parse((char *)k210_cmd_buffer);
		
		  if (json) {
						cJSON *json_command = cJSON_GetObjectItem(json, "cmd");
		
			   if (json_command && json_command->type == cJSON_String) 
				 {
            strcpy(k210_cmd, json_command->valuestring); // 更新全局变量cmd
				   
							
							 if(strcmp(k210_cmd,"send_angle") == 0)
						  {
								  cJSON *voice_angle = cJSON_GetObjectItem(json, "voice_angle");
							
								 		// 从 result 中提取数字字符串
										
								 int result_num = voice_angle->valueint;
								if(result_num < 0) result_num += 360;
						
								result_num = 360 - result_num;
				   
								 K210_angledataIN(result_num);
								 K210_stateIN(k210_complite_echo);
								
						  }
							
					} 
				memset(k210_cmd_buffer,'\0',sizeof(k210_cmd_buffer));
				memset(k210_cmd,'\0',sizeof(k210_cmd));
  		
		   }
	
	     cJSON_Delete(json);	
  }
   usart_rx_it_start(&K210_UART,&k210_uctemp);
}


