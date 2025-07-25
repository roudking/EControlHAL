#include "Angle.h"

static void Angle_ICCallbackfunc(void);
static ANGLE angle_buffer;

void Angle_Create_and_Initbuffer(ANGLE_CONFIG config) {
    angle_buffer.config = config;

    // Initialize the input capture for angle measurement
    Angle_ic_init(angle_buffer.config);

    // Register the callback function for input capture events
    tim_ic_callbackregister(angle_buffer.config.htim, Angle_ICCallbackfunc);
}


#define cnt_clk 72000000/(71+1)//计数器频率

static void Angle_ICCallbackfunc(void) { 
			angle_buffer.config.CCR1 = Angle_ic_getvalue(angle_buffer.config, TIM_CHANNEL_1);
			if(angle_buffer.config.CCR1 != 0)
				{
					angle_buffer.config.CCR2 = Angle_ic_getvalue(angle_buffer.config, TIM_CHANNEL_2);
					angle_buffer.frequency = (double)cnt_clk/(angle_buffer.config.CCR1+1);
					angle_buffer.duty = (double)(angle_buffer.config.CCR2+1)*100/(angle_buffer.config.CCR1+1);
				}
			else
				{
					angle_buffer.frequency = 0;
					angle_buffer.duty = 0;
				}
}

void Angle_getduty(ANGLE *angle) {
	angle->duty = angle_buffer.duty; // Return the current duty cycle
	angle->frequency = angle_buffer.frequency; // Return the current frequency
}
