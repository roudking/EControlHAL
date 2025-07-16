#ifndef _K210_USART_H
#define _K210_USART_H

#include "serial.h"
#include "cJSON.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "K210.h"

#define K210_UART huart2 
#define K210_printf(fmt, ...)  usart_printf(&K210_UART, fmt, ##__VA_ARGS__)

void K210_uartinit(void);

#endif
