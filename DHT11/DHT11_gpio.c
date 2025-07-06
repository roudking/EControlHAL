#include "DHT11_gpio.h"


//对于stm32来说，是输出
void DH11_GPIO_Init_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  GPIO_InitStruct.Pin = DHT11_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);

}

//对于stm32来说，是输入
void DH11_GPIO_Init_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  GPIO_InitStruct.Pin = DHT11_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);

}




