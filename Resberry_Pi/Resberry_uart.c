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

void Resberry_uartsend(unsigned char *p_data,unsigned int uiSize)
{
   usart_transmit(&Resberry_UART, p_data, uiSize);
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
  					 if(strcmp(resberry_cmd,"color") == 0)
						  {
								 cJSON *result = cJSON_GetObjectItem(json, "result");
							
										// 从 result 中提取 x、y、area
								cJSON *x_item    = cJSON_GetObjectItem(result, "x");
								cJSON *y_item    = cJSON_GetObjectItem(result, "y");
								cJSON *area_item = cJSON_GetObjectItem(result, "area");			
										
									int x =  x_item -> valueint;
									int y =  y_item -> valueint;					   
									int area =  area_item -> valueint;					   
								Resberry_greenareadataIN(area);
								Resberry_stateIN(resberry_complite_echo);
								
						  }
							
							else if(strcmp(resberry_cmd,"number") == 0)
						  {
								 cJSON *result = cJSON_GetObjectItem(json, "result");
							
										// 从 result 中提取数字字符串
									int result_num;
									if(strcmp(result->valuestring,"") == 0)
									{
										 result_num = 0;
									}
									else  result_num = atoi(result->valuestring);

								Resberry_numerdataIN(result_num);
								Resberry_stateIN(resberry_complite_echo);
								
						  }
							
					} 
				memset(resberry_cmd_buffer,'\0',sizeof(resberry_cmd_buffer));
				memset(resberry_cmd,'\0',sizeof(resberry_cmd));
  		
		   }
	
	     cJSON_Delete(json);	
  }
   usart_rx_it_start(&Resberry_UART,&resberry_uctemp);
}


