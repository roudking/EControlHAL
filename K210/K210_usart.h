#ifndef _K210_USART_H
#define _K210_USART_H

#include "serial.h"
#include "cJSON.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "K210.h"

#define K210_UART huart3 

void K210_uartinit(void);
void K210_uartsend(unsigned char *p_data,unsigned int uiSize);
void K210_startit(void);
void K210_stopit(void);

#endif
