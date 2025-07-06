#include "Driver_tim_it.h"

void Driver_timcallback(void);

void Driver_tim_it_init(void)
{
  tim_callbackregister(&Driver_TIM_IT_Timer,Driver_timcallback);
	tim_it_start(&Driver_TIM_IT_Timer);
}

void Driver_timcallback(void)
{
  
}