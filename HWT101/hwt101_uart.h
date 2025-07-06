#ifndef _HWT101_UART
#define _HWT101_UART

#include "serial.h"
#include "wit_c_sdk.h"

#define HWT101_UART huart2

void HWT101_UARTStart(void);
void Uart2Send(unsigned char *p_data, unsigned int uiSize);


#endif
