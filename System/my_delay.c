#include "my_delay.h"

void delay_us(uint32_t i)
{
	uint16_t differ = 0xffff- i - 5;//65535-5-i，计数初值，由这个数计数到65535刚好计数us次，
									//也就实现了n us延时

	__HAL_TIM_SET_COUNTER(&DELAY_TIMER, differ);	//设置计数值

	HAL_TIM_Base_Start(&DELAY_TIMER);	//开启定时器

	while(differ < 0xffff-6)
	{
		differ = __HAL_TIM_GET_COUNTER(&DELAY_TIMER); //获取当前计数值
	}

	HAL_TIM_Base_Stop(&DELAY_TIMER);//停止定时器
}

void delay_ms(uint32_t nms)
{
    for (uint32_t i = 0; i < nms; i++) {
        delay_us(1000);  // 延时 1 ms
    }
}
