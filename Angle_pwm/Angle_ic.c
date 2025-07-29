#include "Angle_ic.h"

void Angle_ic_init(ANGLE_CONFIG config) {
    // Initialize the input capture for angle measurement
    tim_ic_it_start(config.htim, TIM_CHANNEL_1);
    tim_ic_it_start(config.htim, TIM_CHANNEL_2);
}

uint32_t Angle_ic_getvalue(ANGLE_CONFIG config,uint32_t channel) {
    // Read the captured value from the specified channel
    return tim_read_captured_value(config.htim, channel);
}

void Angle_ic_callbackfunc(ANGLE_CONFIG *config) { 
			config->CCR1 = Angle_ic_getvalue(*config, TIM_CHANNEL_1);
			if(config->CCR1 != 0)
				{
					config->CCR2 = Angle_ic_getvalue(*config, TIM_CHANNEL_2);
					config->data_buffer.frequency = (double)config->cnt_clk/(config->CCR1+1);
					config->data_buffer.duty = (double)(config->CCR2+1)*100/(config->CCR1+1);
				}
			else
				{
					config->data_buffer.frequency = 0;
					config->data_buffer.duty = 0;
				}
}
