#ifndef _STEPPER_H
#define _STEPPER_H

#include "Emm_V5.h"
#include "math.h"
#include "stdio.h"

#define Stepper_id 1

typedef struct
{
	int stepper_id;
	int step;
	int dir;
  float current_targetangle;
	float last_targetangle;
}STEPPER;

void Stepper_creatstepper(STEPPER *stepper,int id);
void Stepper_setzero(STEPPER *stepper);
void Stepper_gotozero(STEPPER *stepper);
void Stepper_setstep(STEPPER *stepper,int step);
void Stepper_setangle(STEPPER *stepper,float target_angle);


#endif