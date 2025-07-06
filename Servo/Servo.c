#include "Servo.h"

void Servo_init(void)
{
  Servo_pwminit();
}

void Servo_settargetangle(SERVO *servo,float angle)
{
   servo->angle = angle;
}

void Servo_gotoangle(SERVO* servo)
{
  int comparevalue = (int)Servo_Comparevaluecal(servo->angle);
	Servo_setcompare(comparevalue);
}
