#ifndef _RESBERRY_UART_H 
#define _RESBERRY_UART_H

#include "serial.h"
#include "cJSON.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Raspberry_Pi.h"

#define Raspberry_UART huart2 
#define Raspberry_printf(fmt, ...)  usart_printf(&Raspberry_UART, fmt, ##__VA_ARGS__)

void Raspberry_uartinit(void);


#endif
