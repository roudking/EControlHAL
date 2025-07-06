#ifndef _DRIVER_PWM_H
#define _DRIVER_PWM_H

#include "pwm.h"

#define LeftDriver_Timer htim1
#define LeftDriver_TIM_channel_1 TIM_CHANNEL_1
#define LeftDriver_TIM_channel_2 TIM_CHANNEL_2

#define RightDriver_Timer htim1
#define RightDriver_TIM_channel_1 TIM_CHANNEL_3
#define RightDriver_TIM_channel_2 TIM_CHANNEL_4

#define LeftDriver_Timer_autoreload 7200
#define RightDriver_Timer_autoreload 7200

void Driver_pwminit(void);
void Driver_setpwm(int pwm1,int pwm2);


#endif
