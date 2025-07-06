#include "hwt101_uart.h"

unsigned char ucTemp;

static void HWT101_UARTCallback(void);

void Uart2Send(unsigned char *p_data, unsigned int uiSize)
{	
	usart_transmit(&HWT101_UART,p_data,uiSize);
}

void HWT101_UARTStart(void)
{
  usart_callbackregister(&HWT101_UART, HWT101_UARTCallback);
  usart_rx_it_start(&HWT101_UART,&ucTemp);
}


static void HWT101_UARTCallback(void)
{
	WitSerialDataIn(ucTemp);
	usart_rx_it_start(&HWT101_UART,&ucTemp);;
}
