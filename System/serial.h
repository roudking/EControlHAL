#ifndef _SERIAL_H
#define _SERIAL_H

#include "usart.h"
#include "stdio.h"

#define Debugger_UART huart6

typedef void (*UART_Callback)(void);

void usart_rx_it_start(UART_HandleTypeDef *huart,uint8_t *pData);
void usart_rx_it_stop(UART_HandleTypeDef *huart);
void usart_transmit(UART_HandleTypeDef *huart,unsigned char *p_data, unsigned int uiSize);
void usart_callbackregister(UART_HandleTypeDef *huart,UART_Callback callback_function);


#endif
