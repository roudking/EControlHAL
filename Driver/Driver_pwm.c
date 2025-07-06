#include "Driver_pwm.h"

void Driver_pwminit(void)
{
  pwm_init(&LeftDriver_Timer , LeftDriver_TIM_channel_1);
  pwm_init(&LeftDriver_Timer , LeftDriver_TIM_channel_2);
  pwm_init(&RightDriver_Timer, RightDriver_TIM_channel_1);
  pwm_init(&RightDriver_Timer, RightDriver_TIM_channel_2);
}

void Driver_setpwm(int pwm1,int pwm2)
{
	if( pwm1 > 0) 
		{
			pwm_set(&LeftDriver_Timer, LeftDriver_TIM_channel_1, pwm1);
			pwm_set(&LeftDriver_Timer, LeftDriver_TIM_channel_2, 0);
		}
	else if(pwm1 < 0)
		{
			pwm_set(&LeftDriver_Timer, LeftDriver_TIM_channel_1, 0);
			pwm_set(&LeftDriver_Timer, LeftDriver_TIM_channel_2, -pwm1);
		}
	else if(pwm1 == 0)
		{
	 		pwm_set(&LeftDriver_Timer, LeftDriver_TIM_channel_1, LeftDriver_Timer_autoreload);
			pwm_set(&LeftDriver_Timer, LeftDriver_TIM_channel_2, LeftDriver_Timer_autoreload);
		}
  if( pwm2 > 0) 
		{
			pwm_set(&RightDriver_Timer, RightDriver_TIM_channel_1, 0);
			pwm_set(&RightDriver_Timer, RightDriver_TIM_channel_2, pwm2);
		}
	else if(pwm2 < 0)
		{
			pwm_set(&RightDriver_Timer, RightDriver_TIM_channel_1, -pwm2);
			pwm_set(&RightDriver_Timer, RightDriver_TIM_channel_2, 0);
		}
	else if(pwm2 == 0)
	{
			pwm_set(&RightDriver_Timer, RightDriver_TIM_channel_1, RightDriver_Timer_autoreload);
			pwm_set(&RightDriver_Timer, RightDriver_TIM_channel_2, RightDriver_Timer_autoreload);
	}
}


