#ifndef SERVO_CONFIG_H
#define SERVO_CONFIG_H

#include "pwm.h"

typedef enum
{
  servo_270,
	servo_180
}Servo_Category;

typedef struct
{
  TIM_HandleTypeDef *Pwm_TIMERPORT;
  uint16_t  CHANNEL;
  float CounterCycleTime; //us

  Servo_Category kind;
  
  float delta_bias; //us, the bias of the servo angle
}SERVO_CONFIG;

extern SERVO_CONFIG servo_config;

 

#endif // SERVO_CONFIG_H