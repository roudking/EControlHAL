#ifndef _DRIVER_CONFIG
#define _DRIVER_CONFIG

#include "encoder.h"
#include "pwm.h"

typedef struct {

	//电机编码器端口设置
	TIM_HandleTypeDef *encoder_port;

	//电机PWM端口设置
	TIM_HandleTypeDef *pwm_port;
	int pwm_timer_autoreload;
	int channel[2];
  
	//电机编码器极性设置  （软件）
	int encoder_polarity;

	//电机PWM极性设置（软件）
	int pwm_polarity;

} DRIVER_CONFIG;


extern DRIVER_CONFIG leftdriver;
extern DRIVER_CONFIG rightdriver;



#endif
