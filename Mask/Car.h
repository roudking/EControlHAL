
#ifndef _CAR_H
#define _CAR_H

#include "Driver.h"
#include "Nvigation.h"
#include "my_HWT101.h"
#include "HuiduSensor.h"
#include "Resberry_Pi.h"
#include "Beep.h"
#include "Servo.h"
#include "Stepper.h"
#include "Key.h"
#include "K210.h"
#include "Laser.h"
#include "OLED.h"
#include "math.h"

extern const double require_speed;

typedef enum 
{
	 wait_start,
	 goto_line,
   goto_turnright,
	 goto_turnleft,
	 goto_allwhite,
   turnright,
	 turnleft,
	 beep,
	 stop,
	 voice_trace,
	 go_strightoverflow,
	 go_avoidance,
	 gobackto_line,
	 getnum,
	turnleftto_line,
	gountil_end,
	 turnto_end,
	 resethwt101
}MASK_ASSIGNMENT;

typedef enum
{
	 not_started,
   turning,
   complite_turn
}TURN_STATE;

typedef struct
{
  HWT101_DATA angle;
	PID turn_pid;
	PID trace_pid;
	TURN_STATE turn_state;
	float targetyaw;
	float last_targetyaw;
}IMU;

typedef struct
{
   MOTOR motor1;
	 MOTOR motor2;
	 HUIDU huidu;
	 IMU imu;
	 SERVO servo;
	 STEPPER stepper;
	 RESBERRY resberry;
	 K210 k210;
	 LASER laser;
	 My_KEY key;
	 NVIGATION nvigation;
	 int distance;

	 MASK_ASSIGNMENT mask_assignment[100]; 

}CAR;

void Car_creatimu(IMU *imu,PID tracePid,PID turnPid);
void Car_creatmotor(MOTOR *motor,PID pid,POSITION position);
void Car_creatservo(SERVO *servo,float zero_angle);
void Car_creatstepper(STEPPER *stepper,int id);
void Car_settargetyaw(CAR *car,float target_yaw);
void Car_getdistance(CAR *car);
void Car_calrealspeed(float *real_speed,CAR *car);
void Car_returnnum(CAR *car,int* num1,int *num2);

int Car_gotolinefuc(CAR *car);
int Car_gostrightoverflowfuc(CAR *car);
int Car_gototurnrightfuc(CAR *car);
int Car_gototurnleftfuc(CAR *car);
int Car_turnrightfuc(CAR *car);
int Car_turnleftfuc(CAR *car);
int Car_stopfuc(CAR *car);
int Car_beepfuc(CAR *car);
int Car_goavoidance(CAR *car);
int Car_gobacktolinefuc(CAR *car);
int Car_gotoallwhitefuc(CAR *car);
int Car_waitstartfuc(CAR *car);
int Car_getnumberfuc(CAR *car);
int Car_turnlefttolinefuc(CAR *car);
int Car_gountilend(CAR *car);
int Car_turntoend(CAR *car);
int Car_resethwt101fuc(CAR *car);
int Car_voicetrance(CAR *car);

#endif 
