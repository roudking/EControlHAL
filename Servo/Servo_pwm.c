#include "Servo_pwm.h"

void Servo_pwminit(void)
{
  pwm_init(&Servo_Timer_Port,Servo_TIM_channel);
}

void Servo_setcompare(uint16_t pwm)
{
  pwm_set(&Servo_Timer_Port,Servo_TIM_channel,pwm);
}

float  Servo_Comparevaluecal(float angle)
{
		float range;
    if(Servo_kind == servo_270)
		{
		  range = 270.0;
		}
		else if(Servo_kind == servo_180)
		{
		  range = 180.0;
		}
	
	float k = 2000.0/range;
	float high_leveltime = k * (angle - delta_bias) + 500.0;
	float comparevalue = high_leveltime/Servo_TIM_CounterCycleTime;
		return comparevalue;
}

