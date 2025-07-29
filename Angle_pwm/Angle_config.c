#include "Angle_config.h"

static void angle_tim_ic_callback(void);

ANGLE_CONFIG angle1_config = {
    .htim = &htim1,
    .prescaler = 8, // Default prescaler value, can be set later
    .cnt_clk = 72000000 / (8 + 1), // Counter clock frequency based on prescaler
    .tim_ic_callback = angle_tim_ic_callback,
};

static void angle_tim_ic_callback(void) {
   angle1_config.angle_callbackfunc(&angle1_config); // Call the angle calculation callback function
}

void Angle_config_set_anglecallback(ANGLE_CONFIG *config, void (*callback)(ANGLE_CONFIG *)) {
    config->angle_callbackfunc = callback; // Set the angle calculation callback function
}


