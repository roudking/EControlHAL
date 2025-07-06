#ifndef _RESBERRY_UART_H 
#define _RESBERRY_UART_H

#include "serial.h"
#include "cJSON.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Resberry_Pi.h"

#define Resberry_UART huart1 

void Resberry_uartinit(void);
void Resberry_uartsend(unsigned char *p_data,unsigned int uiSize);

#endif
