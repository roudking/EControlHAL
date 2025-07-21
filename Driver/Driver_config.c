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

	.encoder_port = &LeftDriver_Encoder_Timer,

	.pwm_port = &LeftDriver_Timer,
	.pwm_timer_autoreload = LeftDriver_Timer_autoreload,
	.channel[0] = LeftDriver_TIM_channel_1,
	.channel[1] = LeftDriver_TIM_channel_2,

	.encoder_polarity = leftdriver_encoder_polarity,

	.pwm_polarity = leftdriver_pwm_polarity

};

DRIVER_CONFIG rightdriver = {
	.encoder_port = &RightDriver_Encoder_Timer,

	.pwm_port = &RightDriver_Timer,
	.pwm_timer_autoreload = RightDriver_Timer_autoreload,
	.channel[0] = RightDriver_TIM_channel_1,
	.channel[1] = RightDriver_TIM_channel_2,

	.encoder_polarity = rightdriver_encoder_polarity,

	.pwm_polarity = rightdriver_pwm_polarity
};