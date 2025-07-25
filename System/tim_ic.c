#include "tim_ic.h"

uint32_t tim_read_captured_value(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    return HAL_TIM_ReadCapturedValue(htim, Channel);
}

void tim_ic_it_start(TIM_HandleTypeDef *htim,uint32_t Channel)
{
    HAL_TIM_IC_Start_IT(htim, Channel);
}

// 为每个外设实例注册回调
static TIM_ICCallback TIM1_Callback = NULL;
static TIM_ICCallback TIM2_Callback = NULL;
static TIM_ICCallback TIM3_Callback = NULL;
static TIM_ICCallback TIM4_Callback = NULL;
static TIM_ICCallback TIM5_Callback = NULL;
static TIM_ICCallback TIM6_Callback = NULL;
static TIM_ICCallback TIM7_Callback = NULL;

// 在初始化时注册不同的回调函数
void tim_ic_callbackregister(TIM_HandleTypeDef *htim,TIM_ICCallback callback_function) {
	if(htim->Instance == TIM1)
	{
     TIM1_Callback = callback_function;
	}
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
      if (htim->Instance == TIM1 && TIM1_Callback) {
        TIM1_Callback();
    }
}

