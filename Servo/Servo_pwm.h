#ifndef _SERVO_PWM
#define _SERVO_PWM

#include "pwm.h"

typedef enum
{
  servo_270,
	servo_180
}Servo_Category;


#define Servo_Timer_Port    htim8
#define Servo_TIM_channel TIM_CHANNEL_3
#define Servo_TIM_CounterCycleTime    1.0f    //us
#define Servo_kind servo_180
#define delta_bias 2.0f
 

void Servo_pwminit(void);
void Servo_setcompare(uint16_t pwm);
float  Servo_Comparevaluecal(float angle);



#endif 
