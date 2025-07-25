#include "Angle_config.h"

ANGLE_CONFIG angle_config = {
    .htim = &htim1, // Timer handle for input capture
    .prescaler = 8, // Default prescaler value, can be set later
    .cnt_clk = 72000000 / (8 + 1), // Counter clock frequency based on prescaler
};
