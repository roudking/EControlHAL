#ifndef _DRIVER_CONFIG
#define _DRIVER_CONFIG

#include "encoder.h"
#include "pwm.h"

typedef struct {

	//电机编码器端口设置
	TIM_HandleTypeDef *Encoder_PORT;

	//电机PWM端口设置
	TIM_HandleTypeDef *DriverPWM_PORT;
	int DriverPWMTimer_autoreload;
	int Channel[2];
  
	//电机编码器极性设置  （软件）
	int Encoder_polarity;

	//电机PWM极性设置（软件）
	int Pwm_polarity;

} DRIVER_CONFIG;


extern DRIVER_CONFIG leftdriver;
extern DRIVER_CONFIG rightdriver;



#endif
