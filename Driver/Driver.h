#ifndef _DRIVER_H
#define _DRIVER_H

#include "Driver_Encoder.h"
#include "Driver_pwm.h"
#include "pid.h"
#include "stdlib.h"

extern PID pidL;
extern PID pidR;

typedef enum
{
  LEFT,
	RIGHT
}POSITION;

typedef struct
{  
	 POSITION position;
   int targetspeed;
	 int currentspeed;
	 int flitspeed;
	 int lastspeed;
	 PID pid;

}MOTOR;

void Driver_init(void);

void Driver_creatmotor(MOTOR *mymotor,PID pid,POSITION Position);

void Driver_setmotor_targetspeed(MOTOR *motor,int target_speed);

void Driver_getmotor_currentspeed(MOTOR *motor);

void Driver_setspeed(MOTOR* motor1,MOTOR* motor2);

void Driver_setspeedwithfliter(MOTOR *motor1,MOTOR *motor2);

#endif
