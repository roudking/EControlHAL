#ifndef TIM_IC_H
#define TIM_IC_H

#include "tim.h"

typedef void (*TIM_ICCallback)(void);

uint32_t tim_read_captured_value(TIM_HandleTypeDef *htim, uint32_t Channel);
void tim_ic_it_start(TIM_HandleTypeDef *htim,uint32_t Channel);
void tim_ic_callbackregister(TIM_HandleTypeDef *htim,TIM_ICCallback callback_function);


#endif