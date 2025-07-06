#include "serial.h"

int fputc(int ch, FILE *f) {
HAL_UART_Transmit(&Debugger_UART, (uint8_t *)&ch, 1, 0xFFFF);
return ch;
}


// 为每个外设实例注册回调
static UART_Callback USART1_Callback = NULL;
static UART_Callback USART2_Callback = NULL;
static UART_Callback USART3_Callback = NULL;
static UART_Callback USART4_Callback = NULL;
static UART_Callback USART5_Callback = NULL;
static UART_Callback USART6_Callback = NULL;

void usart_rx_it_start(UART_HandleTypeDef *huart,uint8_t *pData)
{
   HAL_UART_Receive_IT(huart,pData,1);
}

void usart_rx_it_stop(UART_HandleTypeDef *huart)
{
   __HAL_UART_DISABLE_IT(huart,UART_IT_RXNE);
}

void usart_transmit(UART_HandleTypeDef *huart,unsigned char *p_data, unsigned int uiSize)
{	
	 HAL_UART_Transmit(huart,p_data,uiSize,HAL_MAX_DELAY);
}



// 在初始化时注册不同的回调函数
void usart_callbackregister(UART_HandleTypeDef *huart,UART_Callback callback_function) {
	if(huart->Instance == USART1)
	{
     USART1_Callback = callback_function;
	}
    else if (huart->Instance == USART2)
    {
     USART2_Callback = callback_function;
    }
   else if(huart->Instance == USART3)
	 {
	   USART3_Callback = callback_function;
	 }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1 && USART1_Callback) {
        USART1_Callback();
    }else if (huart->Instance == USART2 && USART2_Callback) {
        USART2_Callback();
    }
		else if(huart->Instance == USART3 && USART3_Callback){
		    USART3_Callback();
		}
}


