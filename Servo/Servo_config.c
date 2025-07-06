#include "Servo_config.h"

#define Servo_Timer_Port    htim1
#define Servo_TIM_channel TIM_CHANNEL_1
#define Servo_TIM_CounterCycleTime    1.0f    //us
#define Servo_kind servo_180
#define bias 0.0f

SERVO_CONFIG servo_config = {
    .Pwm_TIMERPORT = &Servo_Timer_Port,
    .CHANNEL = Servo_TIM_channel,
    .CounterCycleTime = Servo_TIM_CounterCycleTime,
    .kind = Servo_kind,
    .delta_bias = bias
};