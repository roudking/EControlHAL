#include "encoder.h"

void encoder_init(TIM_HandleTypeDef* tim)
{
	 HAL_TIM_Encoder_Start(tim, TIM_CHANNEL_ALL);
}

int16_t encoder_getcounter(TIM_HandleTypeDef* tim)
{
   int16_t speed =  __HAL_TIM_GET_COUNTER(tim);
   __HAL_TIM_SET_COUNTER(tim,0);
			return speed;
}

int16_t encoder_justgetcounter(TIM_HandleTypeDef* tim)
{
   int16_t speed =  __HAL_TIM_GET_COUNTER(tim);
			return speed;
}

void encoder_clear(TIM_HandleTypeDef* tim)
{
   __HAL_TIM_SET_COUNTER(tim,0);
}