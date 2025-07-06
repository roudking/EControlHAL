#ifndef _RESBERRY_UART_H 
#define _RESBERRY_UART_H

#include "serial.h"
#include "cJSON.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Resberry_Pi.h"

#define Resberry_UART huart2 
#define Resberry_printf(fmt, ...)  usart_printf(&Resberry_UART, fmt, ##__VA_ARGS__)

void Resberry_uartinit(void);


#endif
