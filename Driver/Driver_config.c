#include "Driver_config.h"

//电机编码器设置
#define LeftDriver_Encoder_Timer  htim
#define RightDriver_Encoder_Timer htim

//电机PWM端口设置
#define LeftDriver_Timer htim
#define LeftDriver_TIM_channel_1 TIM_CHANNEL_
#define LeftDriver_TIM_channel_2 TIM_CHANNEL_

#define RightDriver_Timer htim
#define RightDriver_TIM_channel_1 TIM_CHANNEL_
#define RightDriver_TIM_channel_2 TIM_CHANNEL_


#define LeftDriver_Timer_autoreload  
#define RightDriver_Timer_autoreload  

#define leftdriver_encoder_polarity 1
#define leftdriver_pwm_polarity 1

#define rightdriver_encoder_polarity 0
#define rightdriver_pwm_polarity 0


DRIVER_CONFIG leftdriver = {

	
	.Encoder_PORT = &LeftDriver_Encoder_Timer,

	.DriverPWM_PORT = &LeftDriver_Timer,
	.DriverPWMTimer_autoreload = LeftDriver_Timer_autoreload,
	.Channel[0] = LeftDriver_TIM_channel_1,
	.Channel[1] = LeftDriver_TIM_channel_2,
	
	.Encoder_polarity = leftdriver_encoder_polarity,

	.Pwm_polarity = leftdriver_pwm_polarity

};

DRIVER_CONFIG rightdriver = {
	.Encoder_PORT = &RightDriver_Encoder_Timer,

	.DriverPWM_PORT = &RightDriver_Timer,
	.DriverPWMTimer_autoreload = RightDriver_Timer_autoreload,
	.Channel[0] = RightDriver_TIM_channel_1,
	.Channel[1] = RightDriver_TIM_channel_2,

	.Encoder_polarity = rightdriver_encoder_polarity,

	.Pwm_polarity = rightdriver_pwm_polarity
};