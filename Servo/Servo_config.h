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
  TIM_HandleTypeDef *pwm_port; // PWM port for the servo
  uint16_t  channel; // PWM channel for the servo
  float CounterCycleTime; //us

  Servo_Category kind;
  float delta_bias; 
} SERVO_CONFIG;

extern SERVO_CONFIG servo_config;

 

#endif // SERVO_CONFIG_H