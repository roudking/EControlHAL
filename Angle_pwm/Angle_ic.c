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
