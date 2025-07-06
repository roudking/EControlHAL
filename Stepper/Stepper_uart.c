#include "Stepper_uart.h"


/**********************************************************
***	Emm_V5.0步进闭环控制例程
***	编写作者：ZHANGDATOU
***	技术：张大头闭环伺服
***	淘宝店铺：https://zhangdatou.taobao.com
***	CSDN博客：http s://blog.csdn.net/zhangdatou666
***	qq交流群：262438510
**********************************************************/

__IO bool rxFrameFlag = false;
__IO uint8_t rxCmd[FIFO_SIZE] = {0};
__IO uint8_t rxCount = 0;
uint8_t received_byte;


void usart_SendByte(uint16_t data)
{
     usart_transmit(&Stepper_UART_PORT, (uint8_t *)&data, 1);
}

void usart_SendCmd(__IO uint8_t *cmd, uint8_t len)
{
     usart_transmit(&Stepper_UART_PORT, cmd, len);
}




