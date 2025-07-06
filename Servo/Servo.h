#ifndef _SERVO_H
#define _SERVO_H


#include "Servo_pwm.h"

typedef struct
{
   float angle;
}SERVO;

void Servo_init(void);
void Servo_settargetangle(SERVO *servo,float angle);
void Servo_gotoangle(SERVO* servo);

#endif
